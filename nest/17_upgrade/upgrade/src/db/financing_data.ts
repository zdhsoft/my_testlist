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

/** 融资数据表 */
@Index('env', ['env'], {})
@Index('uuid', ['uuid'], {})
@Entity('financing_data', { schema: 'mock-test' })
export class FinancingData {
    public static getTableName() {
        return `financing_data`;
    }
    /** 主键-非万科 */
    @PrimaryGeneratedColumn({ type: 'bigint', name: 'id', comment: '主键-非万科', unsigned: true })
    public id: string;

    /** 环境-非万科 */
    @Column('varchar', { name: 'env', nullable: true, comment: '环境-非万科', length: 10 })
    public env: string | null;

    /** 融资单唯一标志码 */
    @Column('varchar', { name: 'uuid', comment: '融资单唯一标志码', length: 50 })
    public uuid: string;

    /** 资金方名称 */
    @Column('varchar', { name: 'capital_name', nullable: true, comment: '资金方名称', length: 100 })
    public capitalName: string | null;

    /** 合作银行名称 */
    @Column('varchar', { name: 'bank_name', nullable: true, comment: '合作银行名称', length: 100 })
    public bankName: string | null;

    /** 申请公司名称 */
    @Column('varchar', { name: 'apply_company_name', nullable: true, comment: '申请公司名称', length: 200 })
    public applyCompanyName: string | null;

    /** 收款人名称 */
    @Column('varchar', { name: 'supplier_name', nullable: true, comment: '收款人名称', length: 200 })
    public supplierName: string | null;

    /** 币种名称 */
    @Column('varchar', { name: 'currency_name', nullable: true, comment: '币种名称', length: 100 })
    public currencyName: string | null;

    /** 款项类型名称 */
    @Column('varchar', { name: 'fee_type_name', nullable: true, comment: '款项类型名称', length: 100 })
    public feeTypeName: string | null;

    /** 到期日 */
    @Column('datetime', { name: 'expired_date', nullable: true, comment: '到期日' })
    public expiredDate: Date | null;

    /** 融资金额 */
    @Column('decimal', { name: 'financing_amount', nullable: true, comment: '融资金额', precision: 30, scale: 2 })
    public financingAmount: string | null;

    /** 合同号 */
    @Column('varchar', { name: 'contract_number_real', nullable: true, comment: '合同号', length: 50 })
    public contractNumberReal: string | null;

    /** 合同归档号 */
    @Column('varchar', { name: 'contract_number', nullable: true, comment: '合同归档号', length: 255 })
    public contractNumber: string | null;

    /** 合同名称 */
    @Column('varchar', { name: 'contract_name', nullable: true, comment: '合同名称', length: 255 })
    public contractName: string | null;

    /** 产值号 */
    @Column('text', { name: 'output_number', nullable: true, comment: '产值号' })
    public outputNumber: string | null;

    /** 付款确认书编号 */
    @Column('varchar', { name: 'pay_confirm_number', nullable: true, comment: '付款确认书编号', length: 50 })
    public payConfirmNumber: string | null;

    /** 预审状态:0:未审核,1:通 过,2:未通过 */
    @Column('varchar', { name: 'pre_state', nullable: true, comment: '预审状态:0:未审核,1:通 过,2:未通过', length: 1 })
    public preState: string | null;

    /** 预审时间 */
    @Column('datetime', { name: 'pre_time', nullable: true, comment: '预审时间' })
    public preTime: Date | null;

    /** 修改类型:1:业务资料修改;2:收款信息修改 3:更换资金渠道4:业务终止 */
    @Column('varchar', {
        name: 'update_type',
        nullable: true,
        comment: '修改类型:1:业务资料修改;2:收款信息修改 3:更换资金渠道4:业务终止',
        length: 4,
    })
    public updateType: string | null;

    /** 预审修改原因 */
    @Column('text', { name: 'pre_no_result', nullable: true, comment: '预审修改原因' })
    public preNoResult: string | null;

    /** 可放款状态 0：待放款 1：确认放款 */
    @Column('varchar', { name: 'pay_state', nullable: true, comment: '可放款状态 0：待放款 1：确认放款', length: 1 })
    public payState: string | null;

    /** 可放款批次号 */
    @Column('varchar', { name: 'pay_batch', nullable: true, comment: '可放款批次号', length: 50 })
    public payBatch: string | null;

    /** 签章状态 1未签章 4 签章失败 5 已签章 */
    @Column('varchar', {
        name: 'sign_status',
        nullable: true,
        comment: '签章状态 1未签章 4 签章失败 5 已签章',
        length: 1,
    })
    public signStatus: string | null;

    /** 签章时间 */
    @Column('datetime', { name: 'sign_time', nullable: true, comment: '签章时间' })
    public signTime: Date | null;

    /** 签章操作人 */
    @Column('varchar', { name: 'sign_user', nullable: true, comment: '签章操作人', length: 100 })
    public signUser: string | null;

    /** 签章是否下载 0 否 1 是 */
    @Column('varchar', { name: 'sign_is_down', nullable: true, comment: '签章是否下载 0 否 1 是', length: 1 })
    public signIsDown: string | null;

    /** 签章下载人 */
    @Column('varchar', { name: 'sign_down_user', nullable: true, comment: '签章下载人', length: 100 })
    public signDownUser: string | null;

    /** 签章下载时间 */
    @Column('datetime', { name: 'sign_down_time', nullable: true, comment: '签章下载时间' })
    public signDownTime: Date | null;

    /** 签章下载次数 */
    @Column('int', { name: 'sign_down_count', nullable: true, comment: '签章下载次数' })
    public signDownCount: number | null;

    /** 买方确认函是否下载(‘0’ 未下载 ‘1’ 已下载) */
    @Column('varchar', {
        name: 'has_down_buyer',
        nullable: true,
        comment: '买方确认函是否下载(‘0’ 未下载 ‘1’ 已下载)',
        length: 1,
    })
    public hasDownBuyer: string | null;

    /** 付款确认书是否下载(‘0’ 未下载 ‘1’ 已下载) */
    @Column('varchar', {
        name: 'has_down_confirm',
        nullable: true,
        comment: '付款确认书是否下载(‘0’ 未下载 ‘1’ 已下载)',
        length: 1,
    })
    public hasDownConfirm: string | null;

    /** 退票状态：0：正常，1:退票成功 */
    @Column('varchar', { name: 'refund_state', nullable: true, comment: '退票状态：0：正常，1:退票成功', length: 1 })
    public refundState: string | null;

    /** 退票人 */
    @Column('varchar', { name: 'refund_user', nullable: true, comment: '退票人', length: 50 })
    public refundUser: string | null;

    /** 退票原因 */
    @Column('text', { name: 'refund_result', nullable: true, comment: '退票原因' })
    public refundResult: string | null;

    /** 退票时间 */
    @Column('datetime', { name: 'refund_time', nullable: true, comment: '退票时间' })
    public refundTime: Date | null;

    /** 备注 */
    @Column('varchar', { name: 'remark', nullable: true, comment: '备注', length: 255 })
    public remark: string | null;

    /** 融资类型 */
    @Column('varchar', { name: 'financing_type', nullable: true, comment: '融资类型', length: 100 })
    public financingType: string | null;

    /** 收款人银行 */
    @Column('varchar', { name: 'payee_bank_name', nullable: true, comment: '收款人银行', length: 50 })
    public payeeBankName: string | null;

    /** 收款账号 */
    @Column('varchar', { name: 'payee_account_name', nullable: true, comment: '收款账号', length: 50 })
    public payeeAccountName: string | null;

    /** 汇率 */
    @Column('decimal', { name: 'local_cur_ex_rate', nullable: true, comment: '汇率', precision: 30, scale: 0 })
    public localCurExRate: string | null;

    /** 工程项目 */
    @Column('varchar', { name: 'cur_project', nullable: true, comment: '工程项目', length: 100 })
    public curProject: string | null;

    /** 融资放款日期 */
    @Column('datetime', { name: 'pay_date', nullable: true, comment: '融资放款日期' })
    public payDate: Date | null;

    /** 保理融资天数 */
    @Column('int', { name: 'capital_fin_days', nullable: true, comment: '保理融资天数' })
    public capitalFinDays: number | null;

    /** 保理融资利率 */
    @Column('decimal', { name: 'capital_fin_rate', nullable: true, comment: '保理融资利率', precision: 30, scale: 3 })
    public capitalFinRate: string | null;

    /** 状态：-1 作 废，0：正常 */
    @Column('varchar', { name: 'scf_status', nullable: true, comment: '状态：-1 作 废，0：正常', length: 1 })
    public scfStatus: string | null;

    /** 作废时间 */
    @Column('datetime', { name: 'invalid_times', nullable: true, comment: '作废时间' })
    public invalidTimes: Date | null;

    /** 付款账号 */
    @Column('varchar', { name: 'pay_account', nullable: true, comment: '付款账号', length: 100 })
    public payAccount: string | null;

    /** 付款银行 */
    @Column('varchar', { name: 'pay_bank', nullable: true, comment: '付款银行', length: 50 })
    public payBank: string | null;

    /** 一线融资单据编号 */
    @Column('varchar', { name: 'bill_number', nullable: true, comment: '一线融资单据编号', length: 50 })
    public billNumber: string | null;

    /** 源单编号 */
    @Column('varchar', { name: 'payment_bill_number', nullable: true, comment: '源单编号', length: 50 })
    public paymentBillNumber: string | null;

    /** 创建时间 */
    @Column('datetime', { name: 'create_time', nullable: true, comment: '创建时间' })
    public createTime: Date | null;

    /** CCS 更新时间 */
    @Column('datetime', { name: 'ccs_update_time', nullable: true, comment: 'CCS 更新时间' })
    public ccsUpdateTime: Date | null;

    /** 资金中心受理：0 未受理，1 已受理 */
    @Column('varchar', { name: 'accept_state', nullable: true, comment: '资金中心受理：0 未受理，1 已受理', length: 1 })
    public acceptState: string | null;

    /** 实际付款状态：0 未付款 1 已付款 */
    @Column('varchar', {
        name: 'really_pay_state',
        nullable: true,
        comment: '实际付款状态：0 未付款 1 已付款',
        length: 1,
    })
    public reallyPayState: string | null;

    /** 实际付款时间 */
    @Column('datetime', { name: 'really_pay_date', nullable: true, comment: '实际付款时间' })
    public reallyPayDate: Date | null;

    /** 实际付款批次号 */
    @Column('varchar', { name: 'really_pay_batch', nullable: true, comment: '实际付款批次号', length: 50 })
    public reallyPayBatch: string | null;

    /** 区域 */
    @Column('varchar', { name: 'area', nullable: true, comment: '区域', length: 50 })
    public area: string | null;

    /** 合同供应商 */
    @Column('varchar', { name: 'contract_supplier', nullable: true, comment: '合同供应商', length: 50 })
    public contractSupplier: string | null;

    /** 城市公司 */
    @Column('varchar', { name: 'city_company', nullable: true, comment: '城市公司', length: 50 })
    public cityCompany: string | null;

    /** 资产服务方名称 */
    @Column('varchar', { name: 'capital_serve_name', nullable: true, comment: '资产服务方名称', length: 50 })
    public capitalServeName: string | null;

    /** web 操作更新时间 */
    @Column('datetime', { name: 'web_update_time', nullable: true, comment: 'web 操作更新时间' })
    public webUpdateTime: Date | null;

    /** 0 未确认 1 可放款 */
    @Column('varchar', { name: 'bank_confirm_state', nullable: true, comment: '0 未确认 1 可放款', length: 1 })
    public bankConfirmState: string | null;

    /** 银行确认时间 */
    @Column('datetime', { name: 'bank_confirm_date', nullable: true, comment: '银行确认时间' })
    public bankConfirmDate: Date | null;

    /** 0 未出具 1 已出具 */
    @Column('varchar', { name: 'is_give_file', nullable: true, comment: '0 未出具 1 已出具', length: 1 })
    public isGiveFile: string | null;

    /** 转让编号 */
    @Column('varchar', { name: 'trans_number', nullable: true, comment: '转让编号', length: 50 })
    public transNumber: string | null;

    /** 发票号 */
    @Column('text', { name: 'invoice_number', nullable: true, comment: '发票号' })
    public invoiceNumber: string | null;

    /** 一线审核时间 */
    @Column('datetime', { name: 'ccs_audit_datetime', nullable: true, comment: '一线审核时间' })
    public ccsAuditDatetime: Date | null;

    /** 一线审批时间 */
    @Column('datetime', { name: 'ccs_approve_time', nullable: true, comment: '一线审批时间' })
    public ccsApproveTime: Date | null;

    /** 资金中心审核时间 */
    @Column('datetime', { name: 'ccs_zaudit_date', nullable: true, comment: '资金中心审核时间' })
    public ccsZauditDate: Date | null;

    /** 联行号 */
    @Column('varchar', { name: 'payee_bank_number', nullable: true, comment: '联行号', length: 50 })
    public payeeBankNumber: string | null;

    /** 是否并表： 1：并表2：不并表 */
    @Column('varchar', { name: 'is_and_table', nullable: true, comment: '是否并表： 1：并表2：不并表', length: 1 })
    public isAndTable: string | null;

    /** 付确书电子章:0 未签1 已签 */
    @Column('varchar', { name: 'is_sign_flag', nullable: true, comment: '付确书电子章:0 未签1 已签', length: 1 })
    public isSignFlag: string | null;

    /** 买方确认函电子章0 未签1 已签 */
    @Column('varchar', { name: 'is_sign_buyer', nullable: true, comment: '买方确认函电子章0 未签1 已签', length: 1 })
    public isSignBuyer: string | null;

    /** 确认函获取标识0 纸质1 电子 */
    @Column('varchar', { name: 'sign_buyer', nullable: true, comment: '确认函获取标识0 纸质1 电子', length: 1 })
    public signBuyer: string | null;

    /** 付确书出具时间 */
    @Column('datetime', { name: 'give_file_time', nullable: true, comment: '付确书出具时间' })
    public giveFileTime: Date | null;

    /** 修改标识，0 未修改 1 已修改 */
    @Column('varchar', { name: 'is_updated', nullable: true, comment: '修改标识，0 未修改 1 已修改', length: 2 })
    public isUpdated: string | null;

    /** 授权标识 0 未授权 1 已授权 */
    @Column('varchar', { name: 'is_auth', nullable: true, comment: '授权标识 0 未授权 1 已授权', length: 2 })
    public isAuth: string | null;

    /** 合同签署日期 */
    @Column('datetime', { name: 'contract_sign_date', nullable: true, comment: '合同签署日期' })
    public contractSignDate: Date | null;

    /** 合同签署类别 1 项目合同 2简易合同 3 战略协议 4 集采协议 5 费用合同 */
    @Column('varchar', {
        name: 'contract_kind',
        nullable: true,
        comment: '合同签署类别 1 项目合同 2简易合同 3 战略协议 4 集采协议 5 费用合同',
        length: 2,
    })
    public contractKind: string | null;

    /** 款项性质 */
    @Column('varchar', { name: 'fund_flow', nullable: true, comment: '款项性质', length: 100 })
    public fundFlow: string | null;

    /** 银企推送标识，0：否 1：是 */
    @Column('varchar', { name: 'is_send_bank', nullable: true, comment: '银企推送标识，0：否 1：是', length: 2 })
    public isSendBank: string | null;

    /** 操作更新时间 -非万科 */
    @Column('datetime', { name: 'oprt_update_time', nullable: true, comment: '操作更新时间 -非万科' })
    public oprtUpdateTime: Date | null;

    /** 创建时间 -非万科 */
    @Column('datetime', { name: 'gmt_create_time', comment: '创建时间 -非万科', default: () => 'CURRENT_TIMESTAMP' })
    public gmtCreateTime: Date;

    /** 修改时间-非万科 */
    @Column('datetime', { name: 'gmt_update_time', comment: '修改时间-非万科', default: () => 'CURRENT_TIMESTAMP' })
    public gmtUpdateTime: Date;
}

/** 定义where类型 for 融资数据表 */
export declare type WhereFinancingData = FindOptionsWhere<FinancingData>;
/** 定义Record类型 for 融资数据表 */
export declare type RecFinancingData = DeepPartial<FinancingData>;
/** 定义Select类型 for 融资数据表 */
export declare type SelectFinancingData = FindOptionsSelect<FinancingData>;
/** 定义Order类型 for 融资数据表 */
export declare type OrderFinancingData = FindOptionsOrder<FinancingData>;
