import { Body, Controller, Get, Post } from '@nestjs/common';
import { CatService } from './cat.service';
import { Cat } from '../orm/entity/Cat';

@Controller('rest/cat')
export class CatController {
    constructor(private readonly service: CatService) {}

    @Get('/index')
    async index() {
        return await this.service.findAll();
    }

    @Post('/create')
    async create(
        @Body()
        catParam: {
            uuid: string;
            name: string;
            age: number;
            color: string;
        },
    ) {
        const cat = new Cat();
        cat.age = catParam.age;
        cat.uuid = catParam.uuid;
        cat.name = catParam.name;
        cat.color = catParam.color;
        return await this.service.create(cat);
    }
}
