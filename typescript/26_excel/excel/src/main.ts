import nodexlsx from 'node-xlsx';
import fs from 'fs';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
async function main() {
    log.info('---->开始执行');
    const sheetOptions = {
        '!cols': [{ wch: 6 }, { wch: 30 }, { wch: 10 }, { wch: 15 }, { wch: 10 }, { wch: 10 }],
        '!merges': [
            { s: { c: 0, r: 0 }, e: { c: 2, r: 0 } },
            { s: { c: 3, r: 0 }, e: { c: 5, r: 0 } },
        ],
    };
    const s = {
        alignment: {
            horizontal: 'center', // 水平居中
            vertical: 'center', // 垂直居中
        },
    };
    const contentCellStyle = {
        border: {
            top: {
                style: 'medium',
                color: '#000',
            },
            bottom: {
                style: 'medium',
                color: '#000',
            },
            left: {
                style: 'medium',
                color: '#000',
            },
            right: {
                style: 'medium',
                color: '#000',
            },
        },
    };
    // 指定标题单元格样式：加粗居中
    const headerStyle = {
        font: {
            bold: true,
        },
        alignment: {
            horizontal: 'center',
        },
    };
    const title = ['序号', '名称', '年级', '任课老师', '学生数量', '已报名数量'];
    const title1 = [{ v: '天下无难事', s: headerStyle }, null, null, '右边', null];
    const value = [1, 'test', 9, { v: '张老师', s: contentCellStyle }, 10, 99];
    const rows: any[] = [];
    rows.push(title1);
    rows.push(title);
    rows.push(value);
    const data = nodexlsx.build([{ name: '社团列表', data: rows, options: sheetOptions }]);
    const outFileName = 'd:\\temp\\a.xlsx';
    fs.writeFileSync(outFileName, data);
    log.info('生成' + outFileName + ' ok!');
    process.exit(0);
}

main();
