import { Entity, PrimaryGeneratedColumn, Column, OneToMany } from 'typeorm';
import { Photo } from './Photo';

@Entity()
export class TestUser {
    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    name: string;

    @OneToMany((type) => Photo, (photo) => photo.user)
    photos: Photo[];
}
