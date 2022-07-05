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

initMaster();

const a1 = new t1();
const a2 = new t1();
const a3 = new t2();
const a4 = new t2();
a4.name = '9999999999999999999999999999999999999';
console.log(a2.m, a1.m, a3, a4);
