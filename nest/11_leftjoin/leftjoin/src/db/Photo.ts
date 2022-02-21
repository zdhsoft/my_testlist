import { Entity, PrimaryGeneratedColumn, Column, ManyToOne } from 'typeorm';
import { TestUser } from './TestUser';

@Entity()
export class Photo {
    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    url: string;

    @ManyToOne((type) => TestUser, (user) => user.photos)
    user: TestUser;
}
