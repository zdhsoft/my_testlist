import { LoggerService } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('nest');
export class NestLogger implements LoggerService {
    log(message: string, ...opt: any[]) {
        log.info(message, 'xxxx>', ...opt);
    }
    error(message: string, ...opt: any[]) {
        log.error(message, 'xxxx>', ...opt);
    }
    warn(message: string, ...opt: any[]) {
        log.warn(message, 'xxxx>', ...opt);
    }
    debug(message: string, ...opt: any[]) {
        log.debug(message, 'xxxx>', ...opt);
    }
    verbose(message: string, ...opt: any[]) {
        log.trace(message, 'xxxx>', ...opt);
    }
}
