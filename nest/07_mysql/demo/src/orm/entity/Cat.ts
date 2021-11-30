import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('cat', { schema: 'orm' })
export class Cat {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'uuid', length: 100 })
    uuid: string;

    @Column('varchar', { name: 'name', length: 50 })
    name: string;

    @Column('int', { name: 'age' })
    age: number;

    @Column('varchar', { name: 'color', nullable: true, length: 30 })
    color: string | null;

    @Column('timestamp', {
        name: 'createAt',
        default: () => 'CURRENT_TIMESTAMP',
    })
    createAt: Date;

    @Column('timestamp', {
        name: 'updateAt',
        nullable: true,
        default: () => 'CURRENT_TIMESTAMP',
    })
    updateAt: Date | null;
}
