import { Body, Controller, Get, Param, Post, Query } from '@nestjs/common';
import { XCommonRet } from 'xmcommon';
import { XApiService } from './api.service';
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Controller('api')
export class XApiController {
    constructor(private apiServices: XApiService) {
        //
    }
    @Get('heroes')
    public async getHeroes() {
        const r = new XCommonRet();
        do {
            const heroes = await this.apiServices.getHeros();
            r.setOK(heroes);
            // 要插入的代码
        } while (false);
        return r;
    }

    @Get('hero/:id')
    public async getHero(@Param() paramP: { id: string }) {
        const r = new XCommonRet();
        do {
            //
            log.info('paramP---->' + JSON.stringify(paramP));
            const id = +paramP?.id;
            if (Number.isNaN(id)) {
                r.setError(-1, `你传入的id: ${paramP?.id} 是无效的整数!`);
                break;
            }
            const hero = await this.apiServices.getHero(id);
            if (!hero) {
                r.setError(-2, `你传入的id: ${id} 对应的hero不存在！`);
                break;
            }
            r.setOK(hero);
        } while (false);
        return r;
    }
    @Get('del/:id')
    public async delHero(@Param() paramP: { id: string }) {
        const r = new XCommonRet();
        do {
            //
            log.info('paramP---->' + JSON.stringify(paramP));
            const id = +paramP?.id;
            if (Number.isNaN(id)) {
                r.setError(-1, `你传入的id: ${paramP?.id} 是无效的整数!`);
                break;
            }
            await this.apiServices.delHero(id);
        } while (false);
        return r;
    }

    @Post('add')
    public async addHero(@Body() paramBody: { name: string }) {
        const r = new XCommonRet();
        do {
            //
            const ss = await this.apiServices.addHero(paramBody.name);
            r.setOK(ss);
        } while (false);
        return r;
    }

    @Post('update')
    public async updateHero(@Body() paramBody: { id: number; newName: string }) {
        const r = new XCommonRet();
        do {
            await this.apiServices.updateHero(paramBody.id, paramBody.newName);
        } while (false);
        return r;
    }

    @Post('search')
    public async searchHero(@Body() paramBody: { name: string }) {
        const r = new XCommonRet();
        do {
            const list = this.apiServices.searchHero(paramBody.name);
            r.setOK(list);
            //
        } while (false);
        return r;
    }
}
