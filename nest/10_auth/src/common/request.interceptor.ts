/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename request.interceptor.ts
 * @summary：全局拦截器实现
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-08
 *************************************************************************/

import { Injectable, NestInterceptor, ExecutionContext, CallHandler, HttpStatus } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap, map } from 'rxjs/operators';
import { getLogger, XCommonRet } from 'xmcommon';
import { IHttpRet, RetUtils } from './ret_utils';
import { Response, Request } from 'express';

const log = getLogger('拦截器');
/** 每次请求的记数器 */
let requestSeq = 0;

/**
 * 全局拦截器类
 */
@Injectable()
export class RequestInterceptor implements NestInterceptor {
    /**
     * 拦截器入口
     * @param context 上下文对象
     * @param next 后续调用函数
     * @returns
     */
    intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
        /** 请求开始时间 */
        const start = Date.now();
        /** 当前环境 */
        const host = context.switchToHttp();
        /** 请求对象 */
        const req = host.getRequest<Request>();
        /** 响应对象 */
        const res = host.getResponse<Response>();
        /** 当前计数 */
        const seq = requestSeq++;
        /** 当前URL */
        const urlInfo = `${req.method} ${req.url}`;

        log.info(`[${seq}]==> ${urlInfo}`);
        return next
            .handle()
            .pipe(
                map((data) => {
                    /* 这里拦截POST返回的statusCode，它默认返回是201, 这里改为200 */
                    if (res.statusCode === HttpStatus.CREATED && req.method === 'POST') {
                        res.statusCode = HttpStatus.OK;
                    }
                    // 这里要求所有的请求返回，都是XCommonRet
                    if (data instanceof XCommonRet) {
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
            .pipe(
                // 这里打印请求处理完成的信息
                tap(() => log.info(`[${seq}]<== ${urlInfo} ${Date.now() - start} ms`)),
            );
    }
}
