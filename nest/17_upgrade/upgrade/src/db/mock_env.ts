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

@Index('envid', ['env'], { unique: true })
@Entity('mock_env', { schema: 'mock-test' })
export class MockEnv {
    public static getTableName() {
        return `mock_env`;
    }

    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    public id: number;

    /** 环境定义 */
    @Column('varchar', { name: 'env', unique: true, comment: '环境定义', length: 20 })
    public env: string;

    /** 环境说明 */
    @Column('varchar', { name: 'info', nullable: true, comment: '环境说明', length: 255 })
    public info: string | null;

    /** 环境id */
    @Column('varchar', { name: 'env_id', nullable: true, comment: '环境id', length: 5 })
    public envId: string | null;

    @Column('datetime', { name: 'create_time', nullable: true, default: () => 'CURRENT_TIMESTAMP' })
    public createTime: Date | null;

    @Column('datetime', { name: 'update_time', nullable: true, default: () => 'CURRENT_TIMESTAMP' })
    public updateTime: Date | null;
}

export declare type WhereMockEnv = FindOptionsWhere<MockEnv>;

export declare type RecMockEnv = DeepPartial<MockEnv>;

export declare type SelectMockEnv = FindOptionsSelect<MockEnv>;

export declare type OrderMockEnv = FindOptionsOrder<MockEnv>;
