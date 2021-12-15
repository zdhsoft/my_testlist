import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { LocalStrategy } from './local.strategy';
import { PassportModule } from '@nestjs/passport';
import { UserModule } from 'src/user/user.module';
@Module({
    imports: [PassportModule, UserModule],
    providers: [AuthService, LocalStrategy],
})
export class AuthModule {}
