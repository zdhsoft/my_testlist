import { Module } from '@nestjs/common';
import { UserService } from './user.service';
import { UserController } from './user.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from 'src/db/user.entity';
import { Article } from 'src/db/article.entity';
import { Attachment } from 'src/db/attachment.entity';

@Module({
    imports: [TypeOrmModule.forFeature([User, Article, Attachment])],
    providers: [UserService],
    controllers: [UserController],
})
export class UserModule {}
