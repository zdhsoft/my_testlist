import { AccountService } from './account.service';
import { AccountController } from './account.controller';
import { Module } from '@nestjs/common';

@Module({
    imports: [],
    controllers: [AccountController],
    providers: [AccountService],
})
export class AccountModule {}
