import * as mysql from 'mysql';
import { dbcfg } from './config';
import { getLogger, utils, XCommonRet } from 'xmcommon';
const log = getLogger(__filename);

const pool = mysql.createPool(dbcfg);
pool.on('connection', () => {
    log.info('db bool connection ...\n', JSON.stringify(dbcfg, null, 2));
});
export interface IDBColumnOrigin {
    TABLE_CATALOG: string;
    TABLE_SCHEMA: string;
    TABLE_NAME: string;
    COLUMN_NAME: string;
    ORDINAL_POSITION: number;
    COLUMN_DEFAULT?: string;
    IS_NULLABLE: string;
    DATA_TYPE: string;
    CHARACTER_MAXIMUM_LENGTH?: number;
    CHARACTER_OCTET_LENGTH?: number;
    NUMERIC_PRECISION?: number;
    NUMERIC_SCALE?: number;
    DATETIME_PRECISION?: number;
    CHARACTER_SET_NAME?: string;
    COLLATION_NAME?: string;
    COLUMN_TYPE: string;
    COLUMN_KEY: string;
    EXTRA: string;
    PRIVILEGES: string;
    COLUMN_COMMENT: string;
    GENERATION_EXPRESSION: string;
}

export interface IDBTableOrigin {
    TABLE_CATALOG: string;
    TABLE_SCHEMA: string;
    TABLE_NAME: string;
    TABLE_TYPE: string;
    ENGINE?: string;
    VERSION?: number;
    ROW_FORMAT?: string;
    TABLE_ROWS?: number;
    AVG_ROW_LENGTH?: number;
    DATA_LENGTH?: number;
    MAX_DATA_LENGTH?: number;
    INDEX_LENGTH?: number;
    DATA_FREE?: number;
    AUTO_INCREMENT?: number;
    CREATE_TIME?: Date;
    UPDATE_TIME?: Date;
    CHECK_TIME?: Date;
    TABLE_COLLATION?: string;
    CHECKSUM?: number;
    CREATE_OPTIONS?: string;
    TABLE_COMMENT: string;
}
export interface IDBIndexOrigin {
    Table: string;
    Non_unique: number;
    Key_name: string;
    Seq_in_index: number;
    Column_name: string;
    Collation: string;
    Cardinality: number;
    Sub_part: string;
    Packed: string;
    Null: string;
    Index_type: string;
    Comment: string;
    Index_comment: string;
}

export interface IDBIndexOriginEx {
    Table: string;
    Non_unique: number;
    Key_name: string;
    Column_name: string[];
    Collation: string;
    Cardinality: number;
    Sub_part: string;
    Packed: string;
    Null: string;
    Index_type: string;
    Comment: string;
    Index_comment: string;
}

// `CATALOG_NAME` varchar(512) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
// `SCHEMA_NAME` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
// `DEFAULT_CHARACTER_SET_NAME` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
// `DEFAULT_COLLATION_NAME` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
// `SQL_PATH` varchar(512) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL

export interface IDBSchemaOrigin {
    SCHEMA_NAME: string;
    DEFAULT_CHARACTER_SET_NAME: string;
    DEFAULT_COLLATION_NAME: string;
}

export interface ITableInfo {
    table: IDBTableOrigin;
    column: IDBColumnOrigin[];
    index: IDBIndexOriginEx[];
}

export class DBTool {
    /**
     * 查找SQL查询
     * @param {string} paramSQL 查询语句
     * @param {[*]} paramValues 查询用到的值
     * @return {{code:number, result:{fieldCount:number, affectedRows:number, insertId:number, serverStatus:number,
     *  warningCount:number, message:string, protocol41:boolean, changedRows:number}, field:{[*]}, err:*}}
     */
    public static async query<T = any>(paramSQL: string, paramValues: string[] = []) {
        const b = Date.now();
        const r = new XCommonRet<{ data: T; field: any[] }>();
        const [err, result, field] = await utils.WaitClassFunctionEx(pool, 'query', paramSQL, paramValues);
        log.info('SQL:' + paramSQL + ' Time:' + (Date.now() - b) + 'ms');
        if (utils.isNull(err)) {
            r.setOK({ data: result as any as T, field: field as any as any[] });
        } else {
            console.error(err);
            r.setError(-1, String(err));
        }
        return r;
    }

    public static async getSchema(paramDBName: string): Promise<XCommonRet<IDBSchemaOrigin>> {
        const r = new XCommonRet<IDBSchemaOrigin>();
        do {
            const result = await DBTool.query<IDBSchemaOrigin[]>(
                `select * from information_schema.SCHEMATA where SCHEMA_NAME= '${paramDBName}'`,
            );
            if (result.isFail) {
                r.setError(result.err, result.msg);
                break;
            }
            const list = result.data?.data as IDBSchemaOrigin[];
            if (!(Array.isArray(list) && list.length > 0)) {
                r.setError(-1, `没有找到数据库名为:${paramDBName}的定义!`);
            } else {
                r.setOK(list[0]);
            }
        } while (false);
        return r;
    }

    public static async getIndex(paramDBName: string, paramTableName: string): Promise<XCommonRet<IDBIndexOriginEx[]>> {
        const r = new XCommonRet<IDBIndexOriginEx[]>();
        do {
            //
            const result = await DBTool.query<IDBIndexOrigin[]>(`show index from ${paramDBName}.${paramTableName}`);
            if (result.isFail) {
                r.setError(result.err, result.msg);
                break;
            }
            const m = new Map<string, IDBIndexOriginEx>();
            result.data?.data.forEach((v) => {
                //
                let item = m.get(v.Key_name);
                if (utils.isNull(item)) {
                    item = {
                        Table: v.Table,
                        Non_unique: v.Non_unique,
                        Key_name: v.Key_name,
                        Column_name: [],
                        Collation: v.Collation,
                        Cardinality: v.Cardinality,
                        Sub_part: v.Sub_part,
                        Packed: v.Packed,
                        Null: v.Null,
                        Index_type: v.Index_type,
                        Comment: v.Comment,
                        Index_comment: v.Index_comment,
                    };
                    m.set(v.Key_name, item);
                }
                item?.Column_name.push(v.Column_name);
            });
            r.setOK([...m.values()]);
        } while (false);
        return r;
    }

    public static async getTableColumns(
        paramDBName: string,
        paramTableName: string,
    ): Promise<XCommonRet<IDBColumnOrigin[]>> {
        const r = new XCommonRet<IDBColumnOrigin[]>();
        do {
            //
            const result = await DBTool.query<IDBColumnOrigin[]>(
                `select * from information_schema.columns where table_schema = '${paramDBName}' and table_name = '${paramTableName}'`,
            );
            if (result.isOK) {
                r.setOK(result.data?.data);
            } else {
                r.assignFrom(result as any);
            }
        } while (false);
        return r;
    }

    public static async getTables(paramDBName: string): Promise<XCommonRet<IDBTableOrigin[]>> {
        const r = new XCommonRet<IDBTableOrigin[]>();
        do {
            //
            const result = await DBTool.query<IDBTableOrigin[]>(
                `select * from information_schema.TABLES where table_schema = '${paramDBName}'`,
            );
            if (result.isNotOK) {
                r.assignFrom(result as any);
                break;
            } else {
                r.setOK(result.data?.data);
            }
        } while (false);
        return r;
    }
}
