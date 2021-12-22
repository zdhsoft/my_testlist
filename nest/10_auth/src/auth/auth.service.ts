import { Injectable } from '@nestjs/common';
import { UserService } from 'src/api/user/user.service';
import { getLogger, XCommonRet } from 'xmcommon';
import { User } from 'src/db/User';

const log = getLogger(__filename);
@Injectable()
export class AuthService {
    constructor(private readonly userService: UserService) {}
    async validateUser(paramUserName: string, paramUserPassword: string): Promise<XCommonRet<User>> {
        const r = new XCommonRet<User>();
        do {
            const user = await this.userService.findOne(paramUserName);
            if (user?.password === paramUserPassword) {
                r.setData(user);
            } else {
                r.setError(-1, '验证失败');
            }
        } while (false);
        return r;
    }
}
