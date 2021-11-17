import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('Account')
export class AccountEntity {
    @PrimaryGeneratedColumn() id:string;

    @Column()
    account: string
}
