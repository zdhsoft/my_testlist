import { Controller, Get, Post, Query, Req, Res } from '@nestjs/common';
import { UserService } from './user.service';
import { Request, Response } from 'express';
import { XCommonRet } from 'xmcommon';

@Controller('user')
export class UserController {
    constructor(private readonly userService: UserService) {
        //
    }
    // @Post('/info')
    // info_post() {
    //     return 'post';
    // }
    @Get('/info')
    async info_get(@Req() req: Request, @Res() res: Response, @Query('name') name: string) {
        const r = new XCommonRet();
        r.setData(await this.userService.findOne(name));
        return JSON.stringify(r);
    }
}
