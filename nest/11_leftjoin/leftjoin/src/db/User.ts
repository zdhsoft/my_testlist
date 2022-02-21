import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('user', { schema: 'orm' })
export class User {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'nickname', length: 50 })
    nickname: string;

    @Column('varchar', { name: 'username', length: 50 })
    username: string;

    @Column('varchar', { name: 'password', length: 50 })
    password: string;

    @Column('varchar', { name: 'avator', length: 255 })
    avator: string;

    @Column('varchar', { name: 'email', length: 50 })
    email: string;
}
