import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Cat } from '../orm/entity/Cat';
import { User } from '../orm/entity/User';
import { CatService } from './cat.service';
import { CatController } from './cat.controller';

@Module({
    imports: [TypeOrmModule.forFeature([Cat, User])],
    providers: [CatService],
    controllers: [CatController],
})
export class CatModule {}
