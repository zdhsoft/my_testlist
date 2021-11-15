import { LoggerService } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('nest');
export class NestLogger implements LoggerService {
    log(message: string) {
        log.log(message);
    }
    error(message: string, trace: string) {
        log.error(message);
    }
    warn(message: string) {
        log.warn(message);
    }
    debug(message: string) {
        log.debug(message);
    }
    verbose(message: string) {
        log.trace(message);
    }
}
