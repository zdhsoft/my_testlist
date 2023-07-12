import { utils } from 'xmcommon';
import mysql from 'mysql2';
import { ERR } from './errorcode';
import { config } from './config';
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

const dbconfig = {
    connectionLimit: 1,
    database: config.database,
    host: config.host,
    port: config.port,
    user: config.user,
    password: config.password,
};

const pool = mysql.createPool(dbconfig);
pool.on('connection', () => {
    log.info('db pool connection...\n', JSON.stringify(dbconfig, null, 2));
});
/** mysql 操作返回结果 */
export interface IMysqlResult {
    fieldCount: number;
    affectedRows: number;
    insertId: number;
    serverStatus: number;
    warningCount: number;
    message: string;
    protocol41: boolean;
    changedRows: number;
}

export class DBTools {
    /**
     * 查找SQL查询
     * @param {string} paramSQL 查询语句
     * @param {[*]} paramValues 查询用到的值
     * @return {{code:number, result:{fieldCount:number, affectedRows:number, insertId:number, serverStatus:number,
     *  warningCount:number, message:string, protocol41:boolean, changedRows:number}, field:{[*]}, err:*}}
     */
    public static async query(paramSQL: string, paramValues: string[] = []) {
        const b = Date.now();
        const [err, result, field] = await utils.WaitClassFunctionEx(pool, 'query', paramSQL, paramValues);
        log.info('SQL:' + paramSQL + ' Time:' + (Date.now() - b) + 'ms');
        if (utils.isNull(err)) {
            return { code: ERR.ERR_OK, result: result as any, field, err: null };
        } else {
            console.error(err);
            return { code: ERR.ERR_FAIL, result: null, err, field: null };
        }
    }
}
