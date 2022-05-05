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
 * 1.0                 zdhsoft       创建文件            2022-03-28
 *************************************************************************/

import * as xlsx from 'node-xlsx-ex';
// eslint-disable-next-line @typescript-eslint/no-var-requires
// const xlsx = require('node-xlsx-ex');
import fs from 'fs';
// Or var xlsx = require('node-xlsx-ex').default;

const dataSheet1: any[] = [
    [
        1,
        2,
        {
            v: 3,
            s: {
                alignment: {
                    horizontal: 'center', // 水平居中
                    vertical: 'center', // 垂直居中
                },
            },
        },
    ],
    [true, false, null, 'sheetjs'],
    ['foo', 'bar', new Date('2014-02-19T14:30Z'), '0.3'],
    ['baz', null, 'qux'],
];
const dataSheet2 = [
    [4, 5, 6],
    [7, 8, 9, 10],
    [11, 12, 13, 14],
    ['baz', null, 'qux'],
];
const range = { s: { c: 0, r: 0 }, e: { c: 0, r: 3 } }; // A1:A4
const sheetOptions = { '!merges': [range] };

const buffer = xlsx.build([
    { name: 'myFirstSheet', data: dataSheet1, options: {} },
    { name: 'mySecondSheet', data: dataSheet2, options: sheetOptions },
]); // Returns a buffer

fs.writeFileSync('./t.xlsx', buffer);
