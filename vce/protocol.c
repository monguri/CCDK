#include "vce.h"
#include "conn.h"
#include "protocol.h"
#include "vcecommon.h"



int vce_protocol_parser_bin16( conn_t ct ) {
    conn *c = ( conn *) ct.p;
    int datalen, contentlen, ret=0;
    char *data;

    vce_sbuf_get_buffer( &c->rb, &data, &datalen );
    if( datalen < 2 ) return SET_LAST_ERROR(0);
    contentlen = GET_16BIT_INT( data ) & 0xffff;
    /*
    レコード長の制限処理
    制限がしてあったら（１以上）ならレコード長を見て警告関数を呼ぶ。
    警告関数が設定してなければエラーを吐いて終わり。
    レコードの最初の２バイトで判断するので無駄に受信せずすばやい判断が可能
    */
    if(c->maxlen_record>=1&&
        contentlen > c->maxlen_record )
    {
        if(c->maxlen_warning)
        {
            if(c->maxlen_warning(ct)<0)
                return SET_LAST_ERROR(VCE_EPROTO_TOOLONG);
        }
        else
            return SET_LAST_ERROR(VCE_EPROTO_TOOLONG);
    }

    if( datalen < ( 2 + contentlen ) ) return SET_LAST_ERROR(0);
    if( c->pcallback ){
        ret = c->pcallback( ct, data + 2, contentlen );
    }
    vce_sbuf_shrink( &c->rb, NULL, contentlen + 2 );
    SET_LAST_ERROR(0);
    return ret;
}

int vce_protocol_parser_bin32( conn_t ct ) {
    conn *c = ( conn * ) ct.p;
    int datalen , ret = 0;
    unsigned int contentlen;
    char *data;
    vce_sbuf_get_buffer( &c->rb, &data, &datalen );
    
    if( datalen < 4 ) return SET_LAST_ERROR(0);
    if( datalen > BIN32DATA_MAX ) return SET_LAST_ERROR(VCE_EPROTO_TOOLONG);
    contentlen = GET_32BIT_INT( data ) & 0xffffffff;
    if( contentlen > BIN32DATA_MAX ) return SET_LAST_ERROR(VCE_EPROTO_TOOLONG);
    if( datalen < ( 4 + contentlen ) ) return SET_LAST_ERROR(0);
    if( c->pcallback ){
        ret = c->pcallback( ct, data + 4, contentlen );
    }
    vce_sbuf_shrink( &c->rb, NULL, contentlen + 4 );
    SET_LAST_ERROR(0);
    return ret;
}

int vce_protocol_parser_text( conn_t ct ) {
    conn *c = (conn*) ct.p;
    int datalen, ret = 0;
    char *data;
    int i;

    vce_sbuf_get_buffer( &c->rb, &data, &datalen );
    if( datalen < 1 ) return SET_LAST_ERROR(0);

    // 行がそろってるかみる 
    for(i=0;i<datalen;i++){
        if( data[i] == '\r' && data[i+1] == '\n' && (i<(datalen-1))){
            if( c->pcallback ){
                ret = c->pcallback( ct, data, i );
            }
            vce_sbuf_shrink( &c->rb, NULL, i+2 );
            SET_LAST_ERROR(0);
            return ret;
        } else if( data[i] == '\n' ){
            if( c->pcallback ){
                ret = c->pcallback( ct, data, i );
            }
            vce_sbuf_shrink( &c->rb, NULL, i+1 );
            SET_LAST_ERROR(0);
            return ret;
        }
    }
    return 0;
}

int vce_protocol_unparser_bin16( conn_t ct, char *data , int len  ) {
    int totallen;
    char work[2];
    int wable;

    if( !vce_conn_is_valid(ct) ) return SET_LAST_ERROR(VCE_EINVAL);

    /* 最初に全体の長さを求める */
    if( len > BIN16DATA_MAX ) return SET_LAST_ERROR(VCE_ELONGINPUT);
    totallen = 2 + len ;

    wable = vce_conn_writable(ct);
    if( wable < 0 ) return SET_LAST_ERROR(wable);

    if( totallen > wable ){
        return SET_LAST_ERROR( VCE_EWBFULL );
    }

    /* 2回書きこむ、エラーにならない(writableで調べてるから) */

    /* ヘッダをまず書きこむ */
    SET_16BIT_INT( work, len );
    vce_conn_write( ct, work, 2 );
    vce_conn_write( ct, data, len );

    SET_LAST_ERROR(0);
    return len+2;
}

int vce_protocol_unparser_bin32( conn_t ct, char *data, int len ) {
    int totallen,wable;
    char work[4];


    if( !vce_conn_is_valid(ct) ) return SET_LAST_ERROR(VCE_EINVAL);

    if( len > BIN32DATA_MAX ) return SET_LAST_ERROR(VCE_ELONGINPUT);
    totallen = 4 + len;

    wable = vce_conn_writable(ct);
    if( wable < 0 ) return SET_LAST_ERROR(wable);

    if( totallen > wable ){
        return SET_LAST_ERROR(VCE_EWBFULL);
    }
    SET_32BIT_INT(work, len);
    vce_conn_write( ct, work, 4 );
    vce_conn_write( ct, data, len );
    SET_LAST_ERROR(0);
    return len+4;
}

int vce_protocol_unparser_text( conn_t ct, char *data, int len ) {
    int totallen = len + 1;
    int rest = vce_conn_writable( ct );


    if( !vce_conn_is_valid(ct) ) return SET_LAST_ERROR(VCE_EINVAL);

    /* 残りが、改行の分もあるかみる */
    if( rest < 0 ) return SET_LAST_ERROR(rest);

    if( rest < totallen ) return SET_LAST_ERROR(VCE_EWBFULL);

    /* あるなら、2回書きこむ、そのほうがmemcpyより速いだろう */
    vce_conn_write( ct, data, len );
    vce_conn_write( ct, "\n", 1 );
    return totallen;
}

int vce_protocol_parser_through( conn_t ct ) {
    conn *c = (conn*) ct.p;
    char *data;
    int datalen , ret = 0;

    vce_sbuf_get_buffer( &c->rb, &data, &datalen );
    if( datalen > 0 ){
        ret = c->pcallback( ct, data , datalen );
    }
    vce_sbuf_shrink( &c->rb, NULL, datalen );
    SET_LAST_ERROR(0);
    return ret;
}
int vce_protocol_unparser_through( conn_t ct, char *data, int len) {
    if( !vce_conn_is_valid(ct) ) return SET_LAST_ERROR(VCE_EINVAL);

    return vce_conn_write( ct, data, len );
}

int vce_protocol_acceptwatcher_noop( conn_t c ) {
    return 0;
}
int vce_protocol_acceptwatcher_deny( conn_t c ) {
    return -1;
}
int vce_protocol_closewatcher_noop( conn_t c ) {
    return 0;
}


int vce_protocol_pcallback_echo_bin16( conn_t ct, char *data, int len ) {
	VCE_ERROUT1( "Echoing %d bytes\n", len );
	return vce_protocol_unparser_bin16( ct, data, len );
}
int vce_protocol_pcallback_echo_text( conn_t ct, char *data, int len ) {
	VCE_ERROUT1( "Echoing %d bytes\n", len );
	return vce_protocol_unparser_text( ct, data, len );
}
int vce_protocol_pcallback_noop( conn_t ct ,char *data , int len ) {
	VCE_ERROUT2( NOTE_NOOP_PROTOCOL_D_D, len, ct.serial );
	return 0;
}
int vce_protocol_pcallback_dump( conn_t ct, char *data, int len ) {
	VCE_ERROUT2( NOTE_DUMP_PROTOCOL_D_D,	len, ct.serial );
	vce_dump_buffer( data , len );
	VCE_ERROUT0( "\n" );
	return 0;
}


