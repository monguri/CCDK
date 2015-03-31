#include "vce.h"
#include "vcecommon.h"

char * vce_strerror( int ecode ) {
	switch ( ecode ){
    case VCE_NOERROR : return STRDEF_EMESG_NOERROR;
    case VCE_EGENERIC : return STRDEF_EMESG_EGENERIC;
    case VCE_EFULL  :  return  STRDEF_EMESG_EFULL;
    case VCE_EBUG   :  return  STRDEF_EMESG_EBUG;
    case VCE_ERANGE :  return  STRDEF_EMESG_ERANGE;
    case VCE_EINVAL :  return  STRDEF_EMESG_EINVAL;
    case VCE_EMEM   :  return  STRDEF_EMESG_EMEM;
    case VCE_ENOENT :  return  STRDEF_EMESG_ENOENT;
    case VCE_EIO    :  return  STRDEF_EMESG_EIO;
    case VCE_ESOCKET :  return  STRDEF_EMESG_ESOCKET;
    case VCE_EBIND :  return  STRDEF_EMESG_EBIND;
    case VCE_EIPADDR :  return  STRDEF_EMESG_EIPADDR;
    case VCE_ELISTEN :  return  STRDEF_EMESG_ELISTEN;
    case VCE_ECONFIG :  return  STRDEF_EMESG_ECONFIG;
    case VCE_EHOSTNAME :  return  STRDEF_EMESG_EHOSTNAME;
    case VCE_EFCNTL :  return  STRDEF_EMESG_EFCNTL;
    case VCE_ECONNECT :  return  STRDEF_EMESG_ECONNECT;
    case VCE_EBUFSMALL :  return  STRDEF_EMESG_EBUFSMALL;
    case VCE_EPROTO    :  return  STRDEF_EMESG_EPROTO;
    case VCE_ENOTREADY :  return  STRDEF_EMESG_ENOTREADY;
    case VCE_ENEGO    :  return  STRDEF_EMESG_ENEGO;
    case VCE_EPROTO_INVAL :  return  STRDEF_EMESG_EPROTO_INVAL;
    case VCE_EPROTO_ODD :  return  STRDEF_EMESG_EPROTO_ODD;
    case VCE_EPROTO_TOOLONG :  return  STRDEF_EMESG_EPROTO_TOOLONG;
    case VCE_ENOCALLBACK :  return  STRDEF_EMESG_ENOCALLBACK;
    case VCE_ESUPPORT  :  return  STRDEF_EMESG_ESUPPORT;
    case VCE_ECONNSERIAL :  return  STRDEF_EMESG_ECONNSERIAL;
    case VCE_EALIGNMENT :  return  STRDEF_EMESG_EALIGNMENT;
    case VCE_EFORMAT :  return  STRDEF_EMESG_EFORMAT;
    case VCE_ESEARCH :  return  STRDEF_EMESG_ESEARCH;
    case VCE_ECONTENTLEN :  return  STRDEF_EMESG_ECONTENTLEN;
    case VCE_ECONNINIT :  return  STRDEF_EMESG_ECONNINIT;
    case VCE_EBADKEYLEN :  return  STRDEF_EMESG_EBADKEYLEN;
    case VCE_EACCEPT :  return  STRDEF_EMESG_EACCEPT;
    case VCE_ESETSOCKOPT :  return  STRDEF_EMESG_ESETSOCKOPT;
    case VCE_EACCESSFILE :  return STRDEF_EMESG_EACCESSFILE;
    case VCE_EWINSOCKINIT : return STRDEF_EMESG_EWINSOCKINIT;
    case VCE_EWBFULL: return STRDEF_EMESG_EWBFULL;
    case VCE_ELONGINPUT: return STRDEF_EMESG_ELONGINPUT;
    case VCE_ETOOSHORT: return STRDEF_EMESG_ETOOSHORT;
    case VCE_EPROTO_BADLEN: return STRDEF_EMESG_EPROTO_BADLEN;
    case VCE_EPROTO_RESULT: return STRDEF_EMESG_EPROTO_RESULT;
    case VCE_EPROTO_SERVERINVAL: return STRDEF_EMESG_EPROTO_SERVERINVAL;
    case VCE_EPROTO_BADCOMMAND: return STRDEF_EMESG_EPROTO_BADCOMMAND;
    case VCE_EFOPEN_W: return STRDEF_EMESG_EFOPEN_W;
    case VCE_ERENAME: return STRDEF_EMESG_ERENAME;
    case VCE_ENOTFOUND: return STRDEF_EMESG_ENOTFOUND;
    case VCE_ELENTOOLONG: return STRDEF_EMESG_ELENTOOLONG;
    case VCE_EDATASHORT: return STRDEF_EMESG_EDATASHORT;
    case VCE_EOPENDIR: return STRDEF_EMESG_EOPENDIR;
    case VCE_EFSEEK: return STRDEF_EMESG_EFSEEK;
    case VCE_EFREAD: return STRDEF_EMESG_EFREAD;
    case VCE_EMKDIR: return STRDEF_EMESG_EMKDIR;
    case VCE_EALREADY: return STRDEF_EMESG_EALREADY;
    case VCE_EFINALIZE: return STRDEF_EMESG_EFINALIZE;
    case VCE_ECLOSED: return STRDEF_EMESG_ECLOSED;
    case VCE_EGENCOMMAND: return STRDEF_EMESG_EGENCOMMAND;
    case VCE_ENOCRYPTO: return STRDEF_EMESG_ENOCRYPTO;
    case VCE_ETOOLONGNAME: return STRDEF_EMESG_ETOOLONGNAME;
    case VCE_ESIZE: return STRDEF_EMESG_ESIZE;
    case VCE_ESWNOTREADY: return STRDEF_EMESG_ESWNOTREADY;
    case VCE_ESERVERDOWN: return STRDEF_EMESG_ESERVERDOWN;
    case VCE_EODDBUFSIZE: return STRDEF_EMESG_EODDBUFSIZE;
    case VCE_EODDKEYSIZE: return STRDEF_EMESG_EODDKEYSIZE;
    case VCE_EKEYEX: return STRDEF_EMESG_EKEYEX;
    case VCE_EMORESENDBUF: return STRDEF_EMESG_EMORESENDBUF;
    case VCE_EINIT: return STRDEF_EMESG_EINIT;
    case VCE_EARRAY: return STRDEF_EMESG_EARRAY;
    default: return STRDEF_UNKNOWNERROR;
    }
}

char *vce_strerror_close_reason(CLOSE_REASON reason)
{
//  static char tmp[256];
	switch(reason) {
	case CLOSE_REASON_NONE:             //  VCEが内部的に使用する．これが返されるのは， VCE のバグが考えられる．
		return "CLOSE_REASON_NONE";
	case CLOSE_REASON_UNKNOWN:          //  原因不明．基本的に返されることはない． 返された場合は，VCEのバグが考えられる．
		return "CLOSE_REASON_UNKNOWN";
	case CLOSE_REASON_REMOTE:           //  リモートピアによってコネクションが切断されたため， 書きこみも読みこみもできなくなった． CLOSE_REASON_REMOTE は，リモート型の中で，特に分類できなかった場合の generic な理由のときに返される．
		return "CLOSE_REASON_REMOTE";
	case CLOSE_REASON_APPLICATION:      //  アプリケーションによって， vce_conn_close などが呼びだされた． 「ローカル型」の典型的なクローズ理由である．
		return "CLOSE_REASON_APPLICATION";
	case CLOSE_REASON_TIMEOUT:          //  タイムアウト時間になるまで，送受信が行われなかったため， 切断された．タイムアウトの場合は，リモートが原因なのか， ローカルが原因なのか，判別はつかない．
		return "CLOSE_REASON_TIMEOUT";
	case CLOSE_REASON_DECODER:          //  暗号デコーディング関数の内部でエラーが起きた． 相手から送られてきたデータのフォーマットが異常であるか， データレコードが必要としている分のデータが届かない間にコネクションが 利用不可能になってしまった場合に起こる． つまり，このエラーは，「リモート型」である． このエラーは，コネクション初期化時の暗号ネゴシエーションが終わり， データの交換が始まってから起こる．
		return "CLOSE_REASON_DECODER";
	case CLOSE_REASON_ENCODER:          //  暗号エンコーディング関数の内部でエラーが起きた． このエラーは，コネクション初期化時の暗号ネゴシエーションが終わり， データの交換が始まってから起こる． VCE は暗号化用に特別なメモリを使わないこともあり，この理由は 「リモート型」である．
		return "CLOSE_REASON_ENCODER";
	case CLOSE_REASON_PARSER:           //  プロトコルパーサー関数が負の値を返したので， コネクションを切断した． これは，ローカル型である．ローカルのパーサー関数の返り値が負であった．
		return "CLOSE_REASON_PARSER";
	case CLOSE_REASON_INTERNAL:         //  VCE の内部的な問題により，コネクションを閉じた． VCEの内部メモリが足りない場合や，エラーチェックに 失敗した場合や，VCEのバグが考えられる． ローカル型である．
		return "CLOSE_REASON_INTERNAL";
	case CLOSE_REASON_FULL:             //  SWPを使っている場合に，SWPへ送る送信バッファが一杯になっている場合に この値になる．SWPへ送る送信バッファが一杯ということは， SWPのサーバーからの受信バッファも一杯になっている可能性が高い． SWPのバッファー容量を大きくするか， 相手むけ回線の容量が一杯になっていることを疑うべきである． リモートホストのバッファが一杯になっていることから， 「リモート型」と言える．
		return "CLOSE_REASON_FULL";
	default:
		//sprintf(tmp,"CLOSE_REASON_?",reason);
		return "CLOSE_REASON_?????";
	}
}


int vce_get_last_error( void ) {
    return vce_last_error;
}
