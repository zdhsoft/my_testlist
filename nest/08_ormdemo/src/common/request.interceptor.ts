/*
https://docs.nestjs.com/interceptors#interceptors
*/

import { Injectable, NestInterceptor, ExecutionContext, CallHandler, HttpStatus } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap, map } from 'rxjs/operators';
import { getLogger, XCommonRet } from 'xmcommon';
import { IHttpRet, RetUtils } from './ret_utils';
import { Response, Request } from 'express';

const log = getLogger('拦截器');
let requestSeq = 0;

@Injectable()
export class RequestInterceptor implements NestInterceptor {
    intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
        const start = Date.now(); // 请求开始时间
        const host = context.switchToHttp();

        const req = host.getRequest<Request>();
        const res = host.getResponse<Response>();

        const seq = requestSeq++;
        const urlInfo = `${req.method} ${req.url}`;
        log.info(`[${seq}]==> ${urlInfo}`);
        return next
            .handle()
            .pipe(
                map((data) => {
                    if (res.statusCode === HttpStatus.CREATED && req.method === 'POST') {
                        res.statusCode = HttpStatus.OK;
                    }
                    // 这里要求所有的请求返回，都是XCommonRet
                    if (data instanceof XCommonRet) {
                        // log.info('ret is XCommonRet');
                        return RetUtils.byCommonRet(data);
                    } else if (data === undefined) {
                        log.error('--------- data is undefine!');
                        return data;
                    } else {
                        const r: IHttpRet = {
                            ret: -1,
                            msg: '这个请求返回的不是XCommonRet对象！',
                            url: req.originalUrl,
                        };
                        log.error('返回错误:' + JSON.stringify(r));
                        return data;
                    }
                }),
            )
            .pipe(tap(() => log.info(`[${seq}]<== ${urlInfo} ${Date.now() - start} ms`)));
    }
}
