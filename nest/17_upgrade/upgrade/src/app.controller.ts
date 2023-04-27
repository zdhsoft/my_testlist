import { Controller, Get } from '@nestjs/common';
import { XAppService } from './app.service';
import { XRedisService } from './service/redis.service';

@Controller()
export class XAppController {
    constructor(private readonly appService: XAppService, private readonly redisSerivce: XRedisService) {}

    @Get()
    async getHello() {
        this.redisSerivce.set('aaaa', new Date().toString(), 3000);
        return await this.appService.getHello();
    }
}
