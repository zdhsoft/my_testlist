import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Observable } from 'rxjs';
import { Request } from 'express';
// import { getLogger } from 'xmcommon';
import { ISession, urlPrefix } from './constant';
import { XAPIException } from './api_exception';
import { EnumErrorCode } from '../error/error_code';

// const log = getLogger(__filename);

@Injectable()
export class XAuthGuard implements CanActivate {
    canActivate(paramContext: ExecutionContext): boolean | Promise<boolean> | Observable<boolean> {
        const host = paramContext.switchToHttp();
        const req = host.getRequest<Request>();
        const url = req.path;
        let ret = false;
        do {
            if (url.startsWith(urlPrefix.API)) {
                if (url.startsWith(urlPrefix.LOCAL_API)) {
                    ret = true;
                } else {
                    if ((req.session as ISession)?.isLogin === true) {
                        ret = true;
                    } else {
                        // 如果没有登录，则这里返回false
                        ret = false;
                    }
                }
            } else {
                ret = true;
            }
        } while (false);
        if (!ret) {
            throw new XAPIException(EnumErrorCode.NOT_LOGIN, '您还没有登录!', url);
        }
        return ret;
    }
}
