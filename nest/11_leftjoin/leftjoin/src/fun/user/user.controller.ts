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
            await this.userService.getAttachment();
        } while (false);
        return r;
    }
}
