import {
    Column,
    DeepPartial,
    Entity,
    FindOptionsOrder,
    FindOptionsSelect,
    FindOptionsWhere,
    PrimaryGeneratedColumn,
} from 'typeorm';

@Entity('data_invoice', { schema: 'mock-test' })
export class DataInvoice {
    public static getTableName() {
        return `data_invoice`;
    }
    /** 主键 */
    @PrimaryGeneratedColumn({ type: 'bigint', name: 'id', comment: '主键', unsigned: true })
    public id: string;

    /** 融资数据主键 */
    @Column('bigint', { name: 'data_id', comment: '融资数据主键' })
    public dataId: string;

    /** 发票主键 */
    @Column('bigint', { name: 'invoice_id', comment: '发票主键' })
    public invoiceId: string;

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

export declare type WhereDataInvoice = FindOptionsWhere<DataInvoice>;

export declare type RecDataInvoice = DeepPartial<DataInvoice>;

export declare type SelectDataInvoice = FindOptionsSelect<DataInvoice>;

export declare type OrderDataInvoice = FindOptionsOrder<DataInvoice>;
