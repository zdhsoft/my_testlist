import { Controller, Post } from '@nestjs/common';
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
}
