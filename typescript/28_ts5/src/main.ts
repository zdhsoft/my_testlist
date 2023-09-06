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
 * 1.0                 zdhsoft      创建文件            2023-06-05
 *************************************************************************/

import { XCommRet } from '@zdhsoft/commret';
import { test_banner_list } from './test';

test_banner_list();

async function main() {
    await test_banner_list();

    process.exit(0);
}

main();

// function s(): XCommRet<number> {
//     const r = new XCommRet<number>();
//     do {
//         //
//         r.setOK(1999);
//     } while (false);
//     return r;
// }

// const r = s();
// console.log('hello world!' + JSON.stringify(r));
