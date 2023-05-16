import { Module } from '@nestjs/common';
import { ApiService } from './api.service';
import { ApiController } from './api.controller';

@Module({
  providers: [ApiService],
  controllers: [ApiController]
})
export class ApiModule {}
