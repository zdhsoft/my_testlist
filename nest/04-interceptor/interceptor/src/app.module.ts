import { AccountModule } from './account/account.module';
import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';

@Module({
    imports: [AccountModule],
    controllers: [AppController],
    providers: [AppService],
})
export class AppModule {}
