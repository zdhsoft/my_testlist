import { Module } from '@nestjs/common';
import { UserService } from './user.service';
import { UserController } from './user.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from 'src/db/User';
import { Article } from 'src/db/Article';
import { Attachment } from 'src/db/Attachment';

@Module({
    imports: [TypeOrmModule.forFeature([User, Article, Attachment])],
    providers: [UserService],
    controllers: [UserController],
})
export class UserModule {}
