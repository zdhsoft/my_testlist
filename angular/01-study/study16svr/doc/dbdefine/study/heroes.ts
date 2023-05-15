import {
    Column,
    DeepPartial,
    Entity,
    FindOptionsOrder,
    FindOptionsSelect,
    FindOptionsWhere,
    PrimaryGeneratedColumn,
} from 'typeorm';

@Entity('heroes', { schema: 'study16db' })
export class Heroes {
    public static getTableName() {
        return `heroes`;
    }

    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    public id: number;

    /** 英雄名称 */
    @Column('varchar', { name: 'name', comment: '英雄名称', length: 255 })
    public name: string;
}

export declare type WhereHeroes = FindOptionsWhere<Heroes>;

export declare type RecHeroes = DeepPartial<Heroes>;

export declare type SelectHeroes = FindOptionsSelect<Heroes>;

export declare type OrderHeroes = FindOptionsOrder<Heroes>;
