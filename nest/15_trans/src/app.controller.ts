import { Controller, Get } from '@nestjs/common';
import { DataSource } from 'typeorm';
import { AppService } from './app.service';

@Controller()
export class AppController {
    constructor(private readonly appService: AppService, private ds: DataSource) {}

    @Get()
    getHello(): string {
        return this.appService.getHello();
    }
}
