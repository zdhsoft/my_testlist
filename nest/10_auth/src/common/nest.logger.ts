/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename nest.logger.ts
 * @summary：nest的替换日志
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-08
 *************************************************************************/
import { LoggerService } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('nest');
/**
 * nest的日志类
 */
export class NestLogger implements LoggerService {
    log(...msg: any[]) {
        log.info(...msg);
    }
    error(...msg: any[]) {
        log.error(...msg);
    }
    warn(...msg: any[]) {
        log.warn(...msg);
    }
    debug(...msg: any[]) {
        log.debug(...msg);
    }
    verbose(...msg: any[]) {
        log.trace(...msg);
    }
}
