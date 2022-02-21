import { Controller, Get } from '@nestjs/common';
import { XCommonRet } from 'xmcommon';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
    constructor(private userService: UserService) {}
    @Get('/test')
    async test() {
        const r = new XCommonRet();
        do {
            //
            const data = await this.userService.getAttachment();
            r.setOK(data);
        } while (false);
        return r;
    }

    @Get('/in')
    async in() {
        const r = new XCommonRet();
        do {
            const data = await this.userService.in();
            r.setOK(data);
        } while (false);
        return r;
    }
}
