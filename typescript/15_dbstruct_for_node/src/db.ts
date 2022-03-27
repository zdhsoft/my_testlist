import * as mysql from 'mysql';
import { dbcfg } from './config';
import { getLogger, utils, XCommonRet } from 'xmcommon';
const log = getLogger(__filename);

// const pool = mysql.createPool(dbconfig);
// pool.on('connection', () => {
//     log.info('db pool connection...\n', JSON.stringify(dbconfig, null, 2));
// });

const pool = mysql.createPool(dbcfg);
pool.on('connection', () => {
    log.info('db bool connection ...\n', JSON.stringify(dbcfg, null, 2));
});

export interface IDBTable {
    isView: boolean;
    Name: string;
    Engine?: string;
    Version?: number;
    Row_format?: string;
    Rows?: number;
    Avg_row_length?: number;
    Data_length?: number;
    Max_data_length?: number;
    Index_length?: number;
    Data_free?: number;
    Auto_increment?: number;
    Create_time?: Date;
    Update_time?: Date;
    Check_time?: Date;
    Collation?: string;
    Checksum?: string;
    Create_options?: string;
    Comment?: string;
}

export class XTableInfo implements IDBTable {
    public get isView() {
        return this.Comment === 'VIEW';
    }
    public Name: string;
    public Engine?: string;
    public Version?: number;
    public Row_format?: string | undefined;
    public Rows?: number | undefined;
    public Avg_row_length?: number | undefined;
    public Data_length?: number | undefined;
    public Max_data_length?: number | undefined;
    public Index_length?: number | undefined;
    public Data_free?: number | undefined;
    public Auto_increment?: number | undefined;
    public Create_time?: Date | undefined;
    public Update_time?: Date | undefined;
    public Check_time?: Date | undefined;
    public Collation?: string | undefined;
    public Checksum?: string | undefined;
    public Create_options?: string | undefined;
    public Comment?: string | undefined;
    public constructor(param: IDBTable) {
        this.Name = param.Name;
        this.Engine = param.Engine;
        this.Version = param.Version;
        this.Row_format = param.Row_format;
        this.Rows = param.Rows;
        this.Avg_row_length = param.Avg_row_length;
        this.Data_length = param.Data_length;
        this.Max_data_length = param.Max_data_length;
        this.Index_length = param.Index_length;
        this.Data_free = param.Data_free;
        this.Auto_increment = param.Auto_increment;
        this.Create_time = param.Create_time;
        this.Update_time = param.Update_time;
        this.Check_time = param.Check_time;
        this.Collation = param.Collation;
        this.Checksum = param.Checksum;
        this.Create_options = param.Create_options;
        this.Comment = param.Comment;
    }
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
        const r = new XCommonRet<{data: T, field: any[]}>();
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

    public static async getTables(): Promise<XCommonRet<XTableInfo[]>> {
        const r = new XCommonRet<XTableInfo[]>();
        do {
            //
            const result = await DBTool.query<IDBTable[]>('show table status');
            const retTabs: XTableInfo[] = [];
            if (result.isNotOK) {
                r.assignFrom(result as any);
                break;
            } else {
                const tables: IDBTable[] | undefined = result.data?.data;
                if (Array.isArray(tables)) {
                    for (const tab of tables) {
                        retTabs.push(new XTableInfo(tab));
                    }
                }
                r.setOK(retTabs);
            }
        } while (false);
        return r;
    }
}
