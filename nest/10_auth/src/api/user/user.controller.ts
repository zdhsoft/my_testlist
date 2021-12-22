import { Controller, Get, Post, Query, Req, Res } from '@nestjs/common';
import { UserService } from './user.service';
import { Request } from 'express';
import { XCommonRet, getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Controller('api/user')
export class UserController {
    constructor(private readonly userService: UserService) {
        //
    }
    @Post('/info')
    info_post() {
        return 'post';
    }
    @Get('/info')
    async info_get(@Req() req: Request, @Query('name') query: string) {
        log.info('Query:' + JSON.stringify(query));
        const r = new XCommonRet();
        r.setData(await this.userService.findOne(query));
        return r;
    }

    // async info_get(@Req() req: Request, @Res() res: Response, @Query('name') name: string) {
    //     const r = new XCommonRet();
    //     r.setData(await this.userService.findOne(name));
    //     return r;
    // }
}
