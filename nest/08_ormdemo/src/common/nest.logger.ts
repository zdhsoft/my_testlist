import { LoggerService } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('nest');
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
