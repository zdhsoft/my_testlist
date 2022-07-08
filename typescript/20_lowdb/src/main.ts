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

import path from 'path';
import { LowSync, JSONFileSync } from 'lowdb';
import url from 'url';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);

type Data = { posts: string[] };

const file = path.join(__dirname, 'db.json');
const adapter = new JSONFileSync<Data>(file);
const db = new LowSync<Data>(adapter);
db.read();
db.data ||= { posts: [] };
db.data.posts.push('hello');
db.write();
log.log('hello world!');
