import nodexlsx from 'node-xlsx';
import fs from 'fs';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);

export async function invoice() {
    const sheetOptions = {
        '!cols': [
            { wch: 6 },
            { wch: 30 },
            { wch: 10 },
            { wch: 20 },
            { wch: 20 },
            { wch: 10 },
            { wch: 10 },
            { wch: 20 },
            { wch: 20 },
            { wch: 10 },
            { wch: 10 },
            { wch: 20 },
            { wch: 20 },
            { wch: 10 },
            { wch: 10 },
            { wch: 20 },
            { wch: 20 },
            { wch: 10 },
        ],
        '!merges': [
            { s: { c: 0, r: 0 }, e: { c: 0, r: 1 } },
            { s: { c: 1, r: 0 }, e: { c: 1, r: 1 } },
            { s: { c: 2, r: 0 }, e: { c: 5, r: 0 } },
            { s: { c: 6, r: 0 }, e: { c: 9, r: 0 } },
            { s: { c: 10, r: 0 }, e: { c: 13, r: 0 } },
            { s: { c: 14, r: 0 }, e: { c: 17, r: 0 } },
        ],
    };
    const title = [
        '序号',
        '销售方',
        '电子发票专票',
        null,
        null,
        null,
        '专用纸质发票',
        null,
        null,
        null,
        '普通电子发票',
        null,
        null,
        null,
        '普通纸质发票',
        null,
        null,
        null,
    ];
    const title1 = [
        null,
        null,
        '数量',
        '不含税金额',
        '税额',
        '数量',
        '数量',
        '不含税金额',
        '税额',
        '数量',
        '数量',
        '不含税金额',
        '税额',
        '数量',
        '数量',
        '不含税金额',
        '税额',
        '数量',
    ];
    const value = [
        1,
        '测试的销售方',
        10,
        '111,11.000',
        '222,222.00',
        10,
        10,
        '111,11.000',
        '222,222.00',
        10,
        10,
        '111,11.000',
        '222,222.00',
        10,
        10,
        '111,11.000',
        '222,222.00',
        10,
    ];
    const rows: any[] = [];
    rows.push(title);
    rows.push(title1);
    rows.push(value);
    const data = nodexlsx.build([{ name: 'xxxxxx', data: rows, options: sheetOptions }]);
    const outFileName = 'd:\\temp\\b.xlsx';
    fs.writeFileSync(outFileName, data);
    log.info('生成' + outFileName + ' ok!');
}

// 号	销售方	电子发票专票	专用纸质发票	普通电子发票	普通纸质发票
// 数量	不含税金额	税额	数量	不含税金额	税额	数量	不含税金额	税额	数量	不含税金额	税额
