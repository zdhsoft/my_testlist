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
 * 1.0                 zdhsoft      创建文件            2023-01-29
 *************************************************************************/
import PizZip from 'pizzip';
import Docxtemplater from 'docxtemplater';
import fs from 'fs';
import path from 'path';
import { XExcelUtils } from './excel_utils';
const filename = 'th.xlsx';

interface IReplaceKey {
    key: string;
    template: string;
    outname: string;
    newvalue: string;
}

interface ISheetObject {
    data: any;
    list: IReplaceKey[];
    template: string;
    outname: string;
}

function doReplaceWord(paramRep: ISheetObject) {
    console.log(`  开始替换: ${paramRep.template} => ${paramRep.outname}`);
    if (!fs.existsSync(paramRep.template)) {
        console.error('  模板文件不存在:' + paramRep.template);
        return;
    }
    const dirname = path.dirname(paramRep.outname);
    if (!fs.existsSync(dirname)) {
        console.error('  输出目录不存在, 请确定该目录已经存在：' + dirname);
        return;
    }

    const content = fs.readFileSync(paramRep.template, 'binary');
    const zip = new PizZip(content);
    const doc = new Docxtemplater(zip, {
        paragraphLoop: true,
        linebreaks: true,
    });
    const m = paramRep.data;
    doc.render(m);
    const buf = doc.getZip().generate({ type: 'nodebuffer', compression: 'DEFLATE' });
    console.log('  保存文件:' + paramRep.outname);
    fs.writeFileSync(paramRep.outname, buf);
}

function doReplaceSheet(paramSheetName: string, paramSheet: IReplaceKey[]) {
    console.log('sheet:' + paramSheetName);
    const m = new Map<string, ISheetObject>();
    for (const d of paramSheet) {
        const k = `${d.template}:${d.outname}`;
        let o = m.get(k);
        if (!o) {
            o = { data: {}, list: [], template: d.template, outname: d.outname };
            m.set(k, o);
        }
        o.data[d.key] = d.newvalue;
        o.list.push(d);
    }
    for (const [r, v] of m) {
        // console.log('    ' + JSON.stringify(r) + '\n' + JSON.stringify(v, null, 2));
        doReplaceWord(v);
    }
}

function main() {
    console.log('word关键字替换工具 1.0');
    const r = XExcelUtils.readExcelByFile(path.join('.', filename));
    if (r.isNotOK) {
        console.log(r.getErrorInfo());
        return;
    }

    const sheets = r.data as object;

    // console.log(JSON.stringify(r.data, null, 2));
    // console.log('-----------------------------------------------------');
    for (const s in sheets) {
        doReplaceSheet(s, sheets[s]);
    }

    console.log('完成所有替换,请检查是否符合要求!');
    //
    // const content = fs.readFileSync('./template/a.docx', 'binary');
    // const zip = new PizZip(content);
    // const doc = new Docxtemplater(zip, {
    //     paragraphLoop: true,
    //     linebreaks: true,
    // });
    // const m = { aaa: 'xxxxxxxxxxxxxxxxxx', bbb: 'yyyyyyyyyyyyy' };
    // doc.render(m);
    // const buf = doc.getZip().generate({ type: 'nodebuffer', compression: 'DEFLATE' });
    // fs.writeFileSync('./o.docx', buf);
    // console.log('finish-----------');
}

main();
