import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
//import { UserModule } from 'src/user/user.module';
import { LocalStrategy } from './local.strategy';
import { PassportModule } from '@nestjs/passport';

@Module({
    imports: [PassportModule],
    providers: [AuthService, LocalStrategy],
})
export class AuthModule {}
