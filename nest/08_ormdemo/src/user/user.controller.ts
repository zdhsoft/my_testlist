import { Body, Controller, Post } from '@nestjs/common';
import { XCommonRet } from 'xmcommon';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
    constructor(private readonly userService: UserService) {}
    @Post('all')
    // @HttpCode(200)
    async all() {
        const r = new XCommonRet();
        r.setData(await this.userService.findAll());
        return r;
    }

    @Post('user')
    async getUser(@Body() param: { id: number }) {
        const r = new XCommonRet();
        r.setData(await this.userService.findOne(param.id));
        return r;
    }
}
