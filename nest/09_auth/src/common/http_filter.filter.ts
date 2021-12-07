/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename http_filter.filter.ts
 * @summary：请求异常过滤类
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-06
 *************************************************************************/
import { ArgumentsHost, Catch, ExceptionFilter, HttpException, HttpStatus } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('HttpException');

@Catch(HttpException)
export class HttpFilterFilter implements ExceptionFilter {
    catch(paramException: Error, paramHost: ArgumentsHost) {
        const ctx = paramHost.switchToHttp();
        const response = ctx.getResponse();
        const request = ctx.getRequest();

        const message = paramException.message;
        log.error('请求发生异常:', message);
        const status =
            paramException instanceof HttpException
                ? (paramException as HttpException).getStatus()
                : HttpStatus.INTERNAL_SERVER_ERROR;
        const errorResponse = {
            msg: '请求异常:' + message,
            ret: '-1', // 自定义code
            statusCode: status,
            url: request.originalUrl, // 错误的url地址
        };

        // 设置返回的状态码、请求头、发送错误信息
        response.status(HttpStatus.OK);
        response.header('Content-Type', 'application/json; charset=utf-8');
        response.send(errorResponse);
    }
}
