#ifndef _COMMON_H_
#define _COMMON_H_

#include "vce.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#if defined(linux) || defined(__APPLE__) || defined(sun)
#include <unistd.h>
#endif

extern int vce_last_error;
#define SET_LAST_ERROR(x)    ( vce_last_error = (x) )


#define VCE_ERROUT_V0(fmt)  vce_errout_v(fmt)
#define VCE_ERROUT_V1(fmt,a)  vce_errout_v(fmt,(a))
#define VCE_ERROUT_V2(fmt,a,b)  vce_errout_v(fmt,(a),(b))
#define VCE_ERROUT_V3(fmt,a,b,c)  vce_errout_v(fmt,(a),(b),(c))
#define VCE_ERROUT_V4(fmt,a,b,c,d)  vce_errout_v(fmt,(a),(b),(c),(d))
#define VCE_ERROUT_V5(fmt,a,b,c,d,e)  vce_errout_v(fmt,(a),(b),(c),(d),(e))
#define VCE_ERROUT0(fmt)  vce_errout(fmt)
#define VCE_ERROUT1(fmt,a)  vce_errout(fmt,(a))
#define VCE_ERROUT2(fmt,a,b)  vce_errout(fmt,(a),(b))
#define VCE_ERROUT3(fmt,a,b,c)  vce_errout(fmt,(a),(b),(c))
#define VCE_ERROUT4(fmt,a,b,c,d)  vce_errout(fmt,(a),(b),(c),(d))
#define VCE_ERROUT5(fmt,a,b,c,d,e)  vce_errout(fmt,(a),(b),(c),(d),(e))
#define VCE_ERROUT6(fmt,a,b,c,d,e,f) vce_errout(fmt,(a),(b),(c),(d),(e),(f))
#define VCE_ERROUT7(fmt,a,b,c,d,e,f,g) vce_errout(fmt,(a),(b),(c),(d),(e),(f),(g))


// uselog.c 
extern time_t vce_global_time;        
extern int vce_verbose_mode;
extern int vce_log_read_write;
extern int vce_socket_library_ok;
extern int vce_tcpcontext_mi;

#endif
