import { Module } from '@nestjs/common';
import { UserModule } from 'src/user/user.module';
import { LoginController } from './login.controller';

@Module({
    imports: [UserModule],
    controllers: [LoginController],
})
export class LoginModule {}
