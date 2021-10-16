const mysql = require('mysql');
let { utils } = require("xmcommon");

const dbconfig = {
    host    : '127.0.0.1',
    user    : 'root',
    password: 'root123!!!',
    database: 'cmmi',
    port    : 3306,
};

let dbflag = false;

let pool = mysql.createPool(dbconfig);
pool.on('connection', () => {
    console.log("db pool connection...\n", JSON.stringify(dbconfig, null, 2));
    dbflag = true;
});

const ERR = {
    /** 成功 */
    ERR_OK: 0,
    /** 成败 */
    ERR_FAIL: -1,
}

class DBTool {

    static getDBFlag() {
        return dbflag;
    }

    /**
     * 查找SQL查询
     * @param {string} paramSQL 查询语句
     * @param {[*]} paramValues 查询用到的值
     * @return {{code:number, result:{fieldCount:number, affectedRows:number, insertId:number, serverStatus:number,
     *  warningCount:number, message:string, protocol41:boolean, changedRows:number}, field:{[*]}, err:*}}
     */
    static async query(paramSQL, paramValues = []) {
        let curr = Date.now();

        let [err, result, field] = await utils.WaitClassFunctionEx(pool, "query", paramSQL, paramValues);
        if (utils.isNull(err)) {
            console.log('SQL:' + paramSQL + 'values:' + paramValues.join() + ' time:' + (Date.now()-curr) + 'ms');
            return { code: ERR.ERR_OK, result, field, err: null };
        } else {
            console.error('SQL:' + paramSQL + ' time:' + (Date.now()-curr) + 'ms');
            console.error(err);
            return { code: ERR.ERR_FAIL, result: null, err, field: null };
        }
    }

    /**
     * 插入记录
     * 注意paramRecordObject中的名称要和字段名一样,只支持一层数据
     * @param {string} paramTableName 表名
     * @param {object} paramRecordObject 对象记录值
     * @return {{code:number, result:IMysqlResult, err:object, insertId:*}} 执行结果 code==0表示执行成功，code==-1表示有异常
     */
    static async insertRecord(paramTableName, paramRecordObject) {
        let keys = [];
        let values = [];
        let p = [];
        for (let k in paramRecordObject) {
            keys.push(`\`${k}\``);
            values.push(paramRecordObject[k]);
            p.push('?');
        }
        let strRet = ';';
        let strSQL = `INSERT INTO ${paramTableName} (${keys.join(",")}) VALUES (${p.join(",")}) ${strRet}`;
        console.log("insert:" + strSQL + " values:[" + values.join(",") + "]");
        let r = await this.query(strSQL, values);
        if (r.code === 0 && utils.isNotNull(r.result)) {
            r.insertId = r.result.insertId;
        } else {
            // tslint:disable-next-line: max-line-length
            console.error(`insert error: \ncode:${r.err.code}, \nerrno:${r.err.errno}, \nmessage:${r.err.message}, \nSQL:${r.err.sql}`);
            r.insertId = -1;
        }
        return r;
    }

    /**
     * 更新指定的记录
     * 类似于field=field+1的，请放到paramOtherChangeList数组中
     * @param {string} paramTableName 要更新的数据库表名
     * @param {*} paramChanges 要更新的字段和名称
     * @param {*} paramConds 比较的条件
     * @param {[string]} paramOtherChangeList 其它要更新的字段列表
     */
    static async updateRecord(paramTableName, paramChanges, paramConds,  paramOtherChangeList = []) {
        let changes = [];
        if (Array.isArray(paramOtherChangeList)) {
            changes = changes.concat(paramOtherChangeList);
        }
        let values = [];
        for (let k in paramChanges) {
            changes.push(`${k}=?`);
            values.push(paramChanges[k]);
        }

        let conds = [];
        for (let k in paramConds) {
            conds.push(`${k}=?`);
            values.push(paramConds[k]);
        }
        let strSQL = `update ${paramTableName} set ${changes.join(", ")} where ${conds.join(" and ")};`;
        console.log("update:" + strSQL, "[", values.join(','), "]");
        let r = await this.query(strSQL, values);
        if (r.code === 0 && utils.isNotNull(r.result)) {
            r.insertId = r.result.insertId;
        } else {
            // tslint:disable-next-line: max-line-length
            console.error(`update error: \ncode:${r.err.code}, \nerrno:${r.err.errno}, \nmessage:${r.err.message}, \nSQL:${r.err.sql}`);
            r.insertId = -1;
        }
        return r;
    }

    /**
     * 只取查询到的第一个记录
     * @param {string} paramSQL
     * @param {[]} paramValues
     * @return {*} 没有，则返回null，否则返回第一个
     */
    static async GetRecordOne(paramSQL, paramValues = []) {
        let r = await this.query(paramSQL, paramValues);
        if (r.code !== ERR.ERR_OK) {
            return null;
        }
        if (r.result.length === 0) {
            return null;
        }
        return r.result[0];
    }
    /**
     * 取指定表的记录数
     * @param {string} paramTableName 要查询的表名
     * @param {string} paramConds where后面的SQL子句
     * @return {number} 返回的记录数
     */
    static async GetRecordCount(paramTableName, paramConds = null) {
        let strSQL = `select count(*) as cnt from ${paramTableName}`;
        if (utils.isNotNullOrEmptyString(paramConds)) {
            strSQL += ` where ${paramConds} `;
        }
        let r = await this.GetRecordOne(strSQL);
        if (utils.isNull(r)) {
            return 0;
        } else {
            return r.cnt;
        }
    }

    /**
     * 取查询的记录集
     * @param {String} paramSQL 查询的SQL语句
     * @param {[]} paramArrayParamList SQL用到的参数
     * @return {[]} 返回记录集，null表示没有记录
     */
    static async GetRecordListByQuery(paramSQL, paramArrayParamList) {
        let r = await this.query(paramSQL, paramArrayParamList);
        if (r.code !== ERR.ERR_OK) {
            console.error("查询数据库失败,sql:" + paramSQL + ",err:" + r.err);
            return null;
        }

        if (r.result.length === 0) {
            return null;
        }
        return r.result;
    }
    /**
     * 取查询的记录集
     * @param {string} paramTableName 表名
     * @param {*} paramConds
     * @return {[]}
     */
    static async GetRecordList(paramTableName, paramConds) {
        let values = [];
        let conds = [];
        for (let k in paramConds) {
            conds.push(`${k}=?`);
            values.push(paramConds[k]);
        }
        let strSQL = `select * from ${paramTableName} where ${conds.join(" and ")};`;
        console.log(strSQL, "[", values, "]");
        let r = await this.query(strSQL, values);
        if (r.code !== ERR.ERR_OK) {
            console.error("查询数据库失败,sql:" + strSQL + ",err:" + r.err);
            return [];
        }

        if (r.result.length === 0) {
            return [];
        }
        return r.result;
    }
}

exports.DBTool = DBTool;
