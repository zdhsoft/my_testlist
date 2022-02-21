import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Article } from 'src/db/Article';
import { Attachment } from 'src/db/Attachment';
import { User } from 'src/db/User';
import { In, Repository, getConnection } from 'typeorm';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Injectable()
export class UserService {
    constructor(@InjectRepository(User) private readonly userRepository: Repository<User>) {}
    async in(): Promise<any> {
        return this.userRepository.findOne(100);
    }

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
