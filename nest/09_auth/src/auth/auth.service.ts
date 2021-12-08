import { Injectable } from '@nestjs/common';

@Injectable()
export class AuthService {
    async validateUser(username: string, pass: string): Promise<any> {
        // const user = await this.userService.findOne(username);
        // if (user && user.password === pass) {
        //     const { password, ...result } = user;
        //     return result;
        // }
        return null;
    }
}
