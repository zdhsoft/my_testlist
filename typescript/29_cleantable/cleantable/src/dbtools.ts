import { utils } from 'xmcommon';
import mysql from 'mysql2';
import { ERR } from './errorcode';
import { config } from './config';
import { getLogger } from 'xmcommon';
import { XCommRet } from '@zdhsoft/commret';
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
            const r = new XCommRet();
            r.setOK({ result, field });
            return r;
        } else {
            const r = new XCommRet();
            r.setError(ERR.ERR_FAIL, String(err));
            console.error(err);
            return r;
        }
    }

    public static async cleanTable(paramTableName: string, paramCurrIndex: number, paramAllCount: number) {
        const r = new XCommRet();
        do {
            log.info(`开始清理：${paramTableName}  => ${paramCurrIndex}/${paramAllCount}`);
            const strDelete = `DELETE FROM ${paramTableName}`;
            const strAdd = `ALTER TABLE ${paramTableName} ADD COLUMN ___k TINYINT ( 4 ) NOT NULL DEFAULT 0`;
            const strDrop = `ALTER TABLE ${paramTableName} DROP COLUMN ___k;`;

            const r1 = await DBTools.query(strDelete);
            if (r1.isNotOK) {
                log.error(r1);
                break;
            }

            const r2 = await DBTools.query(strAdd);
            if (r2.isNotOK) {
                log.error(r2);
            }
            const r3 = await DBTools.query(strDrop);
            if (r3.isNotOK) {
                log.error(r2);
            }
        } while (false);
        log.info('');
        return r;
    }
}
