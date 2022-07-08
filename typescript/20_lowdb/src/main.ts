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
import { JsonDB } from 'node-json-db';
import { Config } from 'node-json-db/dist/lib/JsonDBConfig';
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

const db = new JsonDB(new Config('./myDataBase', true, true, '/'));
db.load();
if (!db.exists('/test')) {
    db.push('/test', 'cccccc');
}
if (!db.exists('/test1')) {
    db.push('/test1', { fffa: 'aaa11111' });
}

for (let i = 0; i < 10; i++) {
    db.push('/testx/array[]', { id: i + 100, v: 'this is value' + i, d: new Date() }, true);
}
const v = db.getIndex('/testx/array', 101);

log.info('index:' + v);
db.push('/now', new Date());
db.save();

log.log('hello world!');
