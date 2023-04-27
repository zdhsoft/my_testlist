import {
    Column,
    DeepPartial,
    Entity,
    FindOptionsOrder,
    FindOptionsSelect,
    FindOptionsWhere,
    PrimaryGeneratedColumn,
} from 'typeorm';

@Entity('invoice', { schema: 'mock-test' })
export class Invoice {
    public static getTableName() {
        return `invoice`;
    }
    /** 主键 */
    @PrimaryGeneratedColumn({ type: 'bigint', name: 'id', comment: '主键', unsigned: true })
    public id: string;

    /** 发票号码 */
    @Column('varchar', { name: 'number', nullable: true, comment: '发票号码', length: 50 })
    public number: string | null;

    /** 发票代码 */
    @Column('varchar', { name: 'code', nullable: true, comment: '发票代码', length: 50 })
    public code: string | null;

    /** 发票金额(含税) */
    @Column('decimal', { name: 'invoice_amt', nullable: true, comment: '发票金额(含税)', precision: 30, scale: 2 })
    public invoiceAmt: string | null;

    /** 发票不含税金额 */
    @Column('decimal', { name: 'inv_no_tax_amt', nullable: true, comment: '发票不含税金额', precision: 30, scale: 2 })
    public invNoTaxAmt: string | null;

    /** 发票占用状态：0：未占用,1：部分占用,2：全部占用 */
    @Column('varchar', {
        name: 'is_used',
        nullable: true,
        comment: '发票占用状态：0：未占用,1：部分占用,2：全部占用',
        length: 1,
    })
    public isUsed: string | null;

    /** 发票中登状态：全部转让；部分转让 */
    @Column('varchar', {
        name: 'inv_book_state',
        nullable: true,
        comment: '发票中登状态：全部转让；部分转让',
        length: 10,
    })
    public invBookState: string | null;

    /** 转让金额 */
    @Column('decimal', { name: 'inv_trans_amt', nullable: true, comment: '转让金额', precision: 30, scale: 0 })
    public invTransAmt: string | null;

    /** 开票日期 */
    @Column('datetime', { name: 'invoice_date', nullable: true, comment: '开票日期' })
    public invoiceDate: Date | null;

    /** 发票类型：C：增值税普通发票，S:增值税专用发票,Z:其他原始凭证 */
    @Column('varchar', {
        name: 'invoice_type',
        nullable: true,
        comment: '发票类型：C：增值税普通发票，S:增值税专用发票,Z:其他原始凭证',
        length: 1,
    })
    public invoiceType: string | null;

    /** 税率 */
    @Column('decimal', { name: 'tax_rate', nullable: true, comment: '税率', precision: 30, scale: 2 })
    public taxRate: string | null;

    /** 税额 */
    @Column('decimal', { name: 'invoice_tax', nullable: true, comment: '税额', precision: 30, scale: 2 })
    public invoiceTax: string | null;

    /** 发票状态：3：已认证 */
    @Column('varchar', { name: 'invoice_state', nullable: true, comment: '发票状态：3：已认证', length: 255 })
    public invoiceState: string | null;

    /** 状态：-1 作废 */
    @Column('varchar', { name: 'invoice_status', nullable: true, comment: '状态：-1 作废', length: 255 })
    public invoiceStatus: string | null;

    /** 作废时间 */
    @Column('datetime', { name: 'invoice_invalid_times', nullable: true, comment: '作废时间' })
    public invoiceInvalidTimes: Date | null;

    /** 创建时间 */
    @Column('datetime', { name: 'create_time', comment: '创建时间', default: () => 'CURRENT_TIMESTAMP' })
    public createTime: Date;

    /** 修改时间 */
    @Column('datetime', { name: 'update_time', comment: '修改时间', default: () => 'CURRENT_TIMESTAMP' })
    public updateTime: Date;

    /** 本次转让金额 */
    @Column('decimal', { name: 'occupation_amt', nullable: true, comment: '本次转让金额', precision: 30, scale: 0 })
    public occupationAmt: string | null;

    /** 发票验证码 */
    @Column('varchar', { name: 'check_code', nullable: true, comment: '发票验证码', length: 100 })
    public checkCode: string | null;

    /** 发票拆分，S:结算款，C,竣工款 P进度款 H 历史 */
    @Column('varchar', {
        name: 'settle_progress',
        nullable: true,
        comment: '发票拆分，S:结算款，C,竣工款 P进度款 H 历史',
        length: 2,
    })
    public settleProgress: string | null;
}

export declare type WhereInvoice = FindOptionsWhere<Invoice>;

export declare type RecInvoice = DeepPartial<Invoice>;

export declare type SelectInvoice = FindOptionsSelect<Invoice>;

export declare type OrderInvoice = FindOptionsOrder<Invoice>;
