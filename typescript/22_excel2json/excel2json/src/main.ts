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
import { EnumDataBaseType, EnumDataType, EnumOutType, XTypeUtils } from './constant';
const log = getLogger(__filename);

interface ITableInfo {
    sheetName: string;
    describe: string;
    filename: string;
    type: string;
}

const tablelist = 'tablelist';

class XColumnInfo {
    public name: string;
    public key: string;
    public type: EnumDataBaseType;
    public isArray: boolean;
    public outType: string;
    public constructor(paramKey: string, paramName: string) {
        this.name = paramName;
        this.key = paramKey;
        this.type = EnumDataBaseType.UNKNOWN;
        this.isArray = false;
        this.outType = '';
    }
    public toJSON() {
        return {
            name: this.name,
            key: this.key,
            type: this.type,
            isArray: this.isArray,
            outType: this.outType,
        };
    }
}

class XTitleInfo {
    public columns: XColumnInfo[] = [];
    public columnKeyMap = new Map<string, XColumnInfo>();
    public columnNameMap = new Map<string, XColumnInfo>();
    public constructor() {
        //
    }
    public reset() {
        this.columns = [];
        this.columnKeyMap.clear();
        this.columnNameMap.clear();
    }

    public toJSON() {
        return {
            columns: this.columns,
        };
    }

    public getColumnByKey(paramKey: string): XCommonRet<XColumnInfo> {
        const r = new XCommonRet<XColumnInfo>();
        do {
            if (!utils.isString(paramKey)) {
                r.setError(51, `输入的key:${paramKey}不是字符串`);
                break;
            }
            const k = paramKey.trim();
            if (utils.isEmpty(k)) {
                r.setError(52, `输入的key是空串!`);
                break;
            }
            const col = this.columnKeyMap.get(k) as XColumnInfo;
            if (utils.isNull(col)) {
                r.setError(53, `未找到key:${k}的列定义`);
                break;
            }
            r.setOK(col);

            this.columns.push(col);
        } while (false);
        return r;
    }

    public addColumn(paramKey: string, paramName: string): XCommonRet<XColumnInfo> {
        const r = new XCommonRet<XColumnInfo>();
        do {
            if (!utils.isString(paramKey)) {
                r.setError(41, `输入的key:${paramKey}不是字符串`);
                break;
            }
            if (!utils.isString(paramName)) {
                r.setError(42, `输入的Name:${paramName}不是字符串`);
                break;
            }
            const k = paramKey.trim();
            const n = paramName.trim();
            if (utils.isEmpty(k)) {
                r.setError(43, `输入的key是空串!`);
                break;
            }

            if (utils.isEmpty(n)) {
                r.setError(44, `输入的name是空串!`);
                break;
            }

            if (this.columnKeyMap.has(k)) {
                r.setError(45, `输入的key:${k}是重复的!`);
                break;
            }

            if (this.columnNameMap.has(n)) {
                r.setError(46, `输入的name:${n}是重复的!`);
                break;
            }

            const columnInfo = new XColumnInfo(k, n);
            this.columnKeyMap.set(k, columnInfo);
            this.columnNameMap.set(n, columnInfo);
            r.setOK(columnInfo);
        } while (false);
        return r;
    }
}



class XTableInfo {
    public types: EnumOutType[];
    public sheetName: string;
    public fileName: string;
    public describe: string;

    public titleInfo: XTitleInfo;
    public data: any[];
    public outdata: any[];
    public constructor(paramTypes: string, paramSheetName: string, paramFileName: string, paramDescribe = '') {
        this.types = [];
        this.sheetName = paramSheetName;
        this.fileName = paramFileName;
        this.describe = paramDescribe;
        this.setTypes(paramTypes);
        this.titleInfo = new XTitleInfo();
        this.data = [];
    }

    public setTypes(paramTypes: string) {
        if (paramTypes.includes(EnumOutType.CLIENT)) {
            this.types.push(EnumOutType.CLIENT);
        }
        if (paramTypes.includes(EnumOutType.SERVER)) {
            this.types.push(EnumOutType.SERVER);
        }
    }

    public toJSON() {
        return {
            sheetName: this.sheetName,
            describe: this.describe,
            types: this.types,
            fileName: this.fileName,
            title: this.titleInfo,
            data: this.data,
        };
    }

    public init(paramSheetData: any[]): XCommonRet {
        const r = new XCommonRet();
        do {
            this.titleInfo.reset();
            //
            if (!Array.isArray(paramSheetData)) {
                //
                r.setError(-21, `初始化表不是数组!`);
                break;
            }

            if (paramSheetData.length < 3) {
                r.setError(-22, `初始化表的表头小于3行!`);
                break;
            }

            const keyName = paramSheetData[0];
            if (utils.isNull(keyName)) {
                r.setError(-23, `定义Key和Name的第一行为:${keyName}`);
                break;
            }
            if (!utils.isObject(keyName)) {
                r.setError(-24, `定义Key和Name的第一行为:${keyName}, 不是object类型!`);
                break;
            }
            // 初始化name,key
            for (const key in keyName) {
                const name = keyName[key];
                const addResult = this.titleInfo.addColumn(key, name);
                if (addResult.isNotOK) {
                    r.assignFrom(addResult);
                    break;
                }
            }
            if (r.isNotOK) {
                break;
            }
            // 初始化类型
            const colType = paramSheetData[1];
            if (utils.isNull(colType)) {
                r.setError(-23, `定义类型的第二行为:${colType}`);
                break;
            }
            if (!utils.isObject(keyName)) {
                r.setError(-24, `定义类型的第二行为:${colType}, 不是object类型!`);
                break;
            }
            for (const key in colType) {
                let t: string = colType[key];
                if (utils.isNull(t)) {
                    r.setError(-26, `定义的类型值为:${t}, 不是有效的类型!`);
                    break;
                }
                if (!utils.isString(t)) {
                    r.setError(-25, `定义类型值值为:${t}, 不是字符串类型`);
                    break;
                }
                t = t.trim();
                const type = XTypeUtils.baseType(t as EnumDataType);
                if (type === EnumDataBaseType.UNKNOWN) {
                    r.setError(-27, `定义的类型值为:${t}, 不是预设的类型!`);
                    break;
                }

                const isArray = XTypeUtils.isArray(t as EnumDataType);
                const getResult = this.titleInfo.getColumnByKey(key);
                if (getResult.isNotOK) {
                    r.assignFrom(getResult);
                    r.addErrorPre(`实始化类型:Key=${key}, type:${t}`);
                    break;
                }

                const column = getResult.data as XColumnInfo;
                column.isArray = isArray;
                column.type = type;
            }
            // 初始化输出类型
            const outType = paramSheetData[2];
            if (utils.isNull(outType)) {
                r.setError(-28, `定义类型的第三行为:${outType}`);
                break;
            }
            if (!utils.isObject(keyName)) {
                r.setError(-29, `定义类型的第三行为:${outType}, 不是object类型!`);
                break;
            }
            for (const key in outType) {
                let t: string = outType[key];
                if (utils.isNull(t)) {
                    r.setError(-30, `定义的输出类型值为:${t}, 不是有效的类型!`);
                    break;
                }
                if (!utils.isString(t)) {
                    r.setError(-31, `定义类输出类型值为:${t}, 不是字符串类型`);
                    break;
                }
                t = t.trim();
                const getResult = this.titleInfo.getColumnByKey(key);
                if (getResult.isNotOK) {
                    r.assignFrom(getResult);
                    r.addErrorPre(`实始化输出类型:Key=${key}, 输出类型:${t}`);
                    break;
                }

                const column = getResult.data as XColumnInfo;
                column.outType = t;
            }
            // 假加数据
            const dataLength = paramSheetData.length;
            for (let rowIndex = 3; rowIndex < dataLength; rowIndex++) {
                this.data.push(paramSheetData[rowIndex]);
            }

            const makeResult = this.makeOutData();
            if (makeResult.isNotOK) {
                r.assignFrom(makeResult);
                break;
            }
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

    private makeOutData(): XCommonRet {
        const r = new XCommonRet();
        do {
            const outData: any[] = [];
            const data = this.data;

            for (let i = 0; i < data.length; i++) {
                const o = data[i];
                const row = i + 3;
                if (!utils.isObject(o)) {
                    r.setError(-50, `第${row}行:${o}的数据不是有效对象!`);
                    continue;
                }

                const newData: any = {};

                for (const key in o) {
                    const getResult = this.titleInfo.getColumnByKey(key);
                    if (getResult.isNotOK) {
                        r.assignFrom(getResult);
                        r.addErrorPre(`未找到sheet:${this.sheetName},key:${key}的定义信息>`);
                        continue;
                    }
                    const column = getResult.data as XColumnInfo;
                    if (!this.isOut(column.outType)) {
                        continue;
                    }
                    let value = o[key];
                    const type = column.type;
                    let newValue: any;

                    if (column.isArray) {
                        if (utils.isString(value)) {
                            value = value.trim();
                            if (utils.isEmpty(value)) {
                                newValue = [];
                            } else {
                                const valueArray = utils.JsonParse<[]>(value) as any[];
                                if (!Array.isArray(valueArray)) {
                                    r.setError(-51, `第${row}行:${key}=${value}的数据不是有效数组!`);
                                    break;
                                }
                                for (let valueIndex = 0; valueIndex < valueArray.length; valueIndex++) {
                                    let item = valueArray[valueIndex];
                                    if (type === EnumDataBaseType.STRING) {
                                        if (
                                            utils.isInteger(item) ||
                                            utils.isBoolean(item) ||
                                            utils.isNumber(item) ||
                                            utils.isObject(item) ||
                                            utils.isArray(item)
                                        ) {
                                            item = String(item);
                                        } else if (utils.isString(value)) {
                                            value = value.trim();
                                        }
                                    }
                                    if (!XTypeUtils.checkType(type, item)) {
                                        r.setError(
                                            -52,
                                            `第${row}行:${key}=${value}的第${valueIndex}个值为${item}, 不是指定的类型!`,
                                        );
                                        break;
                                    }
                                }
                                if (r.isNotOK) {
                                    break;
                                }
                                newValue = valueArray;
                            }
                        } else if (utils.isNull(value)) {
                            newValue = [];
                        } else {
                            r.setError(-53, `第${row}行:${key}=${value}不是有效数组!`);
                            break;
                        }
                    } else {
                        if (type === EnumDataBaseType.STRING) {
                            if (
                                utils.isInteger(value) ||
                                utils.isBoolean(value) ||
                                utils.isNumber(value) ||
                                utils.isObject(value) ||
                                utils.isArray(value)
                            ) {
                                value = String(value);
                            } else if (utils.isNull(value)) {
                                value = '';
                            } else if (utils.isString(value)) {
                                value = value.trim();
                            }
                        } else if (type === EnumDataBaseType.INT || type === EnumDataBaseType.NUMBER) {
                            if (utils.isNull(value)) {
                                value = 0;
                            } else if (utils.isString(value)) {
                                if (value.trim() === '') {
                                    value = 0;
                                }
                            }
                        } else if (type === EnumDataBaseType.BOOL) {
                            if (utils.isNull(value)) {
                                value = false;
                            } else if (utils.isString(value)) {
                                if (value.trim() === '') {
                                    value = false;
                                }
                            }
                        }
                        if (!XTypeUtils.checkType(type, value)) {
                            r.setError(-54, `第${row}行:${key}=${value}不是指定的类型！`);
                            break;
                        }
                        newValue = value;
                    }
                    newData[column.name] = newValue;
                }
                if (r.isNotOK) {
                    break;
                }
                outData.push(newData);
            }
            if (r.isNotOK) {
                break;
            }
            this.outdata = outData;
        } while (false);
        return r;
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
            log.info(`初始化:${info.sheetName}:${info.describe}`);
            const s = new XTableInfo(info.type, info.sheetName, info.filename, info.describe);

            const sheet = paramExcelData[info.sheetName];
            if (utils.isNull(sheet)) {
                r.setError(-12, `没有找到表名为:${info.sheetName}的表， 请检查一下配置!`);
                break;
            }

            const initResult = s.init(sheet);
            if (initResult.isNotOK) {
                r.assignFrom(initResult);
                r.addErrorPre(`初始化:${info.sheetName}:${info.describe}`);
            } else {
                // log.info('----->\n' + JSON.stringify(s, null, 2));
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
        // 初始化
        const initResult = initTable(excelData[tablelist], excelData);
        if (initResult.isNotOK) {
            r.assignFrom(initResult);
            break;
        }
        // // 输出
        // for (const t of tableInfo) {
        //     //
        // }
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
