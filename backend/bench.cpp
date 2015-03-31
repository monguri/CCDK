

#include "vce.h"
#include "moyai/cumino.h"
#include "ssproto_cli.h"



typedef enum {
    BENCHMARKTYPE_NOT_INIT = 0,
    BENCHMARKTYPE_REALTIME = 1,
    BENCHMARKTYPE_DATABASE = 2,
} BENCHMARKTYPE;

BENCHMARKTYPE g_benchmark_type = BENCHMARKTYPE_NOT_INIT;


class Client;

Client *g_clients[2048];
tcpcontext_t g_rttcp;
char g_host[128] = "localhost";
const int RTPORT = 22223;
const int DBPORT = 22222;
int g_maxcon = 4;
int g_channel_id = 1;
int g_nearcast_range = 0;
int g_portnumber = 0;
int g_filenum = 1024;
int g_filesize = 8192;

long long g_total_sent_count;
long long g_total_sent_bytes;
long long g_total_recv_count;
long long g_total_recv_bytes;
long long g_total_error_count;


class Client {
public:
    conn_t conn;
    double accum_time;
    double last_nc_sent_at, last_pos_sent_at; // for realtime
    double last_ping_sent_at; 
    double last_put_sent_at; // for database
    int id;
    bool joined;
    bool finished;
    int ping_cnt;
    BENCHMARKTYPE bmt;
    Client( const char *host, int port, BENCHMARKTYPE bmt );
    void poll( double dt );
    void sendRandomPos();
};

class StateBuffer {
public:
    Client *cli;
};

Client::Client( const char *host, int port, BENCHMARKTYPE bmt ) : accum_time(0), last_nc_sent_at(0), last_pos_sent_at(0), last_ping_sent_at(0), last_put_sent_at(0), id(0), joined(false), finished(false), ping_cnt(0), bmt(bmt) {
    conn = vce_tcpcontext_connect( g_rttcp, host, port );
    if( !vce_conn_is_valid( conn ) ) {
        assertmsg(false, "Client::Client: vce_tcpcontext_connect failed");
    }
    ssproto_conn_serial_send( conn );
    StateBuffer *sb = (StateBuffer*) vce_conn_get_state_buffer( conn, NULL );
    sb->cli = this;
}
void Client::sendRandomPos() {
    int x = irange(0, g_nearcast_range);
    int y = irange(0, g_nearcast_range);
    ssproto_update_nearcast_position_send( conn, x,y );
    last_pos_sent_at = accum_time + range(0,0.05);
}

void Client::poll( double dt ) {
    accum_time += dt;
    if( bmt == BENCHMARKTYPE_REALTIME ) {
        if( joined ) {
            static char buf[32] = {
                0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15,
                0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15,
            };        
            if( last_pos_sent_at < accum_time - 0.2 ) {
                sendRandomPos();
            }
            if( last_nc_sent_at < accum_time - 0.03 ) {
                int n = irange(1,100);
                for(int i=0;i<n;i++) {
                    int len = ssproto_nearcast_send( conn, 0,0, 300, 12345, buf, sizeof(buf));
                    last_nc_sent_at = accum_time;
                    if(len>0) {
                        g_total_sent_bytes += len;
                        g_total_sent_count ++;
                    } else {
                        g_total_error_count ++;
                    }
                }
            }
        }
    } else if( bmt == BENCHMARKTYPE_DATABASE ) {
        static char buf[SSPROTO_FILE_SIZE_MAX];
        assert( g_filesize <= SSPROTO_FILE_SIZE_MAX );
        memset( buf, 0xff, g_filesize );
        if( last_put_sent_at < accum_time - 0.05 ) {
            static int qid = 0;
            qid++;
            Format path( "_benchmark_%d", qid % g_filenum );
            int len;
            len = ssproto_put_file_send( conn, qid, path.buf, buf, g_filesize );
            if(len<0) print("ssproto_put_file_send failed.");
            g_total_sent_bytes += len;
            g_total_sent_count ++;
            last_put_sent_at = accum_time;
        }
    }
    if( last_ping_sent_at < accum_time - 1 ) {
        ping_cnt++;
        long long llt_usec = (long long)(accum_time*1000*1000);
        ssproto_ping_send( conn, llt_usec, ping_cnt );
        last_ping_sent_at = accum_time;
    }
}

int ssproto_put_file_result_recv( conn_t _c, int query_id, int result, const char *filename ) {
    assertmsg(result==SSPROTO_OK, "ssproto_put_file_result_recv failed. result:%d",result);
    int len = ssproto_get_file_send( _c, query_id, filename );
    if(len<0) print( "ssproto_get_file failed");
    g_total_sent_bytes += len;
    g_total_sent_count++;
    return 0;
}
int ssproto_get_file_result_recv( conn_t _c, int query_id, int result, const char *filename, const char *data, int data_len ) {
    assertmsg(result==SSPROTO_OK, "ssproto_get_file_result_recv failed. result:%d",result);
    g_total_recv_bytes += data_len;
    g_total_recv_count++;
    return 0;
}


int conn_closewatcher( conn_t c, CLOSE_REASON reason ) {
    StateBuffer *sb = (StateBuffer*) vce_conn_get_state_buffer( c, NULL );
    print("closed!. reason:%d id:%d", reason, sb->cli->id );    
    switch(reason) {
    case CLOSE_REASON_REMOTE:  // network error
    case CLOSE_REASON_TIMEOUT:
        break;
    case CLOSE_REASON_APPLICATION: // OK
        break;
    case CLOSE_REASON_UNKNOWN: // program error
    case CLOSE_REASON_DECODER:
    case CLOSE_REASON_ENCODER:
    case CLOSE_REASON_PARSER:
    case CLOSE_REASON_INTERNAL:
    default:
        break;        
    }

    sb->cli->finished = true;

    return 0;
}
int ssproto_cli_sender( conn_t c, char *data, int len ) {
    //    print("ssproto_cli_sender: len:%d",len);
    int r = vce_protocol_unparser_bin32( c, data, len );
    if( r < 0 ) {
        if( vce_conn_is_valid(c) )  print("ssproto_cli_sender: unparser_bin32 failed! ret:%d",r);
    }
    return r;
}
int ssproto_cli_recv_error_callback( conn_t c, int e ) {
    print( "ssproto_cli_recv_error_callback: gen error: %d", e );
    return -1;
}


int ssproto_conn_serial_result_recv( conn_t _c, int serial ) {
    StateBuffer *sb = (StateBuffer*) vce_conn_get_state_buffer( _c, NULL );
    sb->cli->id = serial;
    prt("[cli id:%d]", sb->cli->id);
    if( g_benchmark_type == BENCHMARKTYPE_REALTIME ) {
        ssproto_join_channel_send( _c, g_channel_id );
        sb->cli->sendRandomPos();
    }
    return 0;
}
int ssproto_join_channel_result_recv( conn_t _c, int channel_id, int retcode ) {
    StateBuffer *sb = (StateBuffer*) vce_conn_get_state_buffer( _c, NULL );
    prt("[join id:%d chid:%d : ret:%d]", sb->cli->id, channel_id, retcode );
    sb->cli->joined = true;
    return 0;
}
int ssproto_get_channel_member_count_result_recv( conn_t _c, int channel_id, int maxnum, int curnum ) {return 0;}

int ssproto_nearcast_notify_recv( conn_t _c, int channel_id, int sender_cli_id, int x, int y, int range, int type_id, const char *data, int data_len ) {
    g_total_recv_count++;
    g_total_recv_bytes += data_len;
    return 0;
}
int ssproto_pong_recv( conn_t _c, VCEI64 t_usec, int cmd ) {
    StateBuffer *sb = (StateBuffer*) vce_conn_get_state_buffer( _c, NULL );
    int ping_cnt = cmd;
    if( sb->cli->ping_cnt == ping_cnt ) {
        long long dtus = (long long)(sb->cli->accum_time*1000*1000) - t_usec;
        if( dtus > 200*1000) {
            prt("[ping slow dt:%lldms id:%d]", dtus/1000, sb->cli->id );
        }
    } else {
        prt("[ping too slow. recvcnt:%d curcnt:%d]", ping_cnt, sb->cli->ping_cnt );
    }
    return 0;
}

bool initNetwork() {
    vce_initialize();
    vce_set_verbose_mode(0);

    g_rttcp = vce_tcpcontext_create( 0, // client
                                     NULL, 0,
                                     g_maxcon, // maxcon
                                     1024*1024, 1024*1024,
                                     60,
                                     0,
                                     1, // nodelay
                                     sizeof(StateBuffer) );
    if( !g_rttcp ) {
        print("tcpcontext_create for rt: %s", STRERR );
        return false;
    }
    vce_tcpcontext_set_conn_call_parser_per_heartbeat( g_rttcp, 1000 );
    vce_tcpcontext_set_conn_parser( g_rttcp, vce_protocol_parser_bin32, ssproto_cli_pcallback );
    vce_tcpcontext_set_conn_closewatcher( g_rttcp, conn_closewatcher );
    vce_set_heartbeat_wait_flag(1);                                     

    return true;
}
void printUsage() {
    print("Usage:\nssbench (realtime|database) [--host=IPADDR] [--maxcon=NUMBER] [--channel=NUMBER] [--range=DISTANCE] [--filenum=NUMBER] [--filesize=NUMBER]" );
}

int main( int argc, char **argv ) {
    for(int i=0;i<argc;i++) {
        if( strcmp( argv[i], "realtime" ) == 0 ) {
            g_benchmark_type = BENCHMARKTYPE_REALTIME;
            g_portnumber = RTPORT;
        } else if( strcmp( argv[i], "database" ) == 0 ) {
            g_benchmark_type = BENCHMARKTYPE_DATABASE;
            g_portnumber = DBPORT;
        } else if( strncmp( argv[i], "--host=", strlen("--host=") ) == 0 ) {
            char *p = argv[i] + strlen("--host=");
            strncpy( g_host, p, sizeof(g_host) );
        } else if( strncmp( argv[i], "--maxcon=", strlen("--maxcon=") ) == 0 ) {
            g_maxcon = atoi( argv[i] + strlen("--maxcon=" ) );
        } else if( strncmp( argv[i], "--channel=", strlen("--channel=") ) == 0 ) {
            g_channel_id = atoi( argv[i] + strlen("--channel=" ) );
        } else if( strncmp( argv[i], "--range=", strlen("--range=") ) == 0 ) {
            g_nearcast_range = atoi( argv[i] + strlen("--range=" ) );
        } else if( strncmp( argv[i], "--filenum=", strlen("--filenum=") ) == 0 ) {
            g_filenum = atoi( argv[i] + strlen("--filenum=" ) );
        } else if( strncmp( argv[i], "--filesize=", strlen("--filesize=") ) == 0 ) {
            g_filesize = atoi( argv[i] + strlen("--filesize=" ) );
            if( g_filesize > SSPROTO_FILE_SIZE_MAX ) {
                print("File size too large: %d", g_filesize );
                return 1;
            }
        }
    }
    if( g_benchmark_type == BENCHMARKTYPE_NOT_INIT ) {
        printUsage();
        return 1;
    }

    print("type:%d host:'%s' port:%d maxcon:%d nearcast-range:%d", g_benchmark_type, g_host, g_portnumber, g_maxcon, g_nearcast_range );

    if(!initNetwork()) return 1;


    double last_stat_at = 0;
    while(true) {
        static double lasttime = now();
        double nt = now();
        double dt = nt - lasttime;
        lasttime = nt;
        
        vce_heartbeat();

        // new connection
        static double last_newconn_at=0;
        if( last_newconn_at < nt - 0.05 ) {
            last_newconn_at = nt;
            for(int i=0;i<g_maxcon;i++) {
                if( !g_clients[i] ) {
                    g_clients[i] = new Client(g_host, g_portnumber, g_benchmark_type );
                    break;
                }
            }
        }

        // polling
        for(int i=0;i<g_maxcon;i++) {
            if( g_clients[i] ) g_clients[i]->poll(dt);
        }

        if( last_stat_at < nt - 1 ) {
            static long long last_sent_bytes = 0;
            long long d_sent_bytes = g_total_sent_bytes - last_sent_bytes;
            last_sent_bytes = g_total_sent_bytes;
            static long long last_recv_bytes = 0;
            long long d_recv_bytes = g_total_recv_bytes - last_recv_bytes;
            last_recv_bytes = g_total_recv_bytes;
            print("stat: send:%lld/%lldMB/%.1fMbps recv:%lld/%lldMB/%.1fMbps Error:%d",
                  g_total_sent_count, g_total_sent_bytes/1024/1024, (double)d_sent_bytes/1024.0/1024.0*8,
                  g_total_recv_count, g_total_recv_bytes/1024/1024, (double)d_recv_bytes/1024.0/1024.0*8,
                  g_total_error_count                  
                  );
            last_stat_at = nt;
        }
        

    }
    return 0;
}




int ssproto_version_notify_recv( conn_t _c, unsigned int maj, unsigned int min ) {return 0;}
int ssproto_clean_all_result_recv( conn_t _c ) {return 0;}
int ssproto_check_file_result_recv( conn_t _c, int query_id, int result, const char *filename ) {return 0;}
int ssproto_ensure_image_result_recv( conn_t _c, int query_id, int result, int image_id ) {return 0;}
int ssproto_update_image_part_result_recv( conn_t _c, int query_id, int result, int image_id ) {return 0;}
int ssproto_get_image_png_result_recv( conn_t _c, int query_id, int result, int image_id, const char *png_data, int png_data_len ) {return 0;}
int ssproto_get_image_raw_result_recv( conn_t _c, int query_id, int result, int image_id, int x0, int y0, int w, int h, const char *raw_data, int raw_data_len ) {return 0;}
int ssproto_generate_id_32_result_recv( conn_t _c, int query_id, int generated_id_start, int num ) {return 0;}
int ssproto_kvs_command_str_result_recv( conn_t _c, int query_id, int retcode, int valtype, const char * const *result, int result_len ) {return 0;}
int ssproto_kvs_push_to_list_result_recv( conn_t _c, int query_id, int retcode, const char *key, int updated_num ) {return 0;}
int ssproto_kvs_get_list_range_result_recv( conn_t _c, int query_id, int retcode, int start_ind, int end_ind, const char *key, const char * const *result, int result_len ) {return 0;}
int ssproto_kvs_append_string_array_result_recv( conn_t _c, int query_id, int retcode, const char *key, const char *field ) {return 0;}
int ssproto_kvs_get_string_array_result_recv( conn_t _c, int query_id, int retcode, const char *key, const char *field, const char * const *result, int result_len ) {return 0;}
int ssproto_kvs_save_bin_result_recv( conn_t _c, int query_id, int retcode, int valtype, const char *key, const char *field ) {return 0;}
int ssproto_kvs_load_bin_result_recv( conn_t _c, int query_id, int retcode, int has_data, const char *key, const char *field, const char *data, int data_len ) {return 0;}
int ssproto_counter_get_result_recv( conn_t _c, int counter_category, int counter_id, int result, int curvalue ) {return 0;}
int ssproto_share_project_result_recv( conn_t _c, int project_id ) {return 0;}
int ssproto_publish_project_result_recv( conn_t _c, int project_id ) {return 0;}
int ssproto_search_shared_projects_result_recv( conn_t _c, int user_id, const int *project_ids, int project_ids_len ) {return 0;}
int ssproto_search_published_projects_result_recv( conn_t _c, const int *project_ids, int project_ids_len ) {return 0;}
int ssproto_project_is_joinable_result_recv( conn_t _c, int project_id, int user_id, int result ) {return 0;}
int ssproto_is_published_project_result_recv( conn_t _c, int project_id, int published ) {return 0;}
int ssproto_is_shared_project_result_recv( conn_t _c, int project_id, int shared ) {return 0;}
int ssproto_list_presence_result_recv( conn_t _c, int project_id, const int *user_ids, int user_ids_len ) {return 0;}
int ssproto_count_presence_result_recv( conn_t _c, int project_id, int user_num ) {return 0;}
int ssproto_lock_grid_result_recv( conn_t _c, int grid_id, int x, int y, int retcode ) {return 0;}
int ssproto_unlock_grid_result_recv( conn_t _c, int grid_id, int x, int y, int retcode ) {return 0;}
int ssproto_lock_project_result_recv( conn_t _c, int project_id, int category, int retcode ) {return 0;}
int ssproto_unlock_project_result_recv( conn_t _c, int project_id, int category, int retcode ) {return 0;}
int ssproto_broadcast_notify_recv( conn_t _c, int type_id, int sender_cli_id, const char *data, int data_len ) {return 0;}
int ssproto_channelcast_notify_recv( conn_t _c, int channel_id, int sender_cli_id, int type_id, const char *data, int data_len ) {return 0;}
int ssproto_leave_channel_result_recv( conn_t _c, int retcode ) {return 0;}
