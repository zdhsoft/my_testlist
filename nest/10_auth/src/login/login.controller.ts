import { Controller, Get, Post, Query, UseGuards, Request } from '@nestjs/common';
import { UserService } from 'src/user/user.service';
import { LocalGuard } from 'src/common/local.guard';
@Controller('login')
export class LoginController {
    constructor(private readonly userService: UserService) {
        //
    }

    @UseGuards(LocalGuard)
    @Post('/login')
    async doLogin(@Request() req) {
        return req.user;
    }

    @Post('/info')
    info_post() {
        return 'post';
    }
    @Get('/info')
    async info_get(@Query('name') name: string) {
        return await this.userService.findOne(name);
    }
}
