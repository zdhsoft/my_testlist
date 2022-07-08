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

import { t1, t2 } from './c1';
import { initMaster } from './master';
import path from 'path';
import fs from 'fs';

initMaster();

const a1 = new t1();
const a2 = new t1();
const a3 = new t2();
const a4 = new t2();
a4.name = '9999999999999999999999999999999999999';
console.log(a2.m, a1.m, a3, a4);

function fc(paramPath: string, paramRegExp: RegExp) {
    const list = fs.readdirSync(paramPath);

    const list2 = fs.readdirSync(paramPath, { withFileTypes: true });
    console.log('aaaaa' + JSON.stringify(list, null, 2));
    const listFiles: string[] = [];
    list2.forEach((d) => {
        if (d.isFile()) {
            listFiles.push(d.name);
        }
    });
    const list3 = listFiles.filter((f) => {
        return f.match(paramRegExp);
    });
    console.log('aaa:' + JSON.stringify(list3, null, 2));
    list3.forEach((f) => {
        require(path.join(paramPath, f));
    });
}

const fullPath = path.resolve(__dirname);
// fc(fullPath, /\.master\.js$/);
fc(fullPath, /\.js$/);

// const s = ['D:\\work\\lr\\xn-cps-server\\dist\\common\\master\\cos.master.js'];
// s.filter((f) => {
//     console.log('aaaa' + f.match(/\.master\.js$/));
// });
