#ifndef _UTIL_H_
#define _UTIL_H_

char * vce_make_ipv4_dot_notation( const char *b, int len,char *work, int wkl );
char * vce_make_ipv6_dot_notation( const char *b, int len,char *work, int worklen );

int tolower_direct( int c );

extern void (*vce_internal_free_func)(void*);

#endif
