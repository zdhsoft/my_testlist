// 文件目录: src/entities/article.entity.ts
import { Column, Entity, PrimaryColumn } from 'typeorm';

@Entity('article')
export class Article {
    @PrimaryColumn()
    id: string;

    @Column()
    title: string;

    @Column()
    link: string;

    @Column()
    fileId: string;

    @Column('text')
    content: string;

    @Column()
    categoryId: string;

    @Column()
    formatId: number;

    @Column()
    originId: number;

    @Column()
    createBy: string;
}
