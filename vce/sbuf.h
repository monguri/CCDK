#ifndef _SBUF_H_
#define _SBUF_H_

typedef struct _sbuf
{
    char *buf;
    unsigned int start , end;
    size_t len;

	int mem_i; /* index of array(mem.c) */
} sbuf;

int vce_sbuf_init( sbuf *s, int mi );
void vce_sbuf_cleanup( sbuf *s );
int vce_sbuf_push( sbuf *s, char *p , size_t pl );
int vce_sbuf_shrink( sbuf *s, char *out, size_t outl );
int vce_sbuf_get_rest( sbuf *s );
int vce_sbuf_get_use( sbuf *s );
void vce_sbuf_get_buffer( sbuf *s, char **b , int *l );
int vce_sbuf_is_valid( sbuf *s );

#endif /* _SBUF_H_ */
