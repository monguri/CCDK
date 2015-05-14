#include <time.h>

#ifndef WIN32
#include <unistd.h>
#endif

#include "hiredis/hiredis.h"


#include "vce.h"
#include "moyai/cumino.h"
#include "moyai/common.h"

#include "picojson/picojson.h" 

#include <stdio.h>
#include <ctype.h>

#include "vce.h"

#include "ssproto_sv.h"
#include "presence.h"

const int DBPORT = 22222;
const int RTPORT = 22223;

const int ABS_MAXCON = 200;
int g_maxcon = 30; // To avoid using up too much memory by default value
bool g_dump_shared_projects = false;
bool g_dump_projects = false;
bool g_enable_abort_on_parser_error = false;
bool g_enable_realtime = false; 
bool g_enable_database = false;
int g_emulate_slow_disk_ms = 0;
int g_channel_maxcon = 30;
int g_tcp_timeout = 10; // 10 for LAN (GbE)
bool g_enable_fsync = false;
char g_redis_addr[1024] = "localhost";

char g_topdir[1024] = "./datadir";
redisContext *g_redis;
tcpcontext_t g_dbctx; // For Database server
tcpcontext_t g_rtctx; // For Realtime server

long long g_loopcnt;


class ChannelMember {
public:
    conn_t co;
    int x, y; // Position 
    time_t last_active_at;
    void set( conn_t c ) {
        co = c;
        x=0; y=0;
        last_active_at = time(NULL);
    }
};

class Channel {
public:
    int id; // Not used when 0
    time_t last_active_at; // Will be destroyed soon after stopping receiving data or closed
    ChannelMember members[256]; // Stuffed from the beginning. Re-stuff when deletion
    int num_members; // Total number of members used.
    bool leave( conn_t c ) {
        for(int i=0;i<num_members;i++) {
            if( vce_conn_is_equal( members[i].co, c ) ) {
                deleteMemberAt(i);
                return true;
            }
        }
        return false; // not found
    };
    void deleteMemberAt( int ind ) {
        assert(ind>=0 && ind<elementof(members));
        for(int i=ind+1;i<elementof(members);i++){
            members[i-1] = members[i];
        }
        num_members --;
    }
    bool join( conn_t c ) {
        for(int i=0;i<num_members;i++) {
            if( vce_conn_is_equal( members[i].co, c ) ) {
                return false;
            }
        }
        if( num_members >= elementof(members) ) return false;
        members[num_members].set(c);
        num_members ++;
        return true;
    }
    // TODO: Now scanning every members.  Can be tuned by updating less frequent though.
    bool updatePosition( conn_t co, int x, int y ) {
        for(int i=0;i<num_members;i++) {
            if( vce_conn_is_equal( members[i].co, co ) ) {
                members[i].x = x;
                members[i].y = y;
                members[i].last_active_at = time(NULL); // TODO: Can be tuned by caching.
                return true;
            }
        }
        return false;
    }
    int getMemberCount() { return num_members; }
};

Channel g_channels[1024]; // Max number of concurrent online project at the same.


class ConnectionState {
public:
    double last_ping_at;
    Channel *cur_channel_cache; // Pointer to current channel joined, to avoid searching every time.
    int cur_channel_id; // Channel ID for checking pointer consistency.
    void init() {
        cur_channel_cache = NULL;
        cur_channel_id = 0;
        last_ping_at = 0;
    }
};



/////////
const char *getConnectionType( conn_t c ) {
    tcpcontext_t tctx = vce_conn_get_tcpcontext(c);
    if(tctx == g_dbctx ) {
        return "DB";
    } else {
        return "RT";
    }
}

/////////





typedef struct {
public:
    unsigned int by_conn_id; // Not locked when 0.
    time_t lock_at;
    
} LockEntry;

#define LOCK_TIMEOUT 5

class LockGrid {
public:
    int id; // Not used when 0.
    static const int W=128;
    static const int H=128;    
    LockEntry entries[H][W];
    int lock_cnt;
    LockGrid() : lock_cnt(0) {
        clear();
    };
    void clear() {
        id = 0;
        lock_cnt = 0;
        memset(entries, 0, sizeof(entries) );
    }
    bool lock( int x, int y, int by ) {
        if(x>=W || y>=H ||x<0 ||y<0) return false;
        if( entries[y][x].by_conn_id != 0 ) {
            return false; // Can't lock twice
        }
        entries[y][x].by_conn_id = by;
        entries[y][x].lock_at = time(NULL);
        lock_cnt ++;
        assertmsg( lock_cnt <= W*H, "LockGrid::lock(%d,%d,%d): lock_cnt:%d ", x,y,by, lock_cnt );
        return true;
    }
    bool unlock( int x, int y, unsigned int by ) {
        if(x>=W || y>=H || x<0 || y<0 ) return false;
        if( entries[y][x].by_conn_id == by ) {
            entries[y][x].by_conn_id = 0;
            lock_cnt --;
            assert( lock_cnt >= 0 );
            return true;
        }
        return false;
    }
    bool keepLock( int x,  int y, unsigned int by  ) {
        if(x>=W || y>=H || x<0 || y<0 ) return false;
        if( entries[y][x].by_conn_id == by ) {
            entries[y][x].lock_at = time(NULL);
            //            print("keep %d,%d by %d", x,y, by );
            return true;
        }
        return false;
    }
    int unlockAllBy( unsigned int by ) {
        int cnt=0;
        for(int y=0;y<H;y++) {
            for(int x=0;x<W;x++){
                if( entries[y][x].by_conn_id == by ) {
                    entries[y][x].by_conn_id = 0;
                    lock_cnt--;
                    assert(lock_cnt>=0);
                    cnt++;
                }
            }
        }
        return cnt;
    }
    int countLock() {
        return lock_cnt;
    }
    int pollLockTimeout() {
        print("pollLockTimeout: id:%d",id);
        int unlocked = 0;
        time_t thres = time(NULL) - LOCK_TIMEOUT;
        //        print("thr:%u t:%u", (unsigned int) thres, (unsigned int )time(NULL) );
        for(int y=0;y<H;y++) {
            for(int x=0;x<W;x++){
                if( entries[y][x].by_conn_id != 0 && thres > entries[y][x].lock_at  ) {
                    print("lock timeout at %d,%d by:%d", x,y, entries[y][x].by_conn_id );
                    entries[y][x].by_conn_id = 0;
                    lock_cnt --;
                    assert( lock_cnt >= 0 );
                    unlocked ++;
                }
            }
        }
        return unlocked;
    }
};

LockGrid g_lockgrids[256];


class LockProject : public LockEntry {
public:
    int id;
    int category;
    LockProject() : LockEntry(), id(0), category(0) {}
};

LockProject g_lockprojects[1024];


///////////
void pollAllImageStore();
void pollProgressLockGrids();
void pollAllProject();
void cleanAll( conn_t c );
bool checkCSChannel( ConnectionState *cs);
void pollAllLockProject();
void printStat();

///////////
int conn_closewatcher( conn_t c, CLOSE_REASON reason ) {
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( c, NULL );
    
    print("[closewatcher type:%s reason:%s cur_chid:%d", getConnectionType(c), vce_strerror_close_reason(reason), cs->cur_channel_id );
    
    switch(reason) {
    case CLOSE_REASON_PARSER:
        if( g_enable_abort_on_parser_error ) {
            assertmsg( false, "  Protocol callback error (this may caused by unglaceful client kill)." );
        } else {
            prt( "[close-pcallback-error (this may caused by unglaceful client kill)]" );
        }
        break;
    default:
        break;
    }
    cleanAll(c);
    return 0;
}
void cleanAll( conn_t c ) {
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( c, NULL );
    if( checkCSChannel(cs) ) {
        // TODO: Better to clean presence too. (Otherwise times out). Need user_id to clean presence.
        cs->cur_channel_cache->leave(c);
        cs->cur_channel_cache = NULL;
        cs->cur_channel_id = 0;
    }
 
    for(int i=0;i<elementof(g_lockgrids);i++){
        if( g_lockgrids[i].id != 0 ) {
            g_lockgrids[i].unlockAllBy( c.serial );
        }
    }
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id != 0 && g_lockprojects[i].by_conn_id == c.serial ) {
            //            print("unlockAll: project:%d cat:%d", g_lockprojects[i].id, g_lockprojects[i].category );
            g_lockprojects[i].id = 0;
            g_lockprojects[i].category = 0;
        }
    }
}

int conn_acceptwatcher( conn_t c ) {
    //    vce_errout("acceptwatcher serial:%d",c.serial );
    prt("[newconn serial:%d]", c.serial );
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( c, NULL );
    cs->init();
    unsigned int minv;
    unsigned int majv = ssproto_sv_get_version( &minv );
    ssproto_version_notify_send( c, majv, minv );
    return 0;
}
int ssproto_sv_recv_error_callback( conn_t c, int e ) {
    vce_errout( "ssproto_sv_recv_error_callback e:%d\n",e );
    return 0;
}

int ssproto_sv_sender( conn_t c, char *data, int len ) {
    if( vce_conn_is_closed(c) ) {
        return 0;
    }
    
    char *rb, *wb;
    int rbl, wbl;
    vce_conn_get_buffer( c, &rb, &rbl, &wb, &wbl );

    //    if( wbl > 128 * 1024 ) {
    //        print("write buffer high:%dK in conn:%d", wbl/1024, c.serial );
    //    }

    int ret = vce_protocol_unparser_bin32( c, data, len );
    if(ret<0){
        print("ssproto_sv_sender: unparser returned error:%d conntype:%s", ret, getConnectionType(c));
        if(ret==VCE_EWBFULL ) {
            print("  Write buffer is full! buffer: rused:%d wused:%d serial:%d", rbl, wbl, c.serial);
            vce_conn_close(c);
        }
        
    }
    return ret;
}
int ssproto_toolong_recv_warning( conn_t c,int proto_id,int length) {
    vce_errout( "ssproto_toolong_recv_warning. proto_id:%d len:%d\n",proto_id, length );
    assert(0);
    return 0;
}

bool loadAllSharedProjects();
void loadAllNecessaryFiles() {
    loadAllSharedProjects();
}
int getCurrentConnNum() {
    tcpcontext_stat_t dbst, rtst;
    memset( &dbst, 0, sizeof(dbst) );
    memset( &rtst, 0, sizeof(rtst) );
    if( g_enable_database ) vce_tcpcontext_get_stat( g_dbctx, &dbst );
    if( g_enable_realtime ) vce_tcpcontext_get_stat( g_rtctx, &rtst );
    return dbst.current_conn + rtst.current_conn;
}
bool checkDataTopDir( const char *dirname ) {
    Format f( "%s/00/00/_startup_test", dirname );
    char data[4] = "abc";
    if( writeFile(f.buf, data, sizeof(data), true ) == false ) {
        print("checkDataTopDir: can't write data in '%s'", f.buf );
        return false;
    }
    return true;
}
void printUsage() {
    print("Usage:");
    print("ssv realtime [OPTIONS]" );
    print("ssv database [OPTIONS]" );
    print("ssv realtime database [OPTIONS]" );
    print("Options:");
    print("--dump-sp : dump shared projects with interval" );
    print("--dump-p : dump projects with interval");
    print("--debug-protocol : abort on protocol parser error (for special debug case, dont use in production)");
    print("--maxcon=NUMBER : set max number. Absolute max is 200. Requires huge memory if maxcon gets larger." );
    print("--emulate-slow-disk=NUMBER : Enable slow disk emulation by milliseconds (sleep after each disk access) " );
    print("--channel_max=NUMBER : set max concurrent number of channel members.");
    print("--tcp_timeout=SECONDS : set TCP timeout for database and realtime connections" );
    print("--enable-fsync : Use fsync() when writing a static file (not affect on Redis storage)" );
    print("--redis-addr HOSTNAME : Address of the redis server.  Default is localhost" );
}

int main( int argc, char **argv ) {

    for(int i=0;i<argc;i++) {
        if( strcmp( argv[i], "--dump-sp" ) == 0 ) g_dump_shared_projects = true;
        if( strcmp( argv[i], "--dump-p") == 0 ) g_dump_projects = true;
        if( strcmp( argv[i], "--debug-protocol") == 0 ) g_enable_abort_on_parser_error = true;
        if( strncmp( argv[i], "--maxcon=", strlen("--maxcon=") ) == 0 ) {
            g_maxcon = atoi( argv[i] + strlen("--maxcon=") );
            if(g_maxcon <= 0 ) {
                print("invalid maxcon: %d", g_maxcon );
                return 1;
            }
            if( g_maxcon > ABS_MAXCON ) {
                print("too many max connection specified:%d Absolute max is %d.", g_maxcon, ABS_MAXCON );
                return 1;
            }
        }
        if( strncmp( argv[i], "--emulate-slow-disk=", strlen("--emulate-slow-disk=" ) ) == 0 ) {
            g_emulate_slow_disk_ms = atoi( argv[i] + strlen("--emulate-slow-disk=" ) );
        }
        if( strncmp( argv[i], "--channel_max=", strlen( "--channel_max=" ) ) == 0 ) {
            g_channel_maxcon = atoi( argv[i] + strlen( "--channel_max=" ) );
        }
        if( strncmp( argv[i], "--tcp_timeout=", strlen( "--tcp_timeout=" ) ) == 0 ) {
            g_tcp_timeout = atoi( argv[i] + strlen( "--tcp_timeout=" ) );
        }
        if( strcmp( argv[i], "realtime" ) == 0 ) g_enable_realtime = true;
        if( strcmp( argv[i], "database" ) == 0 ) g_enable_database = true;
        if( strcmp( argv[i], "--enable-fsync" ) == 0 ) g_enable_fsync = true;
        if( strcmp( argv[i], "--redis-addr" ) == 0 ) strncpy(g_redis_addr, argv[++i], sizeof(g_redis_addr));
    }
    if( g_enable_abort_on_parser_error ) {
        print("Enabled asserting on protocol error" );
    }
    if( g_enable_realtime == false && g_enable_database == false ) {
        printUsage();
        return 1;
    }
    
    //
    vce_initialize();
    vce_set_verbose_mode(0);
    vce_set_heartbeat_wait_flag(1);
    
    if( g_enable_database ) {
        if(!checkDataTopDir( g_topdir )) {
            print("Data directory not found: '%s'. Please make correct directories, use datadir/mkdir.rb.", g_topdir );
            return 1;
        }
        g_dbctx = vce_tcpcontext_create( 1, // server
                                         NULL, DBPORT, // addr, port
                                         g_maxcon, // maxcon
                                         1*1024*1024, 2*1024*1024, // recv buffer size, send buffer size
                                         g_tcp_timeout, // timeout
                                         0, // nonblock_connect
                                         0, // nodelay
                                         sizeof(ConnectionState) // statebuf_size
                                         );
        if(!g_dbctx) {
            print( "tcpcontext_create for db: %s", STRERR );
            return 1;
        }
        vce_tcpcontext_set_conn_call_parser_per_heartbeat( g_dbctx, 1000 );
        vce_tcpcontext_set_conn_parser( g_dbctx, vce_protocol_parser_bin32, ssproto_sv_pcallback );
        vce_tcpcontext_set_conn_closewatcher( g_dbctx, conn_closewatcher );
        vce_tcpcontext_set_conn_acceptwatcher( g_dbctx, conn_acceptwatcher );


        // setup redis
        struct timeval timeout = { 1,500000 };
        g_redis = redisConnectWithTimeout( g_redis_addr, 6379, timeout );
        if(g_redis==NULL||g_redis->err) {
            if(g_redis) {
                print("Redis connection error: %s\n", g_redis->errstr);
                redisFree(g_redis);
            } else {
                print("Redis connection error: can't allocate redis context\n");
            }
            return 1;
        }
        // test redis
        {
            redisReply *reply = (redisReply*)redisCommand( g_redis,"PING");
            if( strcmp( reply->str, "PONG" ) != 0 ) {
                print( "Redis PING failed\n" );
                return 1;
            } else {
                print( "Redis PING OK\n" );
            }
            freeReplyObject(reply);
        }
        
        loadAllNecessaryFiles();
    }

    if( g_enable_realtime ) { 
        g_rtctx = vce_tcpcontext_create( 1, // server
                                         NULL, RTPORT,
                                         g_maxcon,
                                         256*1024, 1024*1024,  // recv buffer size, send buffer size
                                         g_tcp_timeout,
                                         0,
                                         1, // nodelay
                                         sizeof(ConnectionState)
                                         );
        if(!g_rtctx) {
            print("tcpcontext_create for rt: %s", STRERR );
            return 1;
        }
        vce_tcpcontext_set_conn_call_parser_per_heartbeat( g_rtctx, 1000 );
        vce_tcpcontext_set_conn_parser( g_rtctx, vce_protocol_parser_bin32, ssproto_sv_pcallback );
        vce_tcpcontext_set_conn_closewatcher( g_rtctx, conn_closewatcher );
        vce_tcpcontext_set_conn_acceptwatcher( g_rtctx, conn_acceptwatcher );
    }

    //
    unsigned int majv, minv;
    majv = ssproto_sv_get_version( &minv );
    print("start loop. DB:%d RT:%d DBport:%d RTport:%d version:%d.%d maxcon:%d channel_max:%d slow-disk:%d fsync:%d",
          g_enable_database, g_enable_realtime, DBPORT, RTPORT, majv, minv,
          g_maxcon, g_channel_maxcon, g_emulate_slow_disk_ms, g_enable_fsync );

    while(1) {
        double nt = now();
        
        vce_heartbeat();
        g_loopcnt++;
        if((g_loopcnt%1000)==0) {
            prt( "." );

            static double last_dot_at = 0;
            int curcon = getCurrentConnNum();

            // Slow loop warn. It can cause too much server latency
            if( curcon > 5 ) {                 
                double dt_per_dot = nt - last_dot_at;
                if( dt_per_dot > 2.0f && last_dot_at > 0 ) {
                    print("server loop slowdown: %f sec", dt_per_dot);
                }
            }
            last_dot_at = nt;
        }

        if( g_enable_database ) { 
            static double last_pollall_at = 0;
            if( nt > last_pollall_at + 2 ) {
                last_pollall_at = nt;
                prt("$");
                pollAllProject();
                pollAllImageStore();
                pollAllLockProject();            
            }
        }

        if( g_enable_realtime ) { 
            static double last_pollgridlock_at = 0;
            if( nt > last_pollgridlock_at + 0.01 ) { // 0.01 * 100 project = 1 second
                last_pollgridlock_at = nt;
                pollProgressLockGrids();
            }
        }
        
        static double last_stat_print = 0;        
        if( nt > last_stat_print + 30 ) {
            printStat();
            last_stat_print = nt;
        }
    }
    return 0;
}

#define CHECK_REALTIME(nm) if(g_enable_realtime==false) { print("Warning: realtime service is not enabled. (%s)",nm ); return 0; }
#define CHECK_DATABASE(nm) if(g_enable_database==false) { print("Warning: database service is not enabled. (%s)",nm ); return 0; }

int ssproto_conn_serial_recv( conn_t c ) {
    print("ssproto_conn_serial_recv. ret:%d", c.serial );
    return ssproto_conn_serial_result_send( c, c.serial );
}
int ssproto_ping_recv( conn_t c, long long t_usec, int cmd ) {
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( c, NULL );
    cs->last_ping_at = now();
    return ssproto_pong_send( c, t_usec, cmd );
}
int ssproto_version_recv( conn_t _c, int maj, int min ) {
    print("ssproto_check_version_recv: maj,min:%d,%d",maj,min);
    unsigned int majv, minv;
    majv = ssproto_sv_get_version( &minv );
    if( (unsigned int)maj != majv || (unsigned int)min != minv ) {
        print("** Version differ! MAJOR: expect:%d received:%d MINOR: expect:%d received:%d", majv, maj, minv, min );
        if( (unsigned int)maj != majv ) {
            print("** Major version differ.closing");

        }
    } else {
        print("version correct for conn:%d", _c.serial);
    }
    return 0;
}

// ID
int ssproto_generate_id_32_recv( conn_t _c, int query_id, int num ) {
    static int id_gen = 1;
    ssproto_generate_id_32_result_send( _c, query_id, id_gen, num );
    id_gen += num;
    print("ssproto_generate_id_32_recv: id_gen is now %d", id_gen );
    return 0;
}

// File
bool validatePath( const char *path ) {
    for(int i=0;;i++) {
        char ch = path[i];
        if(ch=='\0')break;
        bool ok = ( isalpha(ch) || isdigit(ch) || (ch=='-') || (ch=='_') );  // a-zA-Z0-9_-
        if(!ok) return false;
    }
    return true;
}
int makeFullPath( char *out, size_t outlen, const char *filename ) {
    if( strlen(filename) >= 128-1 ) return SSPROTO_E_FILE_NAME_TOO_LONG;    
    if( validatePath(filename) == false ) return SSPROTO_E_FILE_NAME_INVALID;
    
    unsigned int h = hash_pjw(filename);
    snprintf( out, outlen, "%s/%02x/%02x/%s", g_topdir, h%0xff, (h/256)%0xff, filename );
    return SSPROTO_OK;
}
void emulateSlowDisk() {
    if( g_emulate_slow_disk_ms > 0 ) {
#ifndef WIN32
		usleep(g_emulate_slow_disk_ms * 1000);
#else
		print("emulateSlowDisk: high resolution sleep on windows is not implemented yet");
#endif
	}
}
int ssproto_put_file_recv( conn_t _c, int query_id, const char *filename, const char *data, int data_len ) {
    CHECK_DATABASE("put_file");
    char fullpath[1024];
    int err = makeFullPath( fullpath, sizeof(fullpath), filename );
    bool ret = writeFile( fullpath, data, data_len, g_enable_fsync );
    if(ret==false) err = SSPROTO_E_FILE_ACCESS;
    emulateSlowDisk();
    //        print("ssproto_put_file_recv: fullpath: '%s' err:%d data_len:%d", fullpath, err, data_len );
    //    prt("[putfile %s]", fullpath);
    ssproto_put_file_result_send( _c, query_id, err, filename );
    return 0;
}
int ssproto_get_file_recv( conn_t _c, int query_id, const char *filename ) {
    CHECK_DATABASE("get_file");    
    char fullpath[1024];
    int err = makeFullPath( fullpath, sizeof(fullpath), filename );
    static char buf[SSPROTO_FILE_SIZE_MAX];
    size_t sz=0;
    if(err==0) {
        sz = sizeof(buf);
        bool ret = readFile( fullpath, buf, &sz );
        if(ret==false) {
            err = SSPROTO_E_FILE_ACCESS;
            sz = 0;
        }
    }
    prt("f");
    //    print("ssproto_get_file_recv: fullpath: '%s' err:%d read len:%d", fullpath, err, sz );        
    emulateSlowDisk();
    ssproto_get_file_result_send( _c, query_id, err, filename, buf, sz );
    return 0;
}
int ssproto_check_file_recv( conn_t _c, int query_id, const char *filename ) {
    CHECK_DATABASE("check_file");    
    char fullpath[1024];
    int res = makeFullPath( fullpath, sizeof(fullpath), filename );
    if( res == 0 ) { 
        char buf[1];
        size_t sz = 1;
        bool ret = readFile( fullpath, buf, &sz );
        if(ret) {
            res = SSPROTO_FILE_EXIST;
        } else {
            // No file found, but not an error.
            res = SSPROTO_FILE_NOT_EXIST;
        }
    }
    emulateSlowDisk();
    print("ssproto_check_file_recv: fullpath: '%s' res:%d", fullpath, res );
    ssproto_check_file_result_send( _c, query_id, res, filename );
    return 0;    
}


void convertRedisElementsToStringArray( redisReply *reply, char **strary ) {
    static char work[SSPROTO_KVS_ARRAYLEN_MAX][SSPROTO_KVS_ELEMENT_MAX];
    int n = reply->elements;
    if( n > SSPROTO_KVS_ARRAYLEN_MAX ) n = SSPROTO_KVS_ARRAYLEN_MAX;
    for(int i=0;i<n; i++ ){
        switch( reply->element[i]->type ) {
        case REDIS_REPLY_STRING:
        case REDIS_REPLY_ERROR:                
            strary[i] = reply->element[i]->str;
            break;
        case REDIS_REPLY_INTEGER:
            snprintf( work[i], sizeof(work[i]), "%lld", reply->element[i]->integer );
            strary[i] = & work[i][0];
            break;
        case REDIS_REPLY_NIL:
            // TODO: Now VCE's gen can only handle string array. returning special string.
            {
                static char nilstr[] = "(nil)";
                strary[i] = nilstr;
            }
            break;
        }
        //        print("  [%d] : '%s'", i, strary[i] );
    }
}

int ssproto_kvs_command_str_recv( conn_t _c, int query_id, const char *command ) {
    CHECK_DATABASE("kvs_command_str");    
    //    print("ssproto_kvs_command_str_recv: qid:%d cmd:'%s'", query_id, command );
    prt("R");    
    redisReply *reply = (redisReply*) redisCommand( g_redis, command ); // No security! Use only inside data center servers.
    switch( reply->type) {
    case REDIS_REPLY_STRING:
        //        print("redis returns string: '%s'", reply->str );
        ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_OK, SSPROTO_KVS_VALUE_STRING, & reply->str, 1 );
        break;
    case REDIS_REPLY_ARRAY:
        //        print("redis returns array with %d elements", reply->elements );
        char *strary[SSPROTO_KVS_ARRAYLEN_MAX];
        convertRedisElementsToStringArray( reply, strary );
        ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_OK, SSPROTO_KVS_VALUE_ARRAY, strary, reply->elements );
        break;
    case REDIS_REPLY_INTEGER:
        //        print("redis returns integer: %d", reply->integer );
        // Have to convert to string, because now gen can't manage multiple prototypes of same function.
        {
            char s[128];
            snprintf(s,sizeof(s), "%lld", reply->integer);
            char *ptr = s;
            ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_OK, SSPROTO_KVS_VALUE_INTEGER, &ptr, 1 );
        }
        break;
    case REDIS_REPLY_NIL:
        //        print("redis returns nil" );
        ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_OK, SSPROTO_KVS_VALUE_NIL, NULL, 0 );
        break;
    case REDIS_REPLY_ERROR:
        //        print("redis returns error:'%s'", reply->str );
        ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, SSPROTO_KVS_VALUE_ERROR, & reply->str, 1 );
        break;
    case REDIS_REPLY_STATUS:
        //        print("redis returns status:'%s'", reply->str );
        ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, SSPROTO_KVS_VALUE_STRING, & reply->str, 1 );
        break;        
    default:
        print("ssproto_kvs_command_str_recv: redis returns unknown value type:%d cmd:'%s'", reply->type, command );
        {
            char emsg[128];
            snprintf(emsg,sizeof(emsg), "unknown redis reply type: %d", reply->type );
            char *ptr = emsg;
            ssproto_kvs_command_str_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, SSPROTO_KVS_VALUE_ERROR, &ptr,1 );
        }
        break;
    }
    freeReplyObject(reply);
    return 0;
}
int ssproto_kvs_command_str_oneway_recv( conn_t _c, const char *command ) {
    CHECK_DATABASE( "kvs_command_str_oneway");    
    redisCommand( g_redis, command ); // No security! Use only inside data center servers.
    return 0;
}

int ssproto_kvs_save_bin_recv( conn_t _c, int query_id, const char *key, const char *field, const char *data, int data_len ) {
    CHECK_DATABASE( "kvs_save_bin");    
    //    print( "ssproto_kvs_save_bin_recv: qid:%d key:'%s' fied:'%s' datalen:%d", query_id, key, field, data_len );
    prt("R");
    redisReply *reply;
    reply = (redisReply*)redisCommand( g_redis, "HSET %s %s %b", key, field, data, (size_t)data_len );
    int retcode = SSPROTO_OK;
    if( reply->type == REDIS_REPLY_ERROR ) {
        print("redis error on '%s' emsg:'%s'", key, reply->str );
        retcode = SSPROTO_E_KVS_COMMAND;
    } else {
        //        print("redis set ok on '%s'", key );
    }
    ssproto_kvs_save_bin_result_send( _c, query_id, retcode, reply->type, key, field );
    freeReplyObject(reply);    
    return 0;
}
int ssproto_kvs_load_bin_recv( conn_t _c, int query_id, const char *key, const char *field ) {
    CHECK_DATABASE( "kvs_load_bin");    
    //    print( "ssproto_kvs_load_bin_recv: qid:%d key:'%s' field:'%s'",query_id, key, field );
    
    redisReply *reply;
    reply = (redisReply*) redisCommand( g_redis, "HGET %s %s", key, field );

    if( reply->type == REDIS_REPLY_ERROR ) {
        print("redis error on '%s':'%s' emsg:'%s'", key, field, reply->str );
        ssproto_kvs_load_bin_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, 0, key, field, reply->str, reply->len );
    } else if( reply->type == REDIS_REPLY_NIL ){
        // No data stored in redis.
        print("redis no data on '%s' '%s'", key, field );
        ssproto_kvs_load_bin_result_send( _c, query_id, SSPROTO_OK, 0, key, field, NULL,0 );
    } else {
        // Data found!
        //        print("redis get ok on '%s':'%s' reply type:%d", key, field, reply->type );
        prt("R");
        ssproto_kvs_load_bin_result_send( _c, query_id, SSPROTO_OK, 1, key, field, reply->str, reply->len );
    }
    freeReplyObject(reply);            
    return 0;
}

/////////
// presence
Project g_projects[ONLINE_PROJECT_MAX];


void Project::clear() {
    for(int i=0;i<elementof(online_players);i++){
        online_players[i].clear();
    }
}
bool Project::updateUser( int user_id ) {
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id == user_id ) { // found a user
            online_players[i].last_active_at = time(NULL);
            return true; 
        }
    }
    // User not found
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id == 0 ) {
            online_players[i].user_id = user_id;
            online_players[i].last_active_at = time(NULL);
            return true;
        }
    }
    return false; // full
}
bool Project::deleteUser( int user_id ) {
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id == user_id ) {
            online_players[i].clear();
            return true;
        }
    }
    return false;
}

Project *findProject( int id ) {
    for(int i=0;i<elementof(g_projects);i++) {
        if( g_projects[i].id == id ) {
            return & g_projects[i];
        }
    }
    return NULL;
}
Project *allocateProject( int id ) {
    for(int i=0;i<elementof(g_projects);i++) {
        if( g_projects[i].id == 0 ) {
            g_projects[i].id = id;
            g_projects[i].clear();
            prt("[newproj id:%d]", id );
            return & g_projects[i];
        }
    }
    print("allocateProject: full! max:%d", elementof(g_projects) );
    return NULL;
}
int countProject() {
    int n=0;
    for(int i=0;i<elementof(g_projects);i++) {
        if( g_projects[i].id ) n++;
    }
    return n;    
}
void Project::listOnlineUsers( int *out, int *outn ) {
    int outind=0;
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id != 0 ) {
            //           print("listOnlineUsers: [%d]:%d", outind, online_players[i].user_id );
            out[outind] = online_players[i].user_id;
            outind++;
            if( outind >= *outn ) {
                break;
            }
        }
    }
    *outn = outind;
}
// TODO: Use cache for more performance.
int Project::countOnlineUsers() {
    int n=0;
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id != 0 ) n++;
    }
    return n;
}

void Project::poll(time_t nowt) {
    for(int i=0;i<elementof(online_players);i++) {
        if( online_players[i].user_id != 0 && online_players[i].isTimeout(nowt) ) {
            print("Project::poll: timeout user_id:%d", online_players[i].user_id );
            online_players[i].clear();
        }
    }
}

void pollAllProject() {
    time_t nowt = time(NULL);
    for(int i=0;i<elementof(g_projects);i++) {
        if( g_projects[i].id == 0 ) continue;
        g_projects[i].poll(nowt);
    }
}

int ssproto_update_presence_recv( conn_t _c, int project_id, int user_id ) {
    CHECK_DATABASE( "update_presence");    
    //    print("ssproto_update_presence_recv: pj:%d uid:%d", project_id, user_id );
    prt("u");
    Project *pj = findProject(project_id);
    if(!pj) pj = allocateProject( project_id );
    if(!pj) return 0;
    pj->updateUser(user_id);
    return 0;
}
int ssproto_delete_presence_recv( conn_t _c, int project_id, int user_id ) {
    CHECK_DATABASE( "delete_presence");        
    //    print("ssproto_delete_presence_recv: pj:%d uid:%d", project_id, user_id );
    Project *pj = findProject( project_id );
    if(!pj) return 0;
    pj->deleteUser( user_id );
    return 0;
}
int ssproto_list_presence_recv( conn_t _c, int project_id ) {
    CHECK_DATABASE( "list_presence");        
    //    print( "ssproto_get_presence_recv: pj:%d", project_id );
    Project *pj = findProject( project_id );
    if(!pj) return 0;
    
    int out[SSPROTO_PRESENCE_PER_PROJECT_MAX];
    int sz = elementof(out);

    pj->listOnlineUsers(out,&sz);

    //    print("ssproto_get_presence_result: sz:%d",sz);
    ssproto_list_presence_result_send( _c, project_id, out, sz );
    
    return 0;
}

int ssproto_count_presence_recv( conn_t _c, int project_id ){
    CHECK_DATABASE("count_presence");
    //    print("ssproto_count_presence_recv: pj:%d",project_id );
    Project *pj = findProject( project_id );
    if(!pj) {
        //        print("ssproto_count_presence_recv: project id %d not found", project_id );
        ssproto_count_presence_result_send( _c, project_id, 0 );        
        return 0;
    }
    int n = pj->countOnlineUsers();
    prt("[pj:%d online:%d]", project_id, n );
    ssproto_count_presence_result_send( _c, project_id, n );
    return 0;
}

//////////////////
// Redis list. (Mainly for logging)
int ssproto_kvs_push_to_list_recv( conn_t _c, int query_id, const char *key,  const char *s, int trim ) {
    CHECK_DATABASE( "kvs_push_to_list");    
    //    print("ssproto_kvs_push_to_list_recv: k:'%s' s:'%s', trim:%d", key, s, trim );
    prt("R");
    redisReply *reply  = (redisReply*) redisCommand( g_redis, "LPUSH %s %s", key, s );

    switch( reply->type ) {
    case REDIS_REPLY_INTEGER:
        // Have a correct number of elements in a list
        print("ssproto_kvs_push_to_list_recv: redisCommand returned integer:%d", reply->integer );
        ssproto_kvs_push_to_list_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, key, reply->integer );
        break;
    case REDIS_REPLY_ERROR:
    default:
        print("ssproto_kvs_push_to_list_recv: redisCommand error");
        ssproto_kvs_push_to_list_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, key, 0 );
        break;
    }
    freeReplyObject(reply);        
    return 0;   
}
int ssproto_kvs_get_list_range_recv( conn_t _c, int query_id, const char *key, int start_ind, int end_ind ) {
    CHECK_DATABASE("kvs_get_list_range");    
    //    print("ssproto_kvs_get_list_range_recv: '%s' %d-%d", key,  start_ind, end_ind );
    prt("R");
    redisReply *reply = (redisReply*) redisCommand( g_redis, "LRANGE %s %d %d", key, start_ind, end_ind );
    switch(reply->type) {
    case REDIS_REPLY_ARRAY:
        {
            
            char *sary[SSPROTO_KVS_ELEMENT_MAX];
            convertRedisElementsToStringArray( reply, sary );
            ssproto_kvs_get_list_range_result_send( _c, query_id, SSPROTO_OK, start_ind, end_ind, key, sary, reply->elements );
        }
        break;
    default:
        ssproto_kvs_get_list_range_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, start_ind, end_ind, key, NULL, 0 );
        break;
    }
    freeReplyObject(reply);        
    return 0;       
}
/////////////////
// Store JSON array in Redis Hash.
// [ "hoge", "fuga", "piyo" ]
int ssproto_kvs_append_string_array_recv( conn_t _c, int query_id, const char *key, const char *field, const char *s, int trim ) {
    CHECK_DATABASE( "kvs_append_sring_array");    
    //    print("ssproto_kvs_append_string_array_recv '%s':'%s' s:'%s' trim:%d", key, field,s, trim );
    prt("R");
    redisReply *reply = (redisReply*) redisCommand( g_redis, "HGET %s %s", key, field );
    switch(reply->type) {
    case REDIS_REPLY_STRING:
    case REDIS_REPLY_NIL:
        {
            picojson::value v;
            picojson::array ary;
            if( reply->type == REDIS_REPLY_STRING ) {
                std::string err;
                picojson::parse( v, reply->str, reply->str + reply->len, &err );
                if(!err.empty() || v.is<picojson::array>() == false ) {
                    print("parse error or not an array: '%s'", reply->str );
                    v = picojson::value();
                    ary = picojson::array();
                } else {
                    ary = v.get<picojson::array>();
                }
                
            }
            ary.push_back( picojson::value(s) );
            picojson::value modified_v;
            int n = ary.size();
            if( trim == 0 || n <= trim ) {
                modified_v = picojson::value(ary);
            } else { // n > trim
                // start_i is 2 if input is [ a, b, c, d, e ] and n=5, trim=3
                int start_i =  n - trim;
                picojson::array shorter;
                for(int i=start_i;i<n;i++) {
                    shorter.push_back( ary[i] );
                }
                modified_v = picojson::value(shorter);
            }

            std::string serialized = modified_v.serialize();
            redisReply *savereply = (redisReply*) redisCommand( g_redis, "HSET %s %s %s", key, field, serialized.c_str());
            if( savereply->type == REDIS_REPLY_ERROR ) {
                ssproto_kvs_append_string_array_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, key, field );
            } else {
                print("saved serialized json: '%s'", serialized.c_str());
                ssproto_kvs_append_string_array_result_send( _c, query_id, SSPROTO_OK, key, field );
            }
        }
        break;
    case REDIS_REPLY_ERROR:
    default:
        ssproto_kvs_append_string_array_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, key, field );        
        break;
    }
    freeReplyObject(reply);        
    return 0;
}
int ssproto_kvs_get_string_array_recv( conn_t _c, int query_id, const char *key, const char *field ) {
    CHECK_DATABASE( "kvs_get_string_array");    
    //    print("ssproto_kvs_get_string_array_recv: '%s':'%s'", key, field );
    prt("R");
    redisReply *reply = (redisReply*) redisCommand( g_redis, "HGET %s %s", key, field );
    switch(reply->type) {
    case REDIS_REPLY_STRING:
        {
            picojson::value v;
            std::string err;
            picojson::parse( v, reply->str, reply->str + reply->len, &err );
            picojson::array ary;            
            if( !err.empty() || v.is<picojson::array>() == false ) {
                print("parse error or not an array: '%s'", reply->str );
                v = picojson::value();
                ary = picojson::array();
            } else {
                ary = v.get<picojson::array>();
            }
            static char work[SSPROTO_KVS_ARRAYLEN_MAX][SSPROTO_KVS_ELEMENT_MAX];
            static char *workptr[SSPROTO_KVS_ARRAYLEN_MAX];
            
            int n = ary.size();
            int outn = MIN(n, SSPROTO_KVS_ARRAYLEN_MAX);
            for(int i=0;i<outn;i++) {
                std::string s = ary[i].get<std::string>();
                strncpy( work[i], s.c_str(), sizeof(work[i]) );
                workptr[i] = work[i];
            }
            //            print("sending ssproto_kvs_get_string_array_result_send: outn:%d", outn );
            ssproto_kvs_get_string_array_result_send( _c, query_id, SSPROTO_OK, key, field, workptr, outn );
        }
        break;
    case REDIS_REPLY_NIL:
        ssproto_kvs_get_string_array_result_send( _c, query_id, SSPROTO_OK, key, field, NULL, 0 );
        break;
    default:
        ssproto_kvs_get_string_array_result_send( _c, query_id, SSPROTO_E_KVS_COMMAND, key, field, NULL, 0 );
        break;
    }
    freeReplyObject(reply);    
    return 0;
}

///////////////////
// Broadcasting
int ssproto_broadcast_recv( conn_t _c, int type_id, const char *data, int data_len ) {
    CHECK_REALTIME( "broadcast" );
    print("ssproto_broadcast_recv: t:%d", type_id);
    conn_t conns[1024];
    int n = vce_tcpcontext_get_all_connection( g_rtctx, conns, elementof(conns) );
    for(int i=0;i<n;i++) {
        print("bc: to %d", i);
        if( vce_conn_is_equal( _c, conns[i] ) == false ) {
            ssproto_broadcast_notify_send( conns[i], _c.serial, type_id, data, data_len );
        }
    }
    return 0;    
}

Channel *findChannel(int id) {
    for(int i=0;i<elementof(g_channels);i++) {
        if( g_channels[i].id == id ) {
            return & g_channels[i];
        }
    }
    return NULL;
}
Channel *allocateChannel(int id) {
    for(int i=0;i<elementof(g_channels);i++) {
        if( g_channels[i].id == 0 ) {
            g_channels[i].id = id;
            g_channels[i].num_members = 0;
            return & g_channels[i];
        }
    }
    return NULL;
}
bool checkCSChannel( ConnectionState *cs) {
    Channel *ch = cs->cur_channel_cache;
    if( (!ch) || ( ch->id != cs->cur_channel_id ) ) {
        cs->cur_channel_id = 0;
        cs->cur_channel_cache = NULL;
        return false;
    } else {
        return true;
    }
}

int ssproto_get_channel_member_count_recv( conn_t _c, int channel_id ) {
    CHECK_REALTIME( "get_channel_member_count" );
    print("ssproto_get_channel_member_count_recv. chid:%d", channel_id );
    int ret_num = 0;
    Channel *ch = findChannel( channel_id );
    if(ch) ret_num = ch->getMemberCount();
    ssproto_get_channel_member_count_result_send( _c, channel_id, g_channel_maxcon, ret_num );
    return 0;
}

int ssproto_join_channel_recv( conn_t _c, int channel_id ) {
    CHECK_REALTIME( "join_channel");    
    //    print("ssproto_join_channel_recv: chid:%d",channel_id);
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( _c, NULL );

    Channel *ch;
    if( checkCSChannel(cs) ) {
        cs->cur_channel_cache->leave(_c);
    }

    //
    
    ch = findChannel( channel_id );
    if(!ch) ch = allocateChannel(channel_id);
    if(!ch) {
        print("ssproto_join_channel_recv: no more channel! id:%d", channel_id );
        ssproto_join_channel_result_send( _c, channel_id, SSPROTO_E_CHANNEL_FULL );
        return 0;
    }
    if( ch->getMemberCount() > g_channel_maxcon ) {
        print("ssproto_join_channel_recv: reached channel_max. id:%d" , channel_id );
        ssproto_join_channel_result_send( _c, channel_id, SSPROTO_E_CHANNEL_FULL );
        return 0;
    }
    bool res = ch->join( _c );
    if(res) {
        ssproto_join_channel_result_send( _c, channel_id, SSPROTO_OK );
        cs->cur_channel_cache = ch;
        cs->cur_channel_id = channel_id;
        prt("[join chid:%d]", channel_id );
    } else {
        print("ssproto_join_channel_recv: channel full! chid:%d", channel_id );
        ssproto_join_channel_result_send( _c, channel_id, SSPROTO_E_CHANNEL_FULL );
    }

    return 0;
}

int ssproto_leave_channel_recv( conn_t _c ) {
    CHECK_REALTIME( "leave_channel");    
    print("ssproto_leave_channel_recv. serial:%d",_c.serial );
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( _c, NULL );
    Channel *ch = cs->cur_channel_cache;
    if( checkCSChannel(cs) ) {
        print("leavaing channel %d", cs->cur_channel_id );
        ch->leave(_c);
    }
    return 0;
}


int ssproto_channelcast_recv( conn_t _c, int channel_id, int type_id, const char *data, int data_len ) {
    CHECK_REALTIME( "channelcast");
    //    print("ssproto_channelcast_recv: ch:%d type:%d data_len:%d", channel_id, type_id, data_len );
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( _c, NULL );
    if( checkCSChannel(cs) ) {
        Channel *ch = cs->cur_channel_cache;
        for(int i=0;i<ch->num_members;i++) {
            if( vce_conn_is_equal( ch->members[i].co, _c ) == false ) {
                ssproto_channelcast_notify_send( ch->members[i].co, channel_id, _c.serial, type_id, data, data_len );
            }
        }        
    }

    return 0;
}

int ssproto_nearcast_recv( conn_t _c, int x, int y, int range, int type_id, const char *data, int data_len ) {
    CHECK_REALTIME("nearcast");    
    //    static int cnt=0;
    //    if( (++cnt%1000)==0)
    //    print("ssproto_nearcast_recv x:%d y:%d r:%d t:%d len:%d",x,y,range,type_id,data_len);
    //    prt("n%d ", _c.serial );
    
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( _c, NULL );
    if(checkCSChannel(cs)) {
        Channel *ch = cs->cur_channel_cache;
        for(int i=0;i<ch->num_members;i++) {
            ChannelMember *m = & ch->members[i];
            if( m->x >= x - range && m->x <= x + range &&
                m->y >= y - range && m->y <= y + range &&
                vce_conn_is_equal( _c, m->co ) == false  ) {
                ssproto_nearcast_notify_send( m->co, ch->id, _c.serial, x,y, range, type_id, data, data_len );
            }
        }
    }
    return 0;
}

int ssproto_update_nearcast_position_recv( conn_t _c, int x, int y ) {
    CHECK_REALTIME("update_nearcast_position");
    //    print("ssproto_update_nearcast_position_recv: x:%d y:%d ", x,y );
    ConnectionState *cs = (ConnectionState*) vce_conn_get_state_buffer( _c, NULL );
    if(checkCSChannel(cs)) {
        Channel *ch = cs->cur_channel_cache;
        ch->updatePosition( _c, x, y );
    }
    
    return 0;
}


///////////////////

// Lock

LockGrid *findLockGrid( int id ) {
    for(int i=0;i<elementof(g_lockgrids);i++){
        if( g_lockgrids[i].id == id ) {
            return & g_lockgrids[i];
        }
    }
    return NULL;
}
LockGrid *allocateLockGrid( int id ) {
    for(int i=0;i<elementof(g_lockgrids);i++){
        if( g_lockgrids[i].id == 0 ) {
            g_lockgrids[i].clear();  
            g_lockgrids[i].id = id;
            prt("[newlockgrid id:%d]", id );
            return & g_lockgrids[i];
        }
    }
    return NULL;
}
void pollProgressLockGrids() {
    static int cnt=0;
    cnt++;
    int ind = cnt % elementof( g_lockgrids );
    LockGrid *lg = & g_lockgrids[ind];
    if( lg->id > 0 && lg->countLock() > 0 ) {
        //        print("has lock. lk:%d id:%d", lg->countLock(), lg->id);
        lg->pollLockTimeout();
        if( lg->countLock() == 0 ) {
            lg->clear();
        }
    }
}

// grid_id is designed to be used as project id
int ssproto_lock_grid_recv( conn_t _c, int grid_id, int x, int y ) {
    CHECK_REALTIME("lock_grid");    
    //        print("ssproto_lock_grid_recv: g:%d, xy:%d,%d serial:%d", grid_id, x,y, _c.serial );
    LockGrid *lg = findLockGrid( grid_id );
    if(!lg) {
        lg = allocateLockGrid( grid_id );
        if(lg==NULL) {
            print("ssproto_lock_grid_recv: g_lockgrid is full!!");
            ssproto_lock_grid_result_send( _c, grid_id, x,y, SSPROTO_E_CANT_LOCK );
            return 0;
        }
    }

    bool res = lg->lock( x,y, _c.serial );
    ssproto_lock_grid_result_send( _c, grid_id, x,y, res ? SSPROTO_OK : SSPROTO_E_CANT_LOCK );
    return 0;
}
int ssproto_unlock_grid_recv( conn_t _c, int grid_id, int x, int y ) {
    CHECK_REALTIME("unlock_grid");    
    //    print("ssproto_unlock_grid_recv: g:%d x,y:%d serial:%d",grid_id,x,y,_c.serial );
    LockGrid *lg = findLockGrid( grid_id );
    if(lg) {
        bool res = lg->unlock( x,y, _c.serial );
        ssproto_unlock_grid_result_send( _c, grid_id, x,y, res ? SSPROTO_OK : SSPROTO_E_CANT_UNLOCK );
    } else { 
        ssproto_unlock_grid_result_send( _c, grid_id, x,y, SSPROTO_E_CANT_UNLOCK );
    }
    return 0;
}

int ssproto_lock_keep_grid_recv( conn_t _c, int grid_id, int x, int y ) {
    CHECK_REALTIME("lock_keep_grid");    
    //print("ssproto_lock_keep_grid_recv: g:%d xy:%d,%d",grid_id,x,y);
    LockGrid *lg = findLockGrid(grid_id);
    if(lg) {
        lg->keepLock( x,y, _c.serial );
    }
    return 0;
}

bool lockProject( int id, int cat, int by_conn_id ) {
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id == id && g_lockprojects[i].category == cat ) return false; // Can't get the same lock twice
    }
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id == 0 ) {
            g_lockprojects[i].id = id;
            g_lockprojects[i].category = cat;
            g_lockprojects[i].by_conn_id = by_conn_id;
            g_lockprojects[i].lock_at = time(NULL);
            return true;
        }
    }
    return false;
}
bool unlockProject( int id, int cat, unsigned int by_conn_id ) {
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id == id &&
            g_lockprojects[i].category == cat && 
            g_lockprojects[i].by_conn_id == by_conn_id ) {
            g_lockprojects[i].id = 0;
            return true;
        }
    }
    return false;
}
void lockKeepProject( int id, int cat, unsigned int by_conn_id ) {
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id == id &&
            g_lockprojects[i].category == cat && 
            g_lockprojects[i].by_conn_id == by_conn_id ) {
            g_lockprojects[i].lock_at = time(NULL);
            return;
        }
    }
}
void pollAllLockProject() {
    time_t nowt = time(NULL);
    for(int i=0;i<elementof(g_lockprojects);i++) {
        if( g_lockprojects[i].id != 0 &&
            g_lockprojects[i].lock_at < nowt - 5 ) {
            print("pollAllLockProject: project:%d cat:%d timeout.", g_lockprojects[i].id, g_lockprojects[i].category );
            g_lockprojects[i].id = 0;
        }
    }
}

int ssproto_lock_project_recv( conn_t _c, int project_id, int category ) {
    CHECK_REALTIME("lock_project");    
    bool res = lockProject( project_id, category, _c.serial );
    int ret = res ? SSPROTO_OK : SSPROTO_E_CANT_LOCK;
    //    print( "lockProject ret:%d for pj:%d cat:%d", ret, project_id , category );
    ssproto_lock_project_result_send( _c, project_id, category, ret );
    return 0;
}
int ssproto_unlock_project_recv( conn_t _c, int project_id, int category ) {
    CHECK_REALTIME("unlock_project");    
    bool res = unlockProject( project_id, category, _c.serial );
    int ret = res ? SSPROTO_OK : SSPROTO_E_CANT_UNLOCK;
    //    print( "unlockProject ret:%d for pj:%d cat:%d", ret, project_id, category  );    
    ssproto_unlock_project_result_send( _c, project_id, category, ret );    
    return 0;
}
int ssproto_lock_keep_project_recv( conn_t _c, int project_id, int category ) {
    CHECK_REALTIME("lock_keep_project");    
    //    print( "keepProject pjid:%d cat:%d", project_id, category );
    lockKeepProject( project_id, category, _c.serial );
    return 0;
}
int ssproto_clean_all_recv( conn_t _c ) {
    print("ssproto_clean_all_recv. serial:%d", _c.serial );
    cleanAll(_c);
    ssproto_clean_all_result_send( _c );
    return 0;
}
//////////////////
class Member {
public:
    int user_id;
    char nickname[16];
    int face_index;
    int hair_index;
    Member() : user_id(0), face_index(0), hair_index(0) { nickname[0] = '\0'; }
    Member( int uid, const char *nk, int f, int h ) : user_id(uid), face_index(f), hair_index(h) {
        strncpy( nickname, nk, sizeof(nickname) );
    }
};
class SharedProject {
public:
    int project_id;
    int owner_user_id;
    time_t shared_at;
    int member_uids[SSPROTO_SHARE_MAX];
    int members_num;
    bool published;
    SharedProject() : project_id(0), owner_user_id(0), shared_at(0), members_num(0), published(false) {
    }
    void setMembers( const int *with, int num ) {
        int to_copy = MIN( elementof(member_uids), num );
        for(int i=0;i<to_copy;i++) {
            member_uids[i] = with[i];
        }
        members_num = to_copy;
    }
    void dump() {
        print(" project_id:%d owner_user_id:%d shared_at:%u published:%d ", project_id, owner_user_id, (unsigned int)shared_at, published );
        for(int i=0;i<members_num;i++) {
            print("  member_uids[%d] : %d", i, member_uids[i] );
        }
    }
};

SharedProject g_sharedpjs[2048];

char g_sharedproj_filename[] = "_sharedprojects";
bool saveAllSharedProjects() {
    static char fullpath[1024];
    makeFullPath( fullpath, sizeof(fullpath), g_sharedproj_filename );
    double st = now();
    bool ret = writeFile(fullpath, (char*)g_sharedpjs, sizeof(g_sharedpjs), g_enable_fsync );
    double et = now();
    print("saveAllSharedProjects: time:%f result:%d", et-st,ret);
    return ret;
}
// Only once when starting server.
// Ignore data if data size differs. Size will be different when server program is updated.
// You have to clear the data if the size is not changed when updating server program.
bool loadAllSharedProjects() {
    static char fullpath[1024];
    makeFullPath( fullpath, sizeof(fullpath), g_sharedproj_filename );

    size_t sz = sizeof(g_sharedpjs);    
    char *buf = (char*) MALLOC( sz );
    assert(buf);
    
    double st = now();
    bool ret = readFile(fullpath, buf, &sz );
    double et = now();
    if(!ret) {
        print("loadAllSharedProjects: file '%s' not found.", fullpath );
    } else if( sz == sizeof(g_sharedpjs) ) {
        memcpy( (char*)g_sharedpjs, buf, sz );
        print("loadAllSharedProjects: loaded from '%s' time:%f", fullpath, et-st );
    } else {
        print("loadAllSharedProjects: size differ. expect:%u loaded:%u", sizeof(g_sharedpjs), sz );        
    }
    FREE(buf);

    
    return ret;
}

int countLockGridsActive() {
    int n=0;
    for(int i=0;i<elementof(g_lockgrids);i++) {
        if( g_lockgrids[i].id) n++;
    }
    return n;
}

int countSharedProject() {
    int n = 0;
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id ) n++;
    }
    return n;    
}
SharedProject *findSharedProject( int project_id ) {
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id == project_id ) {
            return & g_sharedpjs[i];
        }
    }
    return NULL;
}
SharedProject *findPublishedProject( int project_id ) {
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id == project_id && g_sharedpjs[i].published ) {
            return & g_sharedpjs[i];
        }
    }
    return NULL;
}

SharedProject *findFreeProject() {
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id == 0 ) { 
            return & g_sharedpjs[i];
        }
    }
    return NULL;
}
void freeProject( int pjid ) {
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id == pjid ) {
            g_sharedpjs[i].project_id = 0;
            g_sharedpjs[i].shared_at = 0;
            g_sharedpjs[i].owner_user_id = 0;
            g_sharedpjs[i].members_num = 0;
            return;
        }
    }
}
void unshareProject( int pjid ) {
    // keep published projects
    SharedProject *sp = findSharedProject(pjid);
    if(!sp) {
        print("unshareProject: project %d not found", pjid );
        return;
    }

    if(sp->members_num>0) {
        sp->members_num=0;
    }

    if( sp->published == false && sp->members_num == 0 ) {
        freeProject(pjid);
        print("unshareProject: project %d is any more public nor shared, freed.", pjid );
    }
}


// Reuse even if it is in use.
SharedProject *reuseOldestProject() {
    SharedProject *out = & g_sharedpjs[0];
    time_t oldest = g_sharedpjs[0].shared_at;
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].shared_at < oldest ) {
            oldest = g_sharedpjs[i].shared_at;
            out = & g_sharedpjs[i];
        }
    }
    out->project_id = 0;
    return out;
}

// Make a project public when with==NULL
void shareProject( int pjid, int uid, const int *with, int num ) {
    SharedProject *sp = findSharedProject(pjid );
    if(!sp) {
        sp = findFreeProject();
        if(!sp) {
            sp = reuseOldestProject();
        }
    }
    assert(sp);
    sp->shared_at = time(NULL);
    sp->owner_user_id = uid;
    sp->project_id = pjid;
    if(with) {
        // share to followers
        sp->setMembers( with, num );
    } else {
        // share to public
        sp->published = true;
    }
    saveAllSharedProjects(); // Now it takes only 1ms or so.
}

// TODO: sort
int getPublishedProjects( int *out_ids, int maxn ) {
    int cnt=0;
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id > 0 && g_sharedpjs[i].published ) {
            out_ids[cnt] = g_sharedpjs[i].project_id;
            cnt++;
            if(cnt==maxn)return cnt;
        }
    }
    return cnt;
}

// TODO: sort
int getSharedProjects( int *out_ids, int maxn, int user_id ) {
    int outnum=0;
    for(int i=0;i<elementof(g_sharedpjs);i++) {
        if( g_sharedpjs[i].project_id > 0 && g_sharedpjs[i].published == false ) {
            SharedProject *sp = & g_sharedpjs[i];
            bool to_add = false;
            if( sp->owner_user_id == user_id ) {
                to_add = true;
            } else {
                for(int j=0;j<sp->members_num;j++){
                    if( sp->member_uids[j] == user_id ) {
                        to_add = true;
                        break;
                    }
                }
            }
            if(to_add) {
                out_ids[outnum] = sp->project_id;
                outnum++;
                if( outnum == maxn ) return outnum;
                break;
            }
        }
    }
    return outnum;
}
// Returns true if the userid is able to join a project(pjid). Search only inside of shared projects.
bool checkSharedProjectJoinable( int pjid, int userid ) {
    SharedProject *sp = findSharedProject(pjid);
    if(!sp) { print("checkSharedProjectJoinable: pj %d not found", pjid ); return false; }
    if(sp->published) { print("checkSharedProjectJoinable: pj %d is published", pjid ); return true; }
    for(int i=0;i<sp->members_num;i++){
        if( sp->member_uids[i] == userid ) {
            print("checkSharedProjectJoinable: userid %d is found in pj %d members", userid, pjid );
            return true;
        }
    }
    print("checkSharedProjectJoinable: userid %d is not found in pj %d", userid, pjid );
    return false;
}

int ssproto_share_project_recv( conn_t _c, int user_id, int project_id, const int *with, int with_len ) {
    CHECK_DATABASE("share_project");    
    print("ssproto_share_project_recv: uid:%d pid:%d with_len:%d", user_id, project_id, with_len );
    for(int i=0;i<with_len;i++) {
        print("with: %d ", with[i] );
    }
    shareProject( project_id, user_id, with, with_len );
    ssproto_share_project_result_send( _c, project_id );
    return 0;
}



int ssproto_publish_project_recv( conn_t _c, int user_id, int project_id ) {
    CHECK_DATABASE("publish_project");        
    print("ssproto_publish_project_recv: uid:%d pid:%d", user_id, project_id );
    shareProject( project_id, user_id, NULL, 0 );
    ssproto_publish_project_result_send( _c, project_id );
    return 0;
}

int ssproto_search_published_projects_recv( conn_t _c ) {
    CHECK_DATABASE("search_published_projects");        
    int out[SSPROTO_SEARCH_MAX];
    int n = getPublishedProjects( out, elementof(out) );
    print("ssproto_search_published_projects_recv: found n:%d", n );
    for(int i=0;i<n;i++)  print( "   PJID:%d", out[i] );
    ssproto_search_published_projects_result_send( _c, out, n );
    return 0;
}
int ssproto_search_shared_projects_recv( conn_t _c, int user_id ) {
    CHECK_DATABASE("search_shared_projects");        
    int out[SSPROTO_SEARCH_MAX];
    int n = getSharedProjects( out, elementof(out), user_id );
    print("ssproto_search_shared_projects_recv: found n:%d", n );
    for(int i=0;i<n;i++)  print( "   PJID:%d", out[i] );
    ssproto_search_shared_projects_result_send( _c, user_id, out, n );            
    return 0;
}
int ssproto_project_is_joinable_recv( conn_t _c, int project_id, int user_id ) {
    CHECK_DATABASE("project_is_joinable");        
    bool res = checkSharedProjectJoinable( project_id, user_id );
    int ret = SSPROTO_OK;
    if(res == false ) {
        ret = SSPROTO_E_PROJECT_NOT_SHARED;
    }
    ssproto_project_is_joinable_result_send( _c, project_id, user_id, ret );
    return 0;    
}
int ssproto_unpublish_project_recv( conn_t _c, int project_id ) {
    CHECK_DATABASE("unpublish_project");        
    print("ssproto_unpublish_project_recv project:%d",project_id);
    SharedProject *sp = findSharedProject( project_id );
    if(sp) {
        sp->published = false;
    }
    return 0;    
}
int ssproto_unshare_project_recv( conn_t _c, int project_id ) {
    CHECK_DATABASE("unshare_project");        
    print("ssproto_unshare_project_recv: pjid:%d",project_id);
    unshareProject(project_id);
    return 0;
}
int ssproto_is_published_project_recv( conn_t _c, int project_id ) {
    CHECK_DATABASE("is_published_project");        
    SharedProject *sp = findPublishedProject(project_id);
    int result = 0;
    if(sp && sp->published ) result = 1;
    ssproto_is_published_project_result_send(_c, project_id, result );
    return 0;
}
int ssproto_is_shared_project_recv( conn_t _c, int project_id, int owner_user_id ) {
    CHECK_DATABASE("is_shared_project");        
    SharedProject *sp = findSharedProject(project_id);
    int result = SSPROTO_PROJECT_IS_NOT_SHARED;
    if( sp && sp->owner_user_id == owner_user_id ) {
        print("ssproto_is_shared_project_recv: pub:%d mnum:%d", sp->published, sp->members_num );
        if( sp->members_num > 0 ) {
            result = SSPROTO_PROJECT_IS_SHARED;
        } else if( sp->published ) {
            result = SSPROTO_PROJECT_IS_PUBLISHED;
        }
    }
    ssproto_is_shared_project_result_send( _c, project_id, result );
    return 0;
}


/////////////////
// Image store
class ImageEntry : public Image {
public:
    int id; // Designed for use with project_id.
    double last_updated_at;
    bool changed;
    double last_access_at;
    ImageEntry(int id) : Image(), id(id), last_updated_at(0), changed(false), last_access_at(0) {}
    void updateAccessTime() { last_access_at = now(); }
};

class ImageStore {
public:
    ImageEntry *imgs[1024];
    ImageStore() {
        for(int i=0;i<elementof(imgs);i++) imgs[i] = NULL;
    }

    ImageEntry *alloc( int id, int w, int h ) {
        ImageEntry *e = get(id);
        assert(!e); 
        
        for(int i=0;i<elementof(imgs);i++) {
            if( imgs[i] == NULL ) {
                imgs[i] = new ImageEntry(id);
                imgs[i]->setSize(w,h);
                return imgs[i];
            }
        }
        print("ImageStore::alloc: image entry full!");
        return NULL;
    }
    ImageEntry *get( int id ) {
        for(int i=0;i<elementof(imgs);i++) {
            if( imgs[i] && imgs[i]->id == id ) {
                return imgs[i];
            }
        }
        return NULL;
    }
};
ImageStore g_imgstore;

char *makeImageFullPath( int imgid ) {
    char filename[1024];
    snprintf(filename, sizeof(filename), "_image_%d", imgid );
    static char fullpath[1024];
    makeFullPath( fullpath, sizeof(fullpath), filename );
    return fullpath;
}

void pollAllImageStore() {
    double nt = now();
    const int SAVE_DELAY_SEC = 5;
    const int PURGE_DELAY_SEC = 60;    
    for(int i=0;i<elementof(g_imgstore.imgs);i++) {
        ImageEntry *img = g_imgstore.imgs[i];
        if(img) {
            if( img->changed && img->last_updated_at < nt - SAVE_DELAY_SEC ) {
                char *fullpath = makeImageFullPath( img->id );
                bool ret = img->writeRaw(fullpath);
                img->changed = false;
                prt("[imgsave id:%d ret:%d]", img->id, ret );
            }
            if( img->last_access_at < nt - PURGE_DELAY_SEC ) {
                prt("[imgpurge id:%d]", img->id ); 
                delete img;
                g_imgstore.imgs[i] = NULL;
            }
        }
    }
    
}



int ssproto_ensure_image_recv( conn_t _c, int query_id, int image_id, int w, int h ) {
    CHECK_DATABASE("ensure_image");        
    print("ssproto_ensure_image_recv: qid:%d image_id:%d w:%d h:%d", query_id, image_id, w, h );
    if( w > SSPROTO_IMAGE_WIDTH_MAX || h > SSPROTO_IMAGE_HEIGHT_MAX ) {
        print("ssproto_ensure_image_recv: invalid image size:%d,%d",w,h);
        ssproto_ensure_image_result_send( _c, query_id, SSPROTO_E_IMAGE_INVALID_SIZE, image_id );
    }
    ImageEntry *img = g_imgstore.get( image_id );
    if(!img) {
        // Not in memory, load from storage..

        img = g_imgstore.alloc( image_id, w, h );
        if(!img) {
            ssproto_ensure_image_result_send( _c, query_id, SSPROTO_E_IMAGE_STORE_CANNOT_ALLOCATE, image_id );
            return 0;
        }
            
        char *fullpath = makeImageFullPath( image_id );
        if( img->loadRaw(fullpath) ) {
            // print("loaded png file:'%s'", fullpath );
        } else {
            print("ssproto_ensure_image_recv: can't load file:'%s'", fullpath );
            // Not in file, initialize first!
            img->fill(Color(0,0,0,1));
#if 0            
            for(int i=0;i<w;i++) {
                img->setPixel(i,i, Color(1,0,0,1) );
                img->setPixel(i+1,i, Color(1,0,0,1) );
                img->setPixel(i-1,i, Color(1,0,0,1) );                                
                img->setPixel(i,h-1-i, Color(1,0,0,1) );
                img->setPixel(i+1,h-1-i, Color(1,0,0,1) );
                img->setPixel(i-1,h-1-i, Color(1,0,0,1) );                                
            }
#endif            
            img->writeRaw(fullpath);
        }
    } else {
        print("ssproto_ensure_image_recv: existing image:%d", image_id );
    }
    img->updateAccessTime();
    ssproto_ensure_image_result_send( _c, query_id, SSPROTO_OK, image_id );
    return 0;
}


int ssproto_update_image_part_recv( conn_t _c, int query_id, int image_id,
                                    int x0, int y0, int w, int h,
                                    const unsigned char *r, int r_len,
                                    const unsigned char *g, int g_len,
                                    const unsigned char *b, int b_len ) {
    CHECK_DATABASE("update_image_part");        
    //    print("ssproto_update_image_part_recv: %d,%d,%d,%d",x0,y0,w,h);
    ImageEntry *img = g_imgstore.get(image_id);
    if(!img) {
        print("ssproto_update_image_part_recv: image_id:%d not found", image_id );
        ssproto_update_image_part_result_send( _c, query_id, SSPROTO_E_IMAGE_NOT_FOUND, image_id );
        return 0;
    }
    int elemnum = w*h;
    if( x0 < 0 || y0 < 0 || (x0+w) > img->width || (y0+h) > img->height ||
        elemnum != r_len || elemnum != g_len || elemnum != b_len ) {
        print("ssproto_update_image_part_recv: image_id:%d invalid size:x0:%d,y0:%d,w:%d,h:%d", image_id, x0,y0,w,h);
        ssproto_update_image_part_result_send( _c, query_id, SSPROTO_E_IMAGE_INVALID_SIZE, image_id );
        return 0;
    }


    int i = 0;
    for(int y=y0;y<y0+h;y++) {
        for(int x=x0;x<x0+w;x++) {
            unsigned char rr = r[i], gg = g[i], bb = b[i];
            img->setPixelRaw(x,y,rr,gg,bb,0xff);
            i++;
        }
    }
    img->last_updated_at = now();
    img->changed = true;
    img->updateAccessTime();    
    return 0;    
}

int ssproto_get_image_png_recv( conn_t _c, int query_id, int image_id ) {
    CHECK_DATABASE("get_image_png");        
    ImageEntry *img = g_imgstore.get(image_id);
    if(!img) {
        print("ssproto_get_image_png_reecv: image not found:%d",image_id);
        ssproto_get_image_png_result_send( _c, query_id, SSPROTO_E_IMAGE_NOT_FOUND, image_id, NULL, 0 );
        return 0;
    }

    double st = now();
    static unsigned char pngbuf[SSPROTO_PNG_SIZE_MAX];
    unsigned char *ptr = pngbuf;
    size_t sz = sizeof(pngbuf);
    if( img->writePNGMem( &ptr, &sz ) == false ) {
        print("writePNGMem: failed for img:%d",image_id );
        ssproto_get_image_png_result_send( _c, query_id, SSPROTO_E_IMAGE_CANNOT_CONVERT, image_id, NULL, 0 );
    } else {
        img->updateAccessTime();        
        print("writePNGMem: success for img:%d",image_id );        
        ssproto_get_image_png_result_send( _c, query_id, SSPROTO_OK, image_id, (const char*)ptr, sz );
    }
    double et = now();
    print("PNG time:%f size:%d", et-st, sz);
    return 0;    
}
int ssproto_get_image_raw_recv( conn_t _c, int query_id, int image_id, int x0, int y0, int w, int h ) {
    CHECK_DATABASE("get_image_raw");        
    ImageEntry *img = g_imgstore.get(image_id);
    if(!img) {
        print("ssproto_get_image_png_reecv: image not found:%d",image_id);
        ssproto_get_image_raw_result_send( _c, query_id, SSPROTO_E_IMAGE_NOT_FOUND, image_id, x0,y0,w,h, NULL, 0);
        return 0;
    }
    if( w>512 || h>512 ) {
        print("ssproto_get_image_png_reecv: image invalid w/h:%d/%d", w,h );        
        ssproto_get_image_raw_result_send( _c, query_id, SSPROTO_E_IMAGE_INVALID_SIZE, image_id, x0,y0,w,h, NULL,0 );
        return 0;
    }
    
    static unsigned char rawbuf[SSPROTO_RAW_IMAGE_SIZE_MAX];
    size_t sz = w*h*4;
    assert(sz<=SSPROTO_RAW_IMAGE_SIZE_MAX);
    img->getAreaRaw( x0, y0, w, h, rawbuf, sz );
    img->updateAccessTime();            
    ssproto_get_image_raw_result_send( _c, query_id, SSPROTO_OK, image_id, x0, y0, w, h, (char*)rawbuf, sz );
    //    prt("img:%d(%d,%d,%d,%d sz:%d ret:%d)", image_id, x0,y0,w,h,sz, ret );
    return 0;
}



// Gives SSPROTO_E_* when error
int getCounterValue( int cat, int id, int *out ) {
    char fullpath[1024];
    Format f( "_counter_cat%d_id%d", cat, id );
    int r = makeFullPath( fullpath, sizeof(fullpath), f.buf );
    if(r<0) return r;
    char buf[128];
    size_t sz = sizeof(buf);
    bool ret = readFile(fullpath, buf, &sz );
    if(!ret) return SSPROTO_E_FILE_ACCESS;
    *out = atol(buf);
    return SSPROTO_OK;
}
// Gives SSPROTO_E_* when error
int setCounterValue( int cat, int id, int value ) {
    char fullpath[1024];
    Format f( "_counter_cat%d_id%d", cat, id );
    int r = makeFullPath( fullpath, sizeof(fullpath), f.buf );
    if(r<0) return r;
    char str[128];
    snprintf( str, sizeof(str), "%d", value );
    bool ret = writeFile( fullpath, str, strlen(str), g_enable_fsync );
    if(!ret) return SSPROTO_E_FILE_ACCESS;
    return SSPROTO_OK;
}
int ssproto_counter_add_recv( conn_t _c, int counter_category, int counter_id, int addvalue ) {
    CHECK_DATABASE("counter_add");        
    int v;
    int ret = getCounterValue( counter_category, counter_id, &v );
    //    print("ssproto_counter_add_recv: ret:%d getv:%d addv:%d", ret, v, addvalue );
    if(ret == SSPROTO_OK ) {
        v += addvalue;
        ret = setCounterValue( counter_category, counter_id, v );
        prt(" cntadd[%d,%d,%d]", counter_category, counter_id, v );
        //      print("ssproto_counter_add_recv: cat:%d id:%d newvalue:%d", counter_category, counter_id, v );
    } else {
        setCounterValue( counter_category, counter_id, addvalue );
        //        print("ssproto_counter_add_recv: creating new counter: cat:%d id:%d", counter_category, counter_id );
        prt(" cntini[%d,%d,%d]", counter_category, counter_id, addvalue );
    }
    return 0;
}

int ssproto_counter_get_recv( conn_t _c, int counter_category, int counter_id ) {
    CHECK_DATABASE("counter_get");        
    int v=0;
    int ret = getCounterValue( counter_category, counter_id, &v );
    ssproto_counter_get_result_send( _c, counter_category, counter_id, ret, v );
    return 0;
}

void dumpNetstat() {
    tcpcontext_stat_t dbst, rtst;
    memset( &dbst, 0, sizeof(dbst) );
    memset( &rtst, 0, sizeof(rtst) );
    if(g_enable_database) vce_tcpcontext_get_stat( g_dbctx, &dbst );
    if(g_enable_realtime) vce_tcpcontext_get_stat( g_rtctx, &rtst );
    static long long last_loopcnt;
    static time_t last_dump_at;
    time_t nt = time(NULL);
    long long loop_diff = g_loopcnt - last_loopcnt;
    long long dt = nt-last_dump_at;
    if(dt==0)dt=1;
    static long long last_dbrecv_bytes=0, last_dbsend_bytes=0;
    static long long last_rtrecv_bytes=0, last_rtsend_bytes=0;
    double dbrecv_mbps = (dbst.recv_byte-last_dbrecv_bytes)/(double)(dt)*8 / 1024.0 / 1024.0;
    double dbsend_mbps = (dbst.send_byte-last_dbsend_bytes)/(double)(dt)*8 / 1024.0 / 1024.0;
    double rtrecv_mbps = (rtst.recv_byte-last_rtrecv_bytes)/(double)(dt)*8 / 1024.0 / 1024.0;
    double rtsend_mbps = (rtst.send_byte-last_rtsend_bytes)/(double)(dt)*8 / 1024.0 / 1024.0;

    
    print("Time:%d loop:%lld(d:%lld %lld/sec)", nt, g_loopcnt, loop_diff, loop_diff/dt );
    if( g_enable_database ) {
        print("Database sockets:");
        print("  current_conn:%d recv_byte:%lld(%.1fMbps) send_byte:%lld(%.1fMbps)",  dbst.current_conn, dbst.recv_byte, dbrecv_mbps, dbst.send_byte, dbsend_mbps);
        print("  recv_syscall:%lld recv_syscall_e:%lld", dbst.recv_syscall, dbst.recv_syscall_e );
        print("  send_syscall:%lld send_syscall_e:%lld", dbst.send_syscall, dbst.send_syscall_e );
        print("  accept_syscall:%lld accept_syscall_e:%lld", dbst.accept_syscall, dbst.accept_syscall_e );
        print("  connect_syscall:%lld connect_syscall_e:%lld", dbst.connect_syscall, dbst.connect_syscall_e );
        print("  conn_write:%lld conn_timeout:%lld tcpcontext_connect:%lld", dbst.conn_write, dbst.conn_timeout, dbst.tcpcontext_connect );
    }
    if( g_enable_realtime ) { 
        print("Realtime sockets:");
        print("  current_conn:%d recv_byte:%lld(%.1fMbps) send_byte:%lld(%.1fMbps)",  rtst.current_conn, rtst.recv_byte, rtrecv_mbps, rtst.send_byte, rtsend_mbps );
        print("  recv_syscall:%lld recv_syscall_e:%lld", rtst.recv_syscall, rtst.recv_syscall_e );
        print("  send_syscall:%lld send_syscall_e:%lld", rtst.send_syscall, rtst.send_syscall_e );
        print("  accept_syscall:%lld accept_syscall_e:%lld", rtst.accept_syscall, rtst.accept_syscall_e );
        print("  connect_syscall:%lld connect_syscall_e:%lld", rtst.connect_syscall, rtst.connect_syscall_e );
        print("  conn_write:%lld conn_timeout:%lld tcpcontext_connect:%lld", rtst.conn_write, rtst.conn_timeout, rtst.tcpcontext_connect );
    }
    last_loopcnt = g_loopcnt;
    last_dump_at = nt;
    last_dbrecv_bytes = dbst.recv_byte;
    last_dbsend_bytes = dbst.send_byte;
    last_rtrecv_bytes = rtst.recv_byte;
    last_rtsend_bytes = rtst.send_byte;
}

///////

void printStat() {
    print("\n====");
    dumpNetstat();
    // projects
    print("projects: %d", countProject() );
    if( g_dump_projects ) {
        time_t nowt = time(NULL);
        for(int i=0;i<elementof(g_projects);i++) {
            if( g_projects[i].id)  g_projects[i].dump(nowt);
        }
    }
    print("shared projects: %d", countSharedProject());
    if( g_dump_shared_projects ) {
        for(int i=0;i<elementof(g_sharedpjs);i++) {
            if( g_sharedpjs[i].project_id) g_sharedpjs[i].dump();
        }
    }
    print("locks alive: %d projects", countLockGridsActive() );
    for(int i=0;i<elementof(g_lockgrids);i++) {
        if( g_lockgrids[i].id ) {
            prt( "%d:%d ", g_lockgrids[i].id, g_lockgrids[i].lock_cnt );
        }        
    }
    print("");
    print("====");
}
