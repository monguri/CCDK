/*

  バイナリpack/unpackルーチン。

  PACK された状態： [ ] は1個のデータ。1か2か4バイト。
  Ruby では組みこみの String::pack を使う。
  対応するようにせよ

  SINGLE_CHAR : [char]
  SINGLE_SHORT : [nb-short]
  SINGLE_INT : [nb-int]
  SINGLE_INT64 : [nb-int64]
  CHARARRAY_8 : [char][char]*n
  CHARARRAY_16 : [nb-short][char]*n
  CHARARRAY_32 : [nb-int][char]*n
  SHORTARRAY_8 : [char][short]*n
  SHORTARRAY_16 : [nb-short][nb-short]*n
  SHORTARRAY_32 : [nb-int][nb-short]*n
  INTARRAY_8 : [char][nb-int]*n
  INTARRAY_16 : [nb-short][nb-int]*n
  INTARRAY_32 : [nb-int][nb-int]*n
  INT64ARRAY_8 : [char][nb-int64]*n
  INT64ARRAY_16 : [nb-short][nb-int64]*n
  INT64ARRAY_32 : [nb-int][nb-int64]*n
  STRARRAY_8 : [char][ C-STRING ]*n
  STRARRAY_16 : [nb-short][ C-STRING ]*n

  
 */

#include "vce.h"
#include "vcecommon.h"

/* 32ビット長配列のときに、この要素を越えたらエラーとする */
#define MAXUNITLEN (1024*1024*16)


int vce_binary_unpack( struct bin_info *bi, int bn, char *inp, int len ) {
    int i;
    unsigned int so_far = 0;
    
    /* test phase */
    for(i=0;i<bn;i++){
        unsigned int rest = len - so_far;
        switch( bi[i].t ){
          case SINGLE_CHAR:
            if( rest < 1 ) return SET_LAST_ERROR( VCE_EDATASHORT );
            SET_8BIT_NATIVEINT( bi[i].p, GET_8BIT_INT(&inp[so_far]) );
            so_far += 1;
            break;
          case SINGLE_SHORT:
            if( rest < 2 ) return SET_LAST_ERROR( VCE_EDATASHORT );
            SET_16BIT_NATIVEINT( bi[i].p, GET_16BIT_INT(&inp[so_far]) );
            so_far += 2;
            break;
          case SINGLE_INT:
            if( rest < 4 ) return SET_LAST_ERROR( VCE_EDATASHORT );
            SET_32BIT_NATIVEINT( bi[i].p, GET_32BIT_INT(&inp[so_far]) );
			so_far += 4;
            break;
          case SINGLE_INT64:
            if( rest < 8 ) return SET_LAST_ERROR( VCE_EDATASHORT );
            SET_64BIT_NATIVEINT( bi[i].p, GET_64BIT_INT(&inp[so_far]) );
			so_far += 8;
            break;
          case CHARARRAY_8:
            if( rest < 1 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                unsigned char dl = (unsigned char) inp[so_far];
                if( dl > bi[i].maxu ) return SET_LAST_ERROR(VCE_ELENTOOLONG);
                if( rest < ((unsigned int)dl+1) ) return SET_LAST_ERROR(VCE_EDATASHORT);
                so_far += 1;
                memcpy( bi[i].p, inp+so_far, dl );
                so_far += dl;
                bi[i].n = dl;
            }
            break;
          case CHARARRAY_16:
            if( rest < 2 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                unsigned short dl = GET_16BIT_INT( &inp[so_far] );
                if( dl > bi[i].maxu ) return SET_LAST_ERROR( VCE_ELENTOOLONG );
                if( rest < ((unsigned int)dl+2) ) return SET_LAST_ERROR(VCE_EDATASHORT);
                so_far += 2;
                memcpy( bi[i].p, inp+so_far , dl );
                so_far += dl;
                bi[i].n = dl;
            }
            break;
                    
          case CHARARRAY_32:
            if( rest < 4 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                unsigned int dl = GET_32BIT_INT( &inp[so_far] );
                if( dl > bi[i].maxu ) return SET_LAST_ERROR(VCE_ELENTOOLONG);
                if( dl > MAXUNITLEN ) return SET_LAST_ERROR(VCE_ELENTOOLONG);
                if( rest < (dl+4) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 4;
                memcpy( bi[i].p, inp+so_far, dl );
                so_far += dl;
                bi[i].n = dl;                
            }
            break;
          case SHORTARRAY_8:
            if( rest < 1 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned char dl = inp[so_far];
                if( dl > bi[i].maxu ) return SET_LAST_ERROR(VCE_ELENTOOLONG );
                if( rest < ((unsigned int)dl+1) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 1;
                for(j=0;j<dl;j++){
                    short v = GET_16BIT_INT( &inp[so_far+j*2] );
                    SET_16BIT_NATIVEINT( (char*)(bi[i].p) + j*2, v);
                }
                so_far += dl*2;
                bi[i].n = dl;                
            }
            break;
          case SHORTARRAY_16:
            if( rest < 2 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned short dl = GET_16BIT_INT( &inp[so_far] );
                if( rest < ((unsigned int)dl+2) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 2;
                for(j=0;j<dl;j++){
                    short v = GET_16BIT_INT( &inp[so_far+j*2] );
                    SET_16BIT_NATIVEINT((char*)(bi[i].p) + j*2, v );
                }
                so_far += dl*2;
                bi[i].n = dl;                
            }
            break;
          case SHORTARRAY_32:
            if( rest < 4 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned int dl = GET_32BIT_INT( &inp[so_far] );
                if( rest > MAXUNITLEN ) return SET_LAST_ERROR(VCE_ELENTOOLONG);
                if( rest < (dl+4 ) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 4;
                for(j=0;j<(int)dl;j++){
                    short v = GET_16BIT_INT( &inp[so_far+j*2] );
                    SET_16BIT_NATIVEINT( (char*)(bi[i].p) + j*2, v );
                }
                so_far += dl*2;
                bi[i].n = dl;                
            }                
            break;
          case INTARRAY_8:
            if( rest < 1 ) {
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned char dl = inp[so_far];
                if( dl > bi[i].maxu ) return SET_LAST_ERROR( VCE_ELENTOOLONG );
                if( rest < ((unsigned int)dl+1)) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 1;
                for(j=0;j<dl;j++){
                    int v = GET_32BIT_INT( &inp[so_far+j*4] );
                    SET_32BIT_NATIVEINT( (char*)(bi[i].p) +j*4, v );
                }
                so_far += dl*4;
                bi[i].n = dl;                
            }
            break;
          case INTARRAY_16:
            if( rest < 2 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned short dl = GET_16BIT_INT( &inp[so_far] );
                if( rest < ((unsigned int)dl+2) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 2;
                for(j=0;j<dl;j++){
                    int v = GET_32BIT_INT( &inp[so_far+j*4] );
                    SET_32BIT_NATIVEINT( (char*)(bi[i].p)+j*4,v );
                }
                so_far += dl*4;
                bi[i].n = dl;                
            }
            break;
          case INTARRAY_32:
            if( rest < 4 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned int dl = GET_32BIT_INT( &inp[so_far] );
                if( dl > bi[i].maxu ) return SET_LAST_ERROR( VCE_ELENTOOLONG );
                if( dl > MAXUNITLEN ) return SET_LAST_ERROR(VCE_ELENTOOLONG );
                if( rest < (dl+4)) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 4;
                for(j=0;j<(int)dl;j++){
                    int v = GET_32BIT_INT( &inp[so_far+j*4] );
                    SET_32BIT_NATIVEINT( (char*)(bi[i].p)+j*4, v );
                }
                so_far += dl*4;
                bi[i].n = dl;                
            }
            break;
          case INT64ARRAY_8:
            if( rest < 1 ) {
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned char dl = inp[so_far];
                if( dl > bi[i].maxu ) return SET_LAST_ERROR( VCE_ELENTOOLONG );
                if( rest < ((unsigned int)dl+1)) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 1;
                for(j=0;j<(int)dl;j++){
                    VCEI64 v = GET_64BIT_INT( &inp[so_far+j*8] );
                    SET_64BIT_NATIVEINT( (char*)(bi[i].p) +j*8, v );
                }
                so_far += dl*8;
                bi[i].n = dl;                
            }
            break;
          case INT64ARRAY_16:
            if( rest < 2 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned short dl = GET_16BIT_INT( &inp[so_far] );
                if( rest < ((unsigned int)dl+2) ) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 2;
                for(j=0;j<(int)dl;j++){
                    VCEI64 v = GET_64BIT_INT( &inp[so_far+j*8] );
                    SET_64BIT_NATIVEINT( (char*)(bi[i].p)+j*8,v );
                }
                so_far += dl*8;
                bi[i].n = dl;                
            }
            break;
          case INT64ARRAY_32:
            if( rest < 4 ){
                return SET_LAST_ERROR( VCE_EDATASHORT );
            } else {
                int j;
                unsigned int dl = GET_32BIT_INT( &inp[so_far] );
                if( dl > bi[i].maxu ) return SET_LAST_ERROR( VCE_ELENTOOLONG );
                if( dl > MAXUNITLEN ) return SET_LAST_ERROR(VCE_ELENTOOLONG );
                if( rest < (dl+4)) return SET_LAST_ERROR( VCE_EDATASHORT );
                so_far += 4;
                for(j=0;j<(int)dl;j++){
                    VCEI64 v = GET_64BIT_INT( &inp[so_far+j*8] );
                    SET_64BIT_NATIVEINT( (char*)(bi[i].p)+j*8, v );
                }
                so_far += dl*8;
                bi[i].n = dl;                
            }
            break;
		  case STRARRAY_8:
			if( rest < 1 ){
				return SET_LAST_ERROR( VCE_EDATASHORT );
			} else {
				unsigned int scanner,strcount;
				unsigned int dl = GET_8BIT_INT( &inp[so_far] );
				if( dl > bi[i].maxu ) return SET_LAST_ERROR(VCE_ELENTOOLONG );
				if( rest < dl + 1 ) return SET_LAST_ERROR( VCE_EDATASHORT );
				so_far += 1;
				strcount = 0;
				((char**)(bi[i].p))[0] = &inp[so_far];
				for(scanner=0;(scanner+1)<rest;scanner++){
					/* データの1文字目から順に見ていくスキャナ */
					if( rest < (scanner + 1) ){
						return SET_LAST_ERROR(VCE_EDATASHORT);
					}
					if( strcount == dl )break;

					if( inp[so_far+scanner] == '\0' ){
						((char**)(bi[i].p))[strcount+1] =
							&inp[so_far+scanner+1];
						strcount++;
					}
				}
				bi[i].n = strcount;
				so_far += scanner ;
			}
			break;
		  case STRARRAY_16:
			if( rest < 2 ){
				return SET_LAST_ERROR( VCE_EDATASHORT );
			} else {
				unsigned int scanner, strcount;
				unsigned int dl = GET_16BIT_INT( &inp[so_far] );
				if( dl > bi[i].maxu ) return SET_LAST_ERROR(VCE_ELENTOOLONG );
				if( rest < dl+2 )return SET_LAST_ERROR(VCE_EDATASHORT);
				so_far += 2;
				strcount = 0;
				((char**)(bi[i].p))[0] = &inp[so_far];
				for(scanner=0;(scanner+1)<rest;scanner++){
					if( rest < (scanner +1 ) ){
						return SET_LAST_ERROR(VCE_EDATASHORT);
					}
					if( strcount == dl)break;
					if( inp[so_far+scanner] == '\0' ){
						((char**)(bi[i].p))[strcount+1] =
							&inp[so_far+scanner+1];
						strcount++;
					}
				}
				bi[i].n= strcount;
				so_far += scanner ;
			}
			break;
          default:
            return SET_LAST_ERROR( VCE_EINVAL );
            break;
        }
    }
	SET_LAST_ERROR(VCE_NOERROR);
    return so_far;
}

int vce_binary_pack( struct bin_info *bi, int bn, char *outp, int len ) {
    int i,j;
    unsigned int so_far = 0;

    for(i=0;i<bn;i++){
        unsigned int rest = len - so_far;
        switch( bi[i].t ){
          case SINGLE_CHAR:
            if( rest < 1 ) return SET_LAST_ERROR( VCE_EFULL );
            SET_8BIT_INT( &outp[so_far], GET_8BIT_NATIVEINT(bi[i].p));
            so_far += 1;
            break;
          case SINGLE_SHORT:
            if( rest < 2 ) return SET_LAST_ERROR( VCE_EFULL );
            SET_16BIT_INT( &outp[so_far], GET_16BIT_NATIVEINT(bi[i].p));
            so_far += 2;
            break;
          case SINGLE_INT:
            if( rest < 4 ) return SET_LAST_ERROR( VCE_EFULL );
            SET_32BIT_INT( &outp[so_far], GET_32BIT_NATIVEINT(bi[i].p));
            so_far += 4;
            break;
          case SINGLE_INT64:
            if( rest < 8 ) return SET_LAST_ERROR( VCE_EFULL );
            SET_64BIT_INT( &outp[so_far], GET_64BIT_NATIVEINT(bi[i].p));
            so_far += 8;
            break;
            
          case CHARARRAY_8:
            if( bi[i].n > 255 ) return SET_LAST_ERROR( VCE_EINVAL );
            if( rest < ( 1 + bi[i].n ) ) return SET_LAST_ERROR(VCE_EFULL);
            SET_8BIT_INT( &outp[so_far], bi[i].n );
            so_far += 1;
            memcpy( &outp[so_far], bi[i].p, bi[i].n );
            so_far += bi[i].n;
            break;
            
          case CHARARRAY_16:
            if( bi[i].n > 65535 ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < ( 2+bi[i].n) ) return SET_LAST_ERROR(VCE_EFULL);
            SET_16BIT_INT( &outp[so_far], bi[i].n );
            so_far += 2;
            memcpy( &outp[so_far],bi[i].p, bi[i].n );
            so_far += bi[i].n;
            break;
            
          case CHARARRAY_32:
            if( bi[i].n > MAXUNITLEN ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (2+bi[i].n)) return SET_LAST_ERROR(VCE_EFULL );
            so_far += 4;
            memcpy( &outp[so_far], bi[i].p, bi[i].n );
            so_far += bi[i].n;
            break;
            
          case SHORTARRAY_8:
            if( bi[i].n > 255 ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (1+bi[i].n*2) ) return SET_LAST_ERROR(VCE_EFULL);
            SET_8BIT_INT( &outp[so_far], bi[i].n );
            so_far += 1;
            for(j=0;j<(int)bi[i].n;j++){
                short v = GET_16BIT_NATIVEINT( (char*)(bi[i].p) + j*2 );
                SET_16BIT_INT( &outp[so_far], v );
                so_far += 2;
            }
            break;
            
          case SHORTARRAY_16:
            if( bi[i].n > 65535 ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (2+bi[i].n*2) ) return SET_LAST_ERROR(VCE_EFULL);
            SET_16BIT_INT( &outp[so_far] , bi[i].n );
            so_far += 2;
            for(j=0;j<(int)bi[i].n;j++){
                short v = GET_16BIT_NATIVEINT( (char*)(bi[i].p) + j*2 );
                SET_16BIT_INT( &outp[so_far] , v );
                so_far += 2;
            }
            break;
                                           
          case SHORTARRAY_32:
            if( bi[i].n > MAXUNITLEN ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (4+bi[i].n*2) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_32BIT_INT( &outp[so_far], bi[i].n );
            so_far += 4;
            for(j=0;j<(int)bi[i].n;j++){
                short v = GET_16BIT_NATIVEINT( (char*)(bi[i].p) + j*2 );
                SET_16BIT_INT( &outp[so_far] , v );
                so_far += 2;
            }
            break;
          case INTARRAY_8:
            if( bi[i].n > 255 ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (1+bi[i].n*4) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_8BIT_INT( &outp[so_far] , bi[i].n );
            so_far += 1;
            for(j=0;j<(int)bi[i].n;j++){
                int v = GET_32BIT_NATIVEINT( (char*)(bi[i].p) + j*4 );
                SET_32BIT_INT( &outp[so_far],v );
                so_far += 4;
            }
            break;
            
          case INTARRAY_16:
            if( bi[i].n > 65535 ) return SET_LAST_ERROR( VCE_EINVAL);
            if( rest < (2+bi[i].n*4 ) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_16BIT_INT( &outp[so_far], bi[i].n );
            so_far += 2;
            for(j=0;j<(int)bi[i].n;j++){
                int v = GET_32BIT_NATIVEINT( (char*)(bi[i].p) + j*4  );
                SET_32BIT_INT( &outp[so_far],v );
                so_far += 4;
            }
            break;
            
          case INTARRAY_32:
            if( bi[i].n > MAXUNITLEN ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (4+bi[i].n*4 ) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_32BIT_INT( &outp[so_far], bi[i].n );			
            so_far += 4;
            for(j=0;j<(int)bi[i].n; j++ ){
                int v = GET_32BIT_NATIVEINT( (char*)(bi[i].p) + j*4 );
                SET_32BIT_INT( &outp[so_far],v);
                so_far += 4;
            }
            break;

          case INT64ARRAY_8:
            if( bi[i].n > 255 ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (1+bi[i].n*8) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_8BIT_INT( &outp[so_far] , bi[i].n );
            so_far += 1;
            for(j=0;j<(int)bi[i].n;j++){
                VCEI64 v = GET_64BIT_NATIVEINT( (char*)(bi[i].p) + j*8 );
                SET_64BIT_INT( &outp[so_far],v );
                so_far += 8;
            }
            break;
            
          case INT64ARRAY_16:
            if( bi[i].n > 65535 ) return SET_LAST_ERROR( VCE_EINVAL);
            if( rest < (2+bi[i].n*8 ) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_16BIT_INT( &outp[so_far], bi[i].n );
            so_far += 2;
            for(j=0;j<(int)bi[i].n;j++){
                VCEI64 v = GET_64BIT_NATIVEINT( (char*)(bi[i].p) + j*8  );
                SET_64BIT_INT( &outp[so_far],v );
                so_far += 8;
            }
            break;
            
          case INT64ARRAY_32:
            if( bi[i].n > MAXUNITLEN ) return SET_LAST_ERROR(VCE_EINVAL);
            if( rest < (4+bi[i].n*8 ) ) return SET_LAST_ERROR(VCE_EFULL);
			SET_32BIT_INT( &outp[so_far], bi[i].n );			
            so_far += 4;
            for(j=0;j<(int)bi[i].n; j++ ){
                VCEI64 v = GET_64BIT_NATIVEINT( (char*)(bi[i].p) + j*8 );
                SET_64BIT_INT( &outp[so_far],v);
                so_far += 8;
            }
            break;

		  case STRARRAY_8:
			if( bi[i].n >255 ) return SET_LAST_ERROR(VCE_EINVAL);
			if( rest < 1 + bi[i].n ){
				/* char と、個数分のnull文字は最低必要やね */
				return SET_LAST_ERROR(VCE_EFULL);
			} else {
				unsigned int strtotal;
				SET_8BIT_INT( &outp[so_far], bi[i].n );
				so_far += 1;
				strtotal = 1; /* 先頭の1バイト、個数ね */
				for(j=0;j<(int)bi[i].n;j++){
					int l = vce_strlenmax( ((char**)(bi[i].p))[j],
										   rest - so_far );
					if( l<0) return SET_LAST_ERROR(VCE_EFULL);
					strtotal += l+1;
					if( rest < strtotal ) return SET_LAST_ERROR(VCE_EFULL);
					memcpy( &outp[so_far], ((char**)(bi[i].p))[j],l+1 );
					so_far += l+1;
				}
			}
			break;
		  case STRARRAY_16:
			if( bi[i].n > 65535 ) return SET_LAST_ERROR(VCE_EINVAL);
			if( rest < (2 +bi[i].n ) ){
				return SET_LAST_ERROR(VCE_EFULL);
			} else {
				unsigned int strtotal;
				SET_16BIT_INT(&outp[so_far], bi[i].n );
				so_far += 2;
				strtotal = 2; /* 個数がshortだから */
				for(j=0;j<(int)bi[i].n;j++){
					int l = vce_strlenmax( ((char**)(bi[i].p))[j],
										   rest - so_far );
					if( l < 0 ) return SET_LAST_ERROR(VCE_EFULL);
					strtotal += l+1;
					if( rest < strtotal ) return SET_LAST_ERROR(VCE_EFULL);
					memcpy( &outp[so_far], ((char**)(bi[i].p))[j],l+1);
					so_far += l+1;
				}
			}
			break;

          default:
            return SET_LAST_ERROR( VCE_EINVAL );
            break;
        }
    }
	SET_LAST_ERROR(VCE_NOERROR);
    return so_far;
}

/*
  可変長長さ指定子を初期化する。

  仕様
  
	  0x00 - 0xfc : うしろは0バイト。そのまま長さをあらわす
	  0xfd : うしろは4バイト。その4バイトで長さをあらわす(network-order)
	  0xfe : うしろは8バイト。その8バイト(network-order)で長さをあらわす
	  0xff : 帯域外データ(予約)

  この関数は非公開
  out に 0 を指定すると、長さだけ取れる
 */
int vce_set_variable_length_specifier( char *out, int outmax, unsigned int len_upper, unsigned int len_lower ) {
	if( len_upper == 0 ){
		if( len_lower <= 0xfc ){
			if(out){
				if( outmax < 1 ) return SET_LAST_ERROR(VCE_EFULL);
				out[0] = (unsigned char)len_lower;
			}
			return 1;
		} else {
			if(out){
				if( outmax < (1+4) ) return SET_LAST_ERROR(VCE_EFULL);
				out[0] = 0xfd;
				SET_32BIT_INT(out+1, len_lower);
			}
			return 1+4;
		}
	} else {
		if(out){		
			if( outmax < (1+8) ) return SET_LAST_ERROR(VCE_EFULL);
			out[0] = 0xfe;
			SET_32BIT_INT(out+1,len_upper);
			SET_32BIT_INT(out+1+4,len_lower);
		}
		return 1 + 8;
	}
	/* not reached */
	return SET_LAST_ERROR(VCE_EBUG);
}
/* とりだす   この関数は非公開  */
int vce_get_variable_length_specifier( const char *src, int srcmax, unsigned int *len_upper, unsigned int *len_lower ) {
	unsigned char top;
	if( srcmax < 1 ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	top = src[0];

	if( top <= 0xfc ){
		*len_upper = 0;
		*len_lower = GET_8BIT_INT( src ) & 0xff; 
		return 1;
	} else if( top == 0xfd ){
		if( srcmax < (1+4)) return SET_LAST_ERROR(VCE_ETOOSHORT);
		*len_upper = 0;
		*len_lower = GET_32BIT_INT( src+1);
		return 1+4;
	} else if( top == 0xfe ){
		if( srcmax < (1+8)) return SET_LAST_ERROR(VCE_ETOOSHORT);
		*len_upper = GET_32BIT_INT(src+1);
		*len_lower = GET_32BIT_INT(src+1+4);
		return 1+8;
		return SET_LAST_ERROR(VCE_NOERROR);
	} else if( top == 0xff ){
		*len_lower = *len_upper = 0;
		return SET_LAST_ERROR(VCE_ESUPPORT);
	}
	/* not reached */
	return SET_LAST_ERROR(VCE_EBUG);
}

int vce_binary_push_nb_i1( char *out, int ofs, int maxlen, char c ) {
	if( (ofs+1) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);
	SET_8BIT_INT( out + ofs, c );
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 1;
}

int vce_binary_push_nb_i2( char *out, int ofs, int maxlen, short s ) {
	if( (ofs+2) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);
	SET_16BIT_INT(out + ofs,s);
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 2;
}

int vce_binary_push_nb_i4( char *out, int ofs, int maxlen, int i ) {
	if( (ofs+4) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);
	SET_32BIT_INT(out + ofs,i);
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 4;
}

int vce_binary_push_nb_i8( char *out, int ofs, int maxlen, VCEI64 i ) {
	if( (ofs+8) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);
	SET_64BIT_INT(out + ofs,i);
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 8;
}

int vce_binary_push_nb_ia1( char *out, int ofs, int maxlen, const void *ia, int num ) {
	int headlen,i;
	char lenwork[10];

    if(num<0) return SET_LAST_ERROR(VCE_EINVAL);
	headlen = vce_set_variable_length_specifier(lenwork,sizeof(lenwork),
												0,num );
	if( headlen < 0 ) return headlen;
	
	if( ( ofs + headlen + num ) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);

	for(i=0;i<num;i++){
		out[ ofs + headlen + i ] = ((char*)ia)[i];
	}
	memcpy( out + ofs, lenwork, headlen );
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + headlen + num;
}

int vce_binary_push_nb_ia2( char *out, int ofs, int maxlen, const void *ia, int num ) {
	int headlen,i;
	char lenwork[10];
    if(num<0)return SET_LAST_ERROR(VCE_EINVAL);
	headlen = vce_set_variable_length_specifier( lenwork, sizeof(lenwork),
												 0,num);
	
	if( ( ofs + num*2 + headlen ) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);

	for(i=0;i<num;i++){
		SET_16BIT_INT( out + ofs + headlen + i*2 , ((short*)ia)[i] );
	}
	memcpy( out + ofs, lenwork, headlen );
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + headlen + num*2;
}

int vce_binary_push_nb_ia4( char *out, int ofs, int maxlen, const void *ia, int num ) {
	int headlen,i;
	char lenwork[10];
    if(num<0)return SET_LAST_ERROR(VCE_EINVAL);
	headlen = vce_set_variable_length_specifier( lenwork,sizeof(lenwork),
												 0,num );
	if( ( ofs + headlen + num*4 ) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);

	for(i=0;i<num;i++){
		SET_32BIT_INT( out + ofs + headlen + i*4, ((int*)ia)[i] );
	}
	memcpy( out + ofs, lenwork, headlen );
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + headlen + num*4;
}

int vce_binary_push_nb_ia8( char *out, int ofs, int maxlen, const void *ia, int num ) {
	int headlen,i;
	char lenwork[10];
    if(num<0)return SET_LAST_ERROR(VCE_EINVAL);
	headlen = vce_set_variable_length_specifier( lenwork,sizeof(lenwork),
												 0,num );
	if( ( ofs + headlen + num*8 ) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);

	for(i=0;i<num;i++){
		SET_64BIT_INT( out + ofs + headlen + i*8, ((VCEI64*)ia)[i]);
	}
	memcpy( out + ofs, lenwork, headlen );
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + headlen + num*8;
}

/*
  フォーマット:
  [VARLEN(string num)][ STRING ][ STRING ]...

  STRING : [VARLEN][data]

  eachmax : 各文字列の最大長。
  この長さ以上の文字列があると失敗する。勝手に truncate しない。
  ヌル文字なし。

 */
int vce_binary_push_nb_stra( char *out, int ofs, int maxlen, const char * const *stra, int num, int eachmax ) {
	int headlen,i,total_l;
	char lenwork[10];

    if(num<0)return SET_LAST_ERROR(VCE_EINVAL);
	headlen = vce_set_variable_length_specifier( lenwork,sizeof(lenwork),
												 0,num);
	if( (ofs+headlen) > maxlen ) return SET_LAST_ERROR(VCE_EFULL);

	memcpy( out + ofs, lenwork, headlen );

	total_l = ofs + headlen;
	for(i=0;i<num;i++){
		char slenwork[10];
		char sheadlen;
		int sl = vce_strlenmax( stra[i], eachmax );
		if( sl <0 ) return SET_LAST_ERROR(VCE_EFULL);
		sheadlen = vce_set_variable_length_specifier( slenwork,
													  sizeof(slenwork),
													  0,sl);		
		if( (total_l+sheadlen+sl) >= maxlen ) return SET_LAST_ERROR(VCE_EFULL);

		memcpy( out + total_l , slenwork, sheadlen );
		memcpy( out + total_l + sheadlen , stra[i], sl );
		total_l += sheadlen + sl;
	}
    SET_LAST_ERROR(VCE_NOERROR);
	return total_l;
}

int vce_binary_pop_nb_i1( const char *in, int len, int ofs, char *out) {
	if( ofs >= len ) return SET_LAST_ERROR(VCE_EFULL);
	*out = GET_8BIT_INT( in + ofs );
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + 1;
}

int vce_binary_pop_nb_i2( const char *in, int len, int ofs, short *out ) {
	if( ofs > (len-2) )return SET_LAST_ERROR(VCE_EFULL);
	*out = GET_16BIT_INT( in + ofs );
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 2;
}

int vce_binary_pop_nb_i4( const char *in, int len, int ofs, int *out ) {
	if( ofs > (len-4)) return SET_LAST_ERROR(VCE_EFULL);
	*out = GET_32BIT_INT( in + ofs );
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 4;
}

int vce_binary_pop_nb_i8( const char *in, int len, int ofs, VCEI64 *out ) {
	if( ofs > (len-8)) return SET_LAST_ERROR(VCE_EFULL);
	*out = GET_64BIT_INT( in + ofs );
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + 8;
}

int vce_binary_pop_nb_ia1( const char *src, int len, int ofs, char *out, int *outlen ) {
	int headlen, available = len - ofs;
	unsigned int lu,ll;
	headlen = vce_get_variable_length_specifier( src + ofs, available,
												 &lu,&ll );
	if( headlen < 0 ) return SET_LAST_ERROR(headlen);
	if( lu ) return SET_LAST_ERROR(VCE_ESUPPORT);
	if( (headlen+ll) > available ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	if( ll > *outlen ) return SET_LAST_ERROR(VCE_EFULL);

	memcpy( out, src + ofs + headlen, ll );
	*outlen = ll;
	
    SET_LAST_ERROR(VCE_NOERROR);
	return ofs + headlen + ll;
}

int vce_binary_pop_nb_ia2( const char *src, int len, int ofs, short *out, int *outlen ) {
	int headlen, available = len - ofs,i;
	unsigned int lu,ll;
	headlen = vce_get_variable_length_specifier( src + ofs, available,
												 &lu, &ll );
	if( headlen < 0 ) return SET_LAST_ERROR(headlen);
	if( lu ) return SET_LAST_ERROR(VCE_ESUPPORT);
	if( (headlen+ll*2) > available ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	if( ll > *outlen ) return SET_LAST_ERROR(VCE_EFULL);

	for(i=0;i<ll;i++){
		out[i] = GET_16BIT_INT( src + ofs + headlen + i*2);
	}
	*outlen = ll;
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + headlen + ll*2;
}

int vce_binary_pop_nb_ia4( const char *src, int len, int ofs, int *out, int *outlen ) {
	int headlen, available = len - ofs , i;
	unsigned int lu,ll;
	headlen = vce_get_variable_length_specifier( src + ofs, available,
												 &lu, &ll );
	if( headlen < 0 ) return SET_LAST_ERROR(headlen);
	if( lu ) return SET_LAST_ERROR(VCE_ESUPPORT);
	if( (headlen+ll*4) > available ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	if( ll > *outlen ) return SET_LAST_ERROR(VCE_EFULL);
	for(i=0;i<ll;i++){
		out[i] = GET_32BIT_INT( src +ofs + headlen + i*4 );
	}
	*outlen = ll;
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + headlen + ll*4;
}

int vce_binary_pop_nb_ia8( const char *src, int len, int ofs, VCEI64 *out, int *outlen ) {
	int headlen, available = len - ofs , i;
	unsigned int lu,ll;
	headlen = vce_get_variable_length_specifier( src + ofs, available,
												 &lu, &ll );
	if( headlen < 0 ) return SET_LAST_ERROR(headlen);
	if( lu ) return SET_LAST_ERROR(VCE_ESUPPORT);
	if( (headlen+ll*8) > available ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	if( ll > *outlen ) return SET_LAST_ERROR(VCE_EFULL);
	for(i=0;i<ll;i++){
		out[i] = GET_64BIT_INT( src +ofs + headlen + i*8 );
	}
	*outlen = ll;
    SET_LAST_ERROR(VCE_NOERROR);    
	return ofs + headlen + ll*8;
}

  
int vce_binary_pop_nb_stra( const char *src, int len, int ofs, char **out, int *strnum, int eachmax ) {
	int headlen, available = len - ofs;
	int i,total_l;
	unsigned int lu,ll;

	headlen = vce_get_variable_length_specifier( src + ofs, available,
												 &lu, &ll );
	if( headlen < 0 ) return SET_LAST_ERROR(headlen);
	if( lu ) return SET_LAST_ERROR(VCE_ESUPPORT);
	if( *strnum < ll ){
		return SET_LAST_ERROR(VCE_EFULL);
	}

	total_l = ofs + headlen;
	for(i=0;i<ll;i++){
		unsigned int slu, sll;
		int sheadlen;

		sheadlen = vce_get_variable_length_specifier( src + total_l,
													  len - total_l,
													  &slu, &sll );
		if( slu ) return SET_LAST_ERROR(VCE_ESUPPORT);
		if( sll > (eachmax-1) ){
			return SET_LAST_ERROR(VCE_EFULL);
		}

		memcpy( out[i], src + total_l + sheadlen, sll );
		out[i][sll] = 0; /* null byte */
		total_l += sheadlen + sll;
	}
	*strnum = ll;
    SET_LAST_ERROR(VCE_NOERROR);
	return total_l;
}
