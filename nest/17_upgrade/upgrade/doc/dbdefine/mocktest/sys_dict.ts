import {
    Column,
    DeepPartial,
    Entity,
    FindOptionsOrder,
    FindOptionsSelect,
    FindOptionsWhere,
    Index,
    PrimaryGeneratedColumn,
} from 'typeorm';

/** 系统词典表 */
@Index('idx_dict_key', ['dictKey'], {})
@Entity('sys_dict', { schema: 'mock-test' })
export class SysDict {
    public static getTableName() {
        return `sys_dict`;
    }
    /** ID */
    @PrimaryGeneratedColumn({ type: 'int', name: 'id', comment: 'ID' })
    public id: number;

    /** 系统名 */
    @Column('varchar', { name: 'sys_name', comment: '系统名', length: 20 })
    public sysName: string;

    /** 键 */
    @Column('varchar', { name: 'dict_key', comment: '键', length: 20 })
    public dictKey: string;

    /** 值 */
    @Column('varchar', { name: 'dict_value', nullable: true, comment: '值', length: 100 })
    public dictValue: string | null;

    /** 创建时间 */
    @Column('datetime', {
        name: 'create_time',
        nullable: true,
        comment: '创建时间',
        default: () => 'CURRENT_TIMESTAMP',
    })
    public createTime: Date | null;

    /** 修改时间 */
    @Column('datetime', {
        name: 'update_time',
        nullable: true,
        comment: '修改时间',
        default: () => 'CURRENT_TIMESTAMP',
    })
    public updateTime: Date | null;
}

/** 定义where类型 for 系统词典表 */
export declare type WhereSysDict = FindOptionsWhere<SysDict>;
/** 定义Record类型 for 系统词典表 */
export declare type RecSysDict = DeepPartial<SysDict>;
/** 定义Select类型 for 系统词典表 */
export declare type SelectSysDict = FindOptionsSelect<SysDict>;
/** 定义Order类型 for 系统词典表 */
export declare type OrderSysDict = FindOptionsOrder<SysDict>;
