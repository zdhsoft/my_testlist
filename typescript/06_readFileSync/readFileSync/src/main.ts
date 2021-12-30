/*************************************************************************
 * Copyright(c) 2017-2021,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-28
 *************************************************************************/

console.log('hello world!');

import { CommonUtils } from './commonutils';

async function main() {
    const r = await CommonUtils.readFileSync('7package.json', 'utf8');
    if (r.isOK) {
        console.log(r.data);
    } else {
        console.log(r.msg);
    }
}

main();
