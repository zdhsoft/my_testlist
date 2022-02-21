import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('attachment', { schema: 'orm' })
export class Attachment {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'originName', length: 255 })
    originName: string;

    @Column('int', { name: 'size' })
    size: number;

    @Column('varchar', { name: 'filePath', length: 255 })
    filePath: string;

    @Column('int', { name: 'createBy' })
    createBy: number;
}
