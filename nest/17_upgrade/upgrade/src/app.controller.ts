import { Controller, Get, Session } from '@nestjs/common';
import { XAppService } from './app.service';
import { XRedisService } from './service/redis.service';
import { ISession } from './common/constant';

@Controller()
export class XAppController {
    constructor(private readonly appService: XAppService, private readonly redisSerivce: XRedisService) {}

    @Get()
    async getHello(@Session() paramSession: ISession) {
        paramSession.user = { id: Date.now(), name: new Date().toString() };
        paramSession.save();
        this.redisSerivce.set('aaaa', new Date().toString(), 3000);
        return await this.appService.getHello();
    }
}
