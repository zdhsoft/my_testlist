import { Controller, Get } from '@nestjs/common';
import { XAppService } from './app.service';

@Controller()
export class XAppController {
    constructor(private readonly appService: XAppService) {}

    @Get()
    async getHello() {
        return await this.appService.getHello();
    }
}
