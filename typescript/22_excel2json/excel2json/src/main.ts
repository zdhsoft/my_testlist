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
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

enum EnumOutType {
    CLIENT = 'c',
    SERVER = 's',
};

class XTableInfo {

}

function main() {
    //
    log.info('begin:');
    const result = XExcelUtils.readExcelByFile(xlsxfile);
    fs.writeFileSync(t, JSON.stringify(result, null, 2), 'utf-8');
    log.info('finish!');
}

main();
