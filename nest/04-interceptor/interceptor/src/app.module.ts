import { UploadController } from './upload/upload.controller';
import { UploadService } from './upload/upload.service';

import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';

@Module({
    imports: [],
    controllers: [UploadController, AppController],
    providers: [UploadService, AppService],
})
export class AppModule {}
