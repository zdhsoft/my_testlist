// 文件目录: src/entities/attachment.entity.ts
import { Column, Entity, PrimaryColumn } from 'typeorm';

@Entity('attachment')
export class Attachment {
    @PrimaryColumn()
    id: string;

    @Column()
    originName: string;

    @Column()
    size: number;

    @Column()
    filePath: string;

    @Column()
    createBy: string;
}
