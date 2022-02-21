// 文件目录: src/entities/user.entity.ts
import { Column, Entity, PrimaryColumn } from 'typeorm';

@Entity('user')
export class User {
    @PrimaryColumn()
    id: string;

    @Column()
    nickname: string;

    @Column()
    username: string;

    @Column()
    password: string;

    @Column()
    avator: string;

    @Column()
    email: string;
}
