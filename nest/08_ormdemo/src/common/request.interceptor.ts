/*
https://docs.nestjs.com/interceptors#interceptors
*/

import { Injectable, NestInterceptor, ExecutionContext, CallHandler } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap, map } from 'rxjs/operators';
import { getLogger, XCommonRet } from 'xmcommon';
import { IHttpRet } from './ret_utils';

const log = getLogger('拦截器');
let requestSeq = 0;

@Injectable()
export class RequestInterceptor implements NestInterceptor {
    intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
        const start = Date.now(); // 请求开始时间
        const host = context.switchToHttp();

        const request = host.getRequest();
        const seq = requestSeq++;
        const urlInfo = `${request.method} ${request.url}`;
        log.info(`[${seq}]==> ${urlInfo}`);
        return next
            .handle()
            .pipe(
                map((data) => {
                    if (data instanceof XCommonRet) {
                        log.info('ret is XCommonRet');
                        return {
                            ret: data.err,
                            msg: data.msg,
                            data: data.data,
                        };
                    } else if (data === undefined) {
                        log.error('--------- data is undefine!');
                        return data;
                    } else {
                        const r: IHttpRet = {
                            ret: -1,
                            msg: '这个请求返回的不是XCommonRet对象！',
                            url: request.originalUrl,
                        };
                        log.error('返回错误:' + JSON.stringify(r));
                        return data;
                    }
                }),
            )
            .pipe(tap(() => log.info(`[${seq}]<== ${urlInfo} ${Date.now() - start} ms`)));
    }
}
