import { Controller, Get, Post, Query, Req, Res } from '@nestjs/common';
import { Request, Response } from 'express';
import { UserService } from 'src/user/user.service';
@Controller('login')
export class LoginController {
    // constructor(private readonly userService: UserService) {
    //     //
    // }
    // @Post('/info')
    // info_post() {
    //     return 'post';
    // }
    // @Get('/info')
    // async info_get(@Req() req: Request, @Res() res: Response, @Query('name') name:string) {
    //     return await this.userService.findOne(name);
    // }
}
