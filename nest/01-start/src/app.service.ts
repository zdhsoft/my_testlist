import { Injectable } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
@Injectable()
export class AppService {
    public constructor() {
        log.info('AppService~~~~~~~');
    }
    getHello(): string {
        return 'Hello World!~~~';
    }
}
