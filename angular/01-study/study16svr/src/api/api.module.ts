import { Module } from '@nestjs/common';
import { XApiService } from './api.service';
import { XApiController } from './api.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Heroes } from '../db/heroes';

@Module({
    imports: [TypeOrmModule.forFeature([Heroes])],
    providers: [XApiService],
    controllers: [XApiController],
})
export class XApiModule {}
