import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Article } from 'src/db/article.entity';
import { Attachment } from 'src/db/attachment.entity';
import { User } from 'src/db/user.entity';
import { Repository } from 'typeorm';

@Injectable()
export class UserService {
    constructor(@InjectRepository(User) private readonly userRepository: Repository<User>) {}

    // 三张表关联查询
    async getAttachment(): Promise<any> {
        return this.userRepository
            .createQueryBuilder()
            .leftJoinAndSelect(Article, 'article', 'user.id = article.createBy')
            .leftJoinAndSelect(Attachment, 'attachment', 'user.id = attachment.createBy')
            .select(
                `
        article.id as id,
        article.title as title,
        article.content as content,
        user.id as userId,
        user.nickname as nickname,
        user.username as usernmae,
        user.avator as avator,
        attachment.id as attachmentId,
        attachment.originName as fileName,
        attachment.size as fileSize,
        attachment.filePath as filePath
      `,
            )
            .getRawMany();
    }
}
