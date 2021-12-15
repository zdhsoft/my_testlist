import { Strategy } from 'passport-local';
import { PassportStrategy } from '@nestjs/passport';
import { Injectable, UnauthorizedException } from '@nestjs/common';
import { AuthService } from './auth.service';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Injectable()
export class LocalStrategy extends PassportStrategy(Strategy) {
    constructor(private authService: AuthService) {
        super();
    }

    async validate(username: string, password: string): Promise<any> {
        log.info('是你吗？');
        const user = await this.authService.validateUser(username, password);
        if (!user) {
            throw new UnauthorizedException({}, 'aaaaaaaaaaaaaaaaaaaaaaaa');
        }
        return user;
    }
}
