#include "vce.h"
#include "vcecommon.h"
#include "osdep.h"
#include "util.h"


static void * (*vce_internal_malloc_func)(size_t) = malloc;
static void * (*vce_internal_realloc_func)(void*,size_t) = realloc;
void (*vce_internal_free_func)(void*) = free;

//  アルファベットから数値にする
static int getbinhex( int c ) {
    switch(c){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A':
    case 'a': return 10;
    case 'B':
    case 'b': return 11;
    case 'C':
    case 'c': return 12;
    case 'D':
    case 'd': return 13;
    case 'E':
    case 'e': return 14;
    case 'F':
    case 'f': return 15;
    }
    return 0;
}

void vce_make_binary_array_from_hex( char *out, int outlen, const char *hex ) {
    int i,odd_flag=0;
    int l = (int)strlen( hex );

	if( hex[0] == '0' &&
		( hex[1] == 'X' || hex[1] == 'x') ){
		hex+=2;
	}

    if( l <= 1 )return;
    
    if( ( l % 2 ) != 0 ){
        odd_flag = 1;
    }
    if( !odd_flag ){
        for(i=0;i<outlen;i++){
            if( hex[i*2] == '\0' ) return;
            out[i] = getbinhex( hex[i*2] ) * 16 + getbinhex( hex[i*2+1] );
        }
    } else {
        for(i=0;i<outlen;i++){
            if( hex[i*2+1] == '\0' ){
                out[i] = getbinhex( hex[i*2] ) * 16;
                return;
            }
            out[i] = getbinhex( hex[i*2] ) * 16 + getbinhex( hex[i*2+1] );
        }
    }
}

void vce_make_binary_array_from_line( const char *line, int linelen, char *out, int *outlen, int *uselen ) {
	int i;
	int outmax = *outlen;
	for(i=0;i<linelen; i++){
		int rest = linelen - i;
		if( rest > 2 && line[i] == '\r' && line[i+1] == '\n' ){
			vce_make_binary_array_from_hex(
				out, *outlen= MIN(outmax,i/2), line );
			*uselen = i+2;
			return;
		} else if( rest > 1 && line[i] == '\n' ){
			vce_make_binary_array_from_hex(
				out, *outlen = MIN( outmax, i/2) , line );
			*uselen = i+1;
			return;
		} else if( rest == 1 ){
			vce_make_binary_array_from_hex(
				out, *outlen = MIN( outmax, i/2) , line );
			*uselen = i+1;
			return;
		}
	}
	*uselen = *outlen = 0;
	return;
}

void vce_dump_buffer( char *buf, int len ) {
	int i;
	for( i=0;i<len;i++){
		vce_errout( "%02x " , buf[i]&0xff );
		if( (i %16)== 15 ){
			vce_errout( "\n" );
		}
	}
    vce_errout( "\n" );
}

int vce_make_hex_from_binary_array( char *out, int outlen, const char *buf,int len, int folding ) {
    int i,so_far=0;
    if(len==0){
        if(outlen>=1){
            out[0]='\0';
        }
        return 0;
    }
	for( i = 0; i < len; i++ ){
		if( (so_far + 2) >= outlen ) return SET_LAST_ERROR( VCE_EFULL );
        /* 高速化できる PENDING */
		vce_snprintf( out + so_far ,3, "%02x" , buf[i] & 0xff );
		so_far += 2;
        if( folding ){
            if( (i % 32 ) == 31 || i == ( len-1) ){
                if( ( so_far + 1 ) >= outlen ){
                    return SET_LAST_ERROR( VCE_EFULL);
                }
                vce_snprintf( out + so_far , 2, "\n" );
                so_far ++;
            }
        }
	}
    return so_far;
}


#define TEST_PARAMCHAR(c) ( isalpha(c) || isdigit(c) || c == '-' || c == '_')

int vce_read_simple_config_file( const char *filename, int ( *callback ) (char*,int,char *,char *) ) {
	char line[32768];
	int lineno;
	
	FILE *fp = fopen( filename , "r" );
	if( !fp ){
		return SET_LAST_ERROR(VCE_EACCESSFILE);
	}

	lineno = 0;
	while( fgets( line, sizeof(line), fp ) ){
		char param[32768] , value[32768];
		int plen,ret;
        int sl = (int)strlen(line);
		lineno++;
        if( line[0] == '#' ){continue; }
		if( strlen(line) < 2 ){ continue; }
		
		if( line[sl-2] == '\r' &&
			line[sl-1] == '\n' ){
			line[sl-2] = '\0';
			line[sl-1] = '\0';
            if( strlen(line) < 2 ){ continue; }
		} else if( line[sl-1] == '\n' ){
			line[sl-1] = '\0';
		}
		
		if( ( plen = vce_copy_cstring_upto(
			param, line, '=' , sizeof( param )) ) <= 0){
			continue;
		}
		vce_copy_cstring( value, sizeof( value ), line + plen );

		if( (ret = callback( (char*)filename, lineno, param,value)) < 0 ){
			fclose(fp);
			return ret;
		}
	}

	fclose(fp);
	return SET_LAST_ERROR(VCE_NOERROR);
}

int vce_read_plain_text_file( const char *filename, int (*callback) (char*,int,char*)) {
    char line[32768];
    int lineno;

    FILE *fp = fopen( filename, "r" );
    if( !fp ){
        return SET_LAST_ERROR(VCE_EACCESSFILE);
    }

    lineno = 0;
    while(fgets(line,sizeof(line),fp )){
        int ret;
        lineno++;
        
        if( line[0] == '\n'
            || ( line[0] == '\r' && line[1] == '\n' ) ){
            continue;
        }
        if( ( ret = callback( (char*)filename, lineno, line ))<0){
            fclose(fp);
            return ret;
        }
    }
    fclose(fp);
    return SET_LAST_ERROR(VCE_NOERROR);
}


void *VCEMALLOC( size_t size ) {
    void *p;
    p = vce_internal_malloc_func( size );
    VCE_ERROUT_V2( NOTE_UTIL_MALLOC_U_P, (int)size, p );
	SET_LAST_ERROR(0);
    return p;
}
void VCEFREE( void *p ) {
    VCE_ERROUT_V1( NOTE_UTIL_FREE_P, p );
    vce_internal_free_func(p);
	SET_LAST_ERROR(0);
}




// ipv4 の文字列 192.168.1.2 みたいのをNBバイト列から作る
char * vce_make_ipv4_dot_notation( const char *b, int len, char *work, int worklen ) {
	if( len != 4 ){
		vce_snprintf(work,worklen,"ERROR");
	} else {
		vce_snprintf( work,worklen,"%d.%d.%d.%d",
					  b[0] & 0xff, b[1] & 0xff,
					  b[2] & 0xff, b[3] & 0xff );
	}
	return work;
}

// ipv6 の文字列 0:0:0:134:143:8a:.. みたいのを16バイトの NB バイト列からつくる
char * vce_make_ipv6_dot_notation( const char *b, int len, char *work, int worklen ) {
	if( len != 16 ){
		vce_snprintf( work, worklen, "ERROR" );
	} else {
		int i;
		unsigned short nb_part[8];
		
		for(i=0;i<8;i++){
			unsigned char a,b;
			a = work[i*2];
			b = work[i*2+1];
			nb_part[i] = (a << 8) + b;
		}
		vce_snprintf( work, worklen, "%x:%x:%x:%x:%x:%x:%x:%x",
					  nb_part[0], nb_part[1], nb_part[2], nb_part[3],
					  nb_part[4], nb_part[5], nb_part[6], nb_part[7] );
	}
	return work;
}

void vce_replace_malloc_funcs( void* (*a)(size_t), void* (*r)(void*,size_t), void (*f)(void*)) {
    if(a){
        vce_internal_malloc_func = a;
    }
    if(r){
        vce_internal_realloc_func = r;
    }
    if(f){
        vce_internal_free_func = f;
    }

    //    vce_CRYPTO_set_mem_functions(
    //        vce_internal_malloc_func,
    //        vce_internal_realloc_func,
    //        vce_internal_free_func );

}

/*
  Locale の処理などを一切しない tolower. localeなどの処理は目的上
  まったく要らない。
  
*/
int tolower_direct( int c ) {
    switch( c ){
      case 'A': return 'a';
      case 'B': return 'b';
      case 'C': return 'c';
      case 'D': return 'd';
      case 'E': return 'e';
      case 'F': return 'f';
      case 'G': return 'g';
      case 'H': return 'h';
      case 'I': return 'i';
      case 'J': return 'j';
      case 'K': return 'k';
      case 'L': return 'l';
      case 'M': return 'm';
      case 'N': return 'n';
      case 'O': return 'o';
      case 'P': return 'p';        
      case 'Q': return 'q';
      case 'R': return 'r';
      case 'S': return 's';
      case 'T': return 't';
      case 'U': return 'u';
      case 'V': return 'v';
      case 'W': return 'w';                        
      case 'X': return 'x';
      case 'Y': return 'y';
      case 'Z': return 'z';
      default: return c;
    }
}

