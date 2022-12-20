import { Controller, Get } from '@nestjs/common';
import { XAppService } from './app.service';

@Controller()
export class XAppController {
    constructor(private readonly appService: XAppService) {}

    @Get()
    async getHello() {
        const result = await this.appService.t3();
        return JSON.stringify(result, null, 2);
    }
}
