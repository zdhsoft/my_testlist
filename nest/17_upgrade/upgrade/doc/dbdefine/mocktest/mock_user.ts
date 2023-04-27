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

@Index('account', ['account'], { unique: true })
@Entity('mock_user', { schema: 'mock-test' })
export class MockUser {
    public static getTableName() {
        return `mock_user`;
    }

    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    public id: number;

    /** 账号 */
    @Column('varchar', { name: 'account', unique: true, comment: '账号', length: 40 })
    public account: string;

    /** 密码（md5,小写16进制) */
    @Column('varchar', { name: 'password', comment: '密码（md5,小写16进制)', length: 40 })
    public password: string;

    /** 姓名 */
    @Column('varchar', { name: 'name', comment: '姓名', length: 40 })
    public name: string;

    /** 电子邮箱 */
    @Column('varchar', { name: 'email', comment: '电子邮箱', length: 60 })
    public email: string;

    /** 最后选择的envid */
    @Column('varchar', { name: 'last_env', nullable: true, comment: '最后选择的envid', length: 20 })
    public lastEnv: string | null;

    /** 最后登录的ip */
    @Column('varchar', { name: 'last_login_ip', nullable: true, comment: '最后登录的ip', length: 100 })
    public lastLoginIp: string | null;

    /** 最后一次登录的时间 */
    @Column('datetime', { name: 'last_login_time', nullable: true, comment: '最后一次登录的时间' })
    public lastLoginTime: Date | null;

    /** 创建时间 */
    @Column('datetime', {
        name: 'create_time',
        nullable: true,
        comment: '创建时间',
        default: () => 'CURRENT_TIMESTAMP',
    })
    public createTime: Date | null;

    @Column('datetime', { name: 'update_time', nullable: true, default: () => 'CURRENT_TIMESTAMP' })
    public updateTime: Date | null;
}

export declare type WhereMockUser = FindOptionsWhere<MockUser>;

export declare type RecMockUser = DeepPartial<MockUser>;

export declare type SelectMockUser = FindOptionsSelect<MockUser>;

export declare type OrderMockUser = FindOptionsOrder<MockUser>;
