import { DBTools } from './dbtools';
import { getLogger } from 'xmcommon';
import { cleanTable } from './cleanTable';
import { XMCurrency } from 'xmcurrency';
import crypto from 'crypto';
const log = getLogger(__filename);
// const hmac = crypto.createHmac("sha256", this.key);
// return hmac.update(contentToBeSigned).digest('base64');
function test() {
    const token = 'xxxxyyyy';
    const t = 1669872112;
    const hash = crypto.createHmac('sha256', token);
    const h = crypto.createHash('sha256');
    const mm = hash.update(t.toString()).digest('hex');
    const m = h.update(`${token}${t}`).digest('hex');
    log.info(mm);
    log.info(m);
}

test();

// function test() {
//     const sumAmountIncludingTax = '130000.00';
//     const sumExcludingTaxAmount = '122641.51';

//     const c1 = new XMCurrency(sumAmountIncludingTax);
//     const c3 = c1.sub(sumExcludingTaxAmount);
//     console.log(c1.format(), c3.format());
// }

// test();

// spec_elec
// :
// {count: "1", sumAmountIncludingTax: "130000.00", sumExcludingTaxAmount: "122641.51"}
// count
// :
// "1"
// sumAmountIncludingTax
// :
// "130000.00"
// sumExcludingTaxAmount
// :
// "122641.51"

// async function main() {
//     // eslint-disable-next-line @typescript-eslint/no-var-requires
//     // const cleanTable = require('../cleanTable.json');

//     log.log(JSON.stringify(cleanTable));
//     log.log('hello world!');

//     const list = cleanTable;
//     if (Array.isArray(list) && list.length > 0) {
//         const cnt = list.length;
//         for (let i = 0; i < cnt; i++) {
//             await DBTools.cleanTable(list[i], i + 1, cnt);
//         }
//     }
//     log.info(`处理完成!`);
//     process.exit(0);
// }
// main();

// delete from avenger_approvalloan;
// ALTER TABLE avenger_approvalloan ADD COLUMN `___k` TINYINT ( 4 ) NOT NULL DEFAULT 0;
// ALTER TABLE avenger_approvalloan DROP COLUMN `___k`;
