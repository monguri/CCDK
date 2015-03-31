#ifndef _INIT_H_
#define _INIT_H_

#include "vce.h"

extern vce_limit_t vce_limit;
extern int vce_fdwrap_select_nfds;

extern VCEI64 vce_mainloop_utime_store;
extern time_t vce_global_time;
extern int vce_mainloop_counter;
extern int vce_select_timeout_flag;
extern vce_limit_t vce_limit;
extern time_t vce_global_time;

#endif
