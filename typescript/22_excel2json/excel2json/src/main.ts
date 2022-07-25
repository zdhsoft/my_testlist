/*************************************************************************
 * Copyright(c) 2017-2022,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 zdhsoft      创建文件            2022-07-25
 *************************************************************************/

import fs from 'fs';
// import path from 'path';
import { XExcelUtils } from './excel_utils';

const xlsxfile = './testdata/Build.xlsx';
const t = './testdata/Build.json';
import { getLogger, XCommonRet, utils } from 'xmcommon';
import { EnumOutType } from './constant';
const log = getLogger(__filename);

interface ITableInfo {
    sheetName: string;
    describe: string;
    filename: string;
    type: string;
}

const tablelist = 'tablelist';

class XColumnInfo {
    public constructor() {
        //
    }
}

class XTitleInfo {
    public columns: XColumnInfo[] = [];
    public constructor() {
        //
    }
}

class XTableInfo {
    public types: EnumOutType[];
    public sheetName: string;
    public fileName: string;
    public describe: string;

    public titleInfo: XTitleInfo;
    public constructor(paramTypes: string, paramSheetName: string, paramFileName: string, paramDescribe = '') {
        this.types = [];
        this.sheetName = paramSheetName;
        this.fileName = paramFileName;
        this.describe = paramDescribe;
        this.setTypes(paramTypes);
    }

    public setTypes(paramTypes: string) {
        if (paramTypes.includes(EnumOutType.CLIENT)) {
            this.types.push(EnumOutType.CLIENT);
        }
        if (paramTypes.includes(EnumOutType.SERVER)) {
            this.types.push(EnumOutType.SERVER);
        }
    }

    public init(paramSheetData: any[]): XCommonRet {
        const r = new XCommonRet();
        do {
            //
        } while (false);
        return r;
    }

    public isOut(paramTypes: string) {
        for (const t of this.types) {
            if (paramTypes.includes(t)) {
                return true;
            }
        }
        return false;
    }
}

const tableInfo: XTableInfo[] = [];

function initTable(paramTableInfoList: ITableInfo[], paramExcelData: any): XCommonRet {
    tableInfo.splice(0);
    const r = new XCommonRet();
    do {
        //
        if (utils.isNull(paramTableInfoList)) {
            r.setError(-11, `tablelist不存在!`);
            break;
        }

        for (const info of paramTableInfoList) {
            log.info(`处理:${info.sheetName}:${info.describe}`);
            const s = new XTableInfo(info.type, info.sheetName, info.filename, info.describe);
            log.info(`  ==>${JSON.stringify(s)}`);

            const sheet = paramExcelData[info.sheetName];
            if (utils.isNull(sheet)) {
                r.setError(-12, `没有找到表名为:${info.sheetName}的表， 请检查一下配置!`);
                break;
            }

            const initResult = s.init(sheet);
            if (initResult.isNotOK) {
                r.assignFrom(initResult);
                r.addErrorPre(`初始化:${info.sheetName}:${info.describe}`);
            }
            tableInfo.push(s);
        }
        if (r.isNotOK) {
            break;
        }
    } while (false);
    return r;
}

function main() {
    log.info('begin:');
    const r = new XCommonRet();
    do {
        const result = XExcelUtils.readExcelByFile(xlsxfile);
        if (result.isNotOK) {
            r.assignFrom(r);
            return;
        }
        const excelData: any = result.data;
        fs.writeFileSync(t, JSON.stringify(excelData, null, 2), 'utf-8');

        const initResult = initTable(excelData[tablelist], excelData);
        if (initResult.isNotOK) {
            r.assignFrom(initResult);
            break;
        }
    } while (false);
    log.info(`finish!:${JSON.stringify(r)}`);
    return r;
}

function boot() {
    try {
        main();
    } catch (e) {
        log.info(e);
    }
}

boot();
