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
import fs from 'fs';

function main() {
    //
    const s = fs.readFileSync('./template.mst', { encoding: 'utf-8' });
    // console.log(s);
    const m = [
        {
            item: [{ a: 100 }, { b: 200 }, 'a', true],
        },
        {
            Index: 'hello world',
        },
    ];

    Handlebars.registerHelper('json', (context) => {
        const json = JSON.stringify(context) || '';
        const withoutQuotes = json.replace(/"([^(")"]+)":/g, '$1:');
        return withoutQuotes.slice(1, withoutQuotes.length - 1);
    });
    const template = Handlebars.compile(s);
    console.log(template(m));
}
main();
g.getName();
// fs.readFileSync()

// console.log('hello world!');
// const template = Handlebars.compile('Name: {{name}} >>>> age: {{age}}');
// console.log(template({ name: 'Nils', age: 18 }));
