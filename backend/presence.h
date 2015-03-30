#ifndef _PRESENCE_H_
#define _PRESENCE_H_

class Activity {
public:
    int user_id;
    time_t last_active_at;
    Activity() : user_id(0), last_active_at(0) {}
    void clear() { user_id=0; last_active_at=0; }
    static const int TIMEOUT = 30;
    bool isTimeout(time_t nowt) { return (nowt - last_active_at) > TIMEOUT; }
};

class Project {
public:
    int id;
    Activity online_players[SSPROTO_PRESENCE_PER_PROJECT_MAX];
    Project() : id(0) {}
    void clear();
    bool updateUser( int user_id );
    bool deleteUser( int user_id );
    void listOnlineUsers( int *out, int *n );
    int countOnlineUsers();
    void poll( time_t nowt );
    void dump( time_t nowt ) {
        print( " id:%d online:%d", id, countOnlineUsers() );
        for(int i=0;i<elementof(online_players);i++) {
            if( online_players[i].user_id) {
                print( " [%d] : uid:%d active:%d", i, online_players[i].user_id, nowt - online_players[i].last_active_at  );
            }
        }
    }    
};

#define ONLINE_PROJECT_MAX 1024

#endif
