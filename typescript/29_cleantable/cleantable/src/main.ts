import { DBTools } from './dbtools';
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

async function main() {
    // eslint-disable-next-line @typescript-eslint/no-var-requires
    const cleanTable = require('../cleanTable.json');

    log.log(JSON.stringify(cleanTable));
    log.log('hello world!');

    const list = cleanTable?.cleanTable as string[];
    if (Array.isArray(list) && list.length > 0) {
        const cnt = list.length;
        for (let i = 0; i < cnt; i++) {
            await DBTools.cleanTable(list[i], i + 1, cnt);
        }
    }
    log.info(`处理完成!`);
    process.exit(0);
}
main();

// delete from avenger_approvalloan;
// ALTER TABLE avenger_approvalloan ADD COLUMN `___k` TINYINT ( 4 ) NOT NULL DEFAULT 0;
// ALTER TABLE avenger_approvalloan DROP COLUMN `___k`;
