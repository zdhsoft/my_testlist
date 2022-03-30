/* eslint-disable prettier/prettier */
import { dbcfg } from './config';
import { DBTool, IDBTableOrigin, IDBSchemaOrigin, ITableInfo, IDBColumnOrigin, IDBIndexOriginEx } from './db';
import { getLogger, XCommonRet, utils } from 'xmcommon';
import fs from 'fs';
import path from 'path';
const log = getLogger(__filename);

// INSERT INTO `` (`TABLE_NAME`, `ENGINE`, `VERSION`, `ROW_FORMAT`, `TABLE_ROWS`, `AVG_ROW_LENGTH`, `DATA_LENGTH`, `MAX_DATA_LENGTH`, `INDEX_LENGTH`, `DATA_FREE`, `AUTO_INCREMENT`, `CREATE_TIME`, `UPDATE_TIME`, `CHECK_TIME`, `TABLE_COLLATION`, `CHECKSUM`, `CREATE_OPTIONS`, `TABLE_COMMENT`) VALUES ('wkinfoword', 'InnoDB', 10, 'Dynamic', 0, 0, 16384, 0, 0, 0, NULL, '2022-03-21 10:51:30', NULL, NULL, 'utf8_general_ci', NULL, '', '');

function getCName(paramColumn: IDBColumnOrigin) {
    let r = paramColumn.COLUMN_NAME;
    if (paramColumn.COLUMN_KEY === 'PRI') {
        r = r + '**(主键)**';
    }
    if(utils.isNotNull(paramColumn.EXTRA) && paramColumn.EXTRA.indexOf('auto_increment') >= 0) {
        r = r + '[自增]';
    }
    return r;
}

function getCIsNotNull(paramColumn: IDBColumnOrigin) {
    if (paramColumn.IS_NULLABLE === 'YES') {
        return '是';
    }
    if (paramColumn.COLUMN_KEY === 'PRI') {
        return '是';
    }
    return '';
}

async function exportMarkDown(
    paramTitle: string,
    paramSchema: IDBSchemaOrigin,
    paramTables: ITableInfo[],
    paramFileName: string,
) {
    const r = new XCommonRet();
    do {
        const filename = path.isAbsolute(paramFileName) ? paramFileName : path.join(process.cwd(), paramFileName);
        const dir = path.dirname(filename);
        const makeResult = utils.mkdirsSyncEx(dir);
        if (!makeResult.ret) {
            r.setError(-1, makeResult.msg);
            break;
        }

        if (utils.fileExistsSync(filename)) {
            if (!utils.isFileSync(filename)) {
                r.setError(-1, `${filename}：已经存在，但是它不是文件`);
                break;
            }
        }

        const fd = fs.openSync(filename, 'w+');
        fs.writeFileSync(fd, '# ' + paramTitle + '\n\n');
        fs.writeFileSync(fd, '[TOC]\n\n');
        fs.writeFileSync(fd, '## 数据库构结:' + paramSchema.SCHEMA_NAME + '\n\n');
        fs.writeFileSync(fd, '| 数据库名 | 字符集 | 排序规则 |\n');
        fs.writeFileSync(fd, '|:----|:----|:----|\n');
        fs.writeFileSync(
            fd,
            `| ${paramSchema.SCHEMA_NAME} | ${paramSchema.DEFAULT_CHARACTER_SET_NAME} | ${paramSchema.DEFAULT_COLLATION_NAME} |\n\n`,
        );
        fs.writeFileSync(fd, '## 表结构\n\n');

        for (const t of paramTables) {
            const { table, column, index } = t;
            fs.writeFileSync(fd, `### ${table.TABLE_NAME}(${t.table.TABLE_COMMENT || ''})\n\n`);
            fs.writeFileSync(fd, '| 存储引擎 | 行格式 | 自增 | 表排序规则 | 表注释 |\n');
            fs.writeFileSync(fd, '|:---|:---|:---|:---|:---|\n');
            fs.writeFileSync(
                fd,
                `| ${table.ENGINE} | ${table.ROW_FORMAT} | ${utils.isNull(table.AUTO_INCREMENT) ? '' : 'YES'} | ${
                    table.TABLE_COLLATION || ''
                } | ${table.TABLE_COMMENT} |\n\n`,
            );
            fs.writeFileSync(fd, '#### 表结构\n\n');
            fs.writeFileSync(fd, '| 字段名 | 类型 | 字符集 | 排序规则 |非空| 缺省值 | 注释 |\n');
            fs.writeFileSync(fd, '|:---|:---|:---|:---|:---|:---|:---|\n');
            for (const c of column) {
                fs.writeFileSync(
                    fd,
                    `| ${getCName(c)} | ${c.COLUMN_TYPE}|${c.CHARACTER_SET_NAME || ''} | ${c.COLLATION_NAME || ''}|${
                        getCIsNotNull(c)}| ${c.COLUMN_DEFAULT || ''} | ${c.COLUMN_COMMENT} |\n`,
                );
            }
            fs.writeFileSync(fd, '\n#### 索引\n\n');
            fs.writeFileSync(fd, '| 索引名 | 类型 | 唯一 |字段列表 |\n');
            fs.writeFileSync(fd, '|:---|:---|:---|:---|\n');
            for (const i of index) {
                fs.writeFileSync(fd, `|${i.Key_name}|${i.Index_type}|${(i.Non_unique === 0)? '是' : ''}|${i.Column_name.join(',')}|\n`);
            }
            fs.writeFileSync(fd, '\n');
        }
        fs.closeSync(fd);
    } while (false);
    return r;
}

async function main() {
    const r = new XCommonRet();
    do {
        const list: ITableInfo[] = [];
        const db = dbcfg.database as string;

        const schemaReuslt = await DBTool.getSchema(db);
        if (schemaReuslt.isNotOK) {
            r.assignFrom(schemaReuslt);
            break;
        }

        const schema = schemaReuslt.data as IDBSchemaOrigin;

        const tableResult = await DBTool.getTables(db);
        if (tableResult.isNotOK) {
            r.assignFrom(tableResult);
            break;
        }

        const tables = tableResult.data as IDBTableOrigin[];
        let n = 0;
        for (const t of tables) {
            if (n < 10) {
                log.info('----------------------------------\n' + JSON.stringify(t, null, 2));
            }
            n++;
            const columnResult = await DBTool.getTableColumns(db, t.TABLE_NAME);
            if (columnResult.isNotOK) {
                r.assignFrom(columnResult);
                break;
            }
            const indexResult = await DBTool.getIndex(db, t.TABLE_NAME);
            if (indexResult.isNotOK) {
                r.assignFrom(indexResult);
                break;
            }
            list.push({
                table: t,
                column: columnResult.data as IDBColumnOrigin[],
                index: indexResult.data as IDBIndexOriginEx[],
            });
        }
        if (r.isNotOK) {
            break;
        }

        await exportMarkDown('链融数据库表结构定义', schema, list, './db.md');
    } while (false);
    if (r.isNotOK) {
        log.error(r.getErrorInfo());
    } else {
        log.info('ok');
    }
    process.exit(0);
}
main();
