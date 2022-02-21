import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('article', { schema: 'orm' })
export class Article {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'title', length: 255 })
    title: string;

    @Column('varchar', { name: 'link', length: 255 })
    link: string;

    @Column('int', { name: 'fileId' })
    fileId: number;

    @Column('text', { name: 'content' })
    content: string;

    @Column('int', { name: 'categoryId' })
    categoryId: number;

    @Column('int', { name: 'formatId' })
    formatId: number;

    @Column('int', { name: 'originId' })
    originId: number;

    @Column('int', { name: 'createBy' })
    createBy: number;
}
