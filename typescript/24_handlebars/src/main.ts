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
 * 1.0                 zdhsoft      创建文件            2022-10-09
 *************************************************************************/
import Handlebars from 'handlebars';

console.log('hello world!');
const template = Handlebars.compile('Name: {{name}} >>>> age: {{age}}');
console.log(template({ name: 'Nils', age: 18 }));
