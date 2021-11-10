import { Controller, Get } from '@nestjs/common';
import { AppService } from './app.service';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
@Controller()
export class AppController {
    constructor(private readonly appService: AppService) {
        log.info('------------AppController');
    }

    @Get()
    getHello(): string {
        log.info('getHello---->');
        return this.appService.getHello();
    }
}
