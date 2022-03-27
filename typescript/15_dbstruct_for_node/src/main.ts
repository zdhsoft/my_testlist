import { DBTool } from './db';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

// INSERT INTO `` (`TABLE_NAME`, `ENGINE`, `VERSION`, `ROW_FORMAT`, `TABLE_ROWS`, `AVG_ROW_LENGTH`, `DATA_LENGTH`, `MAX_DATA_LENGTH`, `INDEX_LENGTH`, `DATA_FREE`, `AUTO_INCREMENT`, `CREATE_TIME`, `UPDATE_TIME`, `CHECK_TIME`, `TABLE_COLLATION`, `CHECKSUM`, `CREATE_OPTIONS`, `TABLE_COMMENT`) VALUES ('wkinfoword', 'InnoDB', 10, 'Dynamic', 0, 0, 16384, 0, 0, 0, NULL, '2022-03-21 10:51:30', NULL, NULL, 'utf8_general_ci', NULL, '', '');

async function main() {
    do {
        const t = await DBTool.getTables();
        log.info('t' + JSON.stringify(t, null, 2));
    } while (false);
}
main();
