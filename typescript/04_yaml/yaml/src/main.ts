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
 * 1.0                 祝冬华       创建文件            2021-12-21
 *************************************************************************/

import yaml from 'js-yaml';
import fs from 'fs';

// const fs   = require('fs');

console.log('hello world!');
const data = fs.readFileSync('ci.yaml', 'utf8');
const doc = yaml.load(data);
console.log('------------分隔线---------------');
console.log(JSON.stringify(doc, null, 2));
console.log('------------分隔线---------------');
console.log(yaml.dump(doc));

/**
 *
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 * @returns
 */
function fff(p1: number, p2: number, p3: string, p4: any): string {
    return [p1, p2, p3, p4].join();
}

console.log(fff(1, 2, '3', 4));
