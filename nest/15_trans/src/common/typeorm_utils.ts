import { Like, In, DataSource, EntityManager } from 'typeorm';
import { utils, XCommonRet } from 'xmcommon';
import { EnumErrorCode } from '../error/error_code';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

export class XTypeormUtils {
    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`%${paramValue}%`);
        }
    }

    public static in(param: unknown[]) {
        return In(param);
    }

    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like_begin(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`${paramValue}%`);
        }
    }
    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like_end(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`%${paramValue}`);
        }
    }
    /**
     * 删除对象中，属性值为null或undefined的属性
     * @param paramWhere 要处理的对象
     * @returns 处理的对象
     */
    public static cleanNull(paramWhere: any) {
        const delKey: string[] = [];
        for (const k in paramWhere) {
            if (utils.isNull(paramWhere[k])) {
                delKey.push(k);
            }
        }

        for (const k of delKey) {
            delete paramWhere[k];
        }
        return paramWhere;
    }

    /**
     * 处理bigint的参数
     * @param paramValue 要处理的值
     */
    public static bigInt(paramValue?: number): string | undefined {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return String(paramValue);
        }
    }

    /**
     * 事物
     * @param paramDS TypeORM的数据源
     * @param paramTransName 事物名称，没有传入空串或null
     * @param paramRunInTransaction 执行事物的函数
     */
    public static async transaction(
        paramDS: DataSource,
        paramTransName: string | null = '',
        paramRunInTransaction: (paramMgr: EntityManager) => Promise<XCommonRet>,
    ) {
        const queryRunner = paramDS.createQueryRunner();
        await queryRunner.startTransaction();

        let transTag = '';
        if (!utils.isEmpty(paramTransName)) {
            transTag = `[${paramTransName}]`;
        }

        const r = new XCommonRet();
        try {
            // 执千事物中的逻辑
            const result = await paramRunInTransaction(queryRunner.manager);
            if (result.isNotOK) {
                log.warn(`事物${transTag}执行失败:${JSON.stringify(result)}`);
                await queryRunner.rollbackTransaction();
            } else {
                await queryRunner.commitTransaction();
            }
            r.assignFrom(result);
        } catch (e) {
            r.setError(EnumErrorCode.TRANSACTION_EXCEPTION, `事物异常:${String(e)}`);
            log.warn(`事物${transTag}异常:${JSON.stringify(r)}`);
            await queryRunner.rollbackTransaction();
        }
    }
}
