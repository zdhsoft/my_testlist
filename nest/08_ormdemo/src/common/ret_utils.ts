import { XCommonRet } from 'xmcommon';

export interface IHttpRet {
    ret: number;
    msg?: string;
    data?: unknown;
    url?: string;
}
export class RetUtils {
    public static ret(paramErr: number, paramErrMsg?: string, paramData?: unknown, paramURL?: string): IHttpRet {
        return {
            ret: paramErr,
            msg: paramErrMsg,
            data: paramData,
            url: paramURL,
        };
    }

    public static byCommonRet(paramRet: XCommonRet): IHttpRet {
        return {
            ret: paramRet.err,
            msg: paramRet.msg,
            data: paramRet.data,
        };
    }
}
