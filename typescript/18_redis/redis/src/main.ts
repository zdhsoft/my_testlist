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

import { RedisClientType } from '@redis/client';
import * as redis from 'redis';

let c: any;
async function getRedis() {
    const opts = {
        host: '127.0.0.1',
        port: 6379,
        database: 1,
    };
    let client = redis.createClient(opts);
    if (!(c === undefined || c === null)) {
        client = c;
    } else {
        c = client;
        await client.connect();
    }
    return client;
}

const k1 = 'aaaaaa';
const k2 = 'bbbbbb';
async function expire() {
    const client = await getRedis();
    const s = await client.expire(k1, 100);
    const k = await client.expire(k2, 100);
    console.log(`${k1}: expire ${s}`);
    console.log(`${k2}: expire ${k}`);
}

async function testRedure() {
    const s = ['1', '2', '3', '4', '5'];
    const k = s.reduce((p: string[], curr: string, index: number) => {
        const kk = `[${index}] = ${curr}` as never;
        p.push(kk);
        return p;
    }, []);
    console.info('----->' + JSON.stringify(k));
}

async function main() {
    const client = await getRedis();
    const s = client.set(k1, 1999, { EX: 2600 });
    const r = await client.get(k1);
    await client.set(k2, JSON.stringify({ name: 'hello' }), { EX: 99 });
    s.then(
        (...a) => {
            console.log('SUCCESS:' + JSON.stringify(a));
        },
        (...b) => {
            'FAIL:' + JSON.stringify(b);
        },
    );
    // console.log('set result:' + s);
    console.log('get result:' + JSON.stringify(r, null, 2));

    await expire();
}
testRedure();
// main();
