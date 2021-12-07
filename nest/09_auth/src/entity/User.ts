import { Column, Entity, Index, PrimaryGeneratedColumn } from 'typeorm';

@Index('name', ['name'], { unique: true })
@Entity('user', { schema: 'orm' })
export class User {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'firstName', length: 255 })
    firstName: string;

    @Column('varchar', { name: 'lastName', length: 255 })
    lastName: string;

    @Column('int', { name: 'age' })
    age: number;

    @Column('varchar', { name: 'name', unique: true, length: 255 })
    name: string;

    @Column('varchar', { name: 'password', length: 255 })
    password: string;
}
