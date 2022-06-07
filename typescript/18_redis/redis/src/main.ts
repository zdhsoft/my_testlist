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

import * as redis from 'redis';
// export interface RedisClientOptions<M extends RedisModules = RedisModules, F extends RedisFunctions = RedisFunctions, S extends RedisScripts = RedisScripts> extends RedisExtensions<M, F, S> {
//     url?: string;
//     socket?: RedisSocketOptions;
//     username?: string;
//     password?: string;
//     name?: string;
//     database?: number;
//     commandsQueueMaxLength?: number;
//     disableOfflineQueue?: boolean;
//     readonly?: boolean;
//     legacyMode?: boolean;
//     isolationPoolOptions?: PoolOptions;
// }
async function initRedis() {
    //
    // import { createClient } from 'redis';
    const opts = {
        host: '127.0.0.1',
        port: 6379,
        database: 1,
    };
    const client = redis.createClient(opts);
    await client.connect();
    return client;
}

async function main() {
    const client = await initRedis();
    const s = client.set('aaaaa', 1999, { EX: 2600 });
    const r = await client.get('aaaaa');
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
}

main();
