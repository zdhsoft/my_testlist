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
 * 1.0                 祝冬华       创建文件            2022-01-04
 *************************************************************************/

import * as redis from 'redis';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

log.log('hello test redis!');

const redisURL = 'redis://localhost:6379';

// export interface RedisClientOptions<M extends RedisModules, S extends RedisScripts> extends RedisPlugins<M, S> {
//     url?: string;
//     socket?: RedisSocketOptions;
//     username?: string;
//     password?: string;
//     name?: string;
//     database?: number;
//     commandsQueueMaxLength?: number;
//     readonly?: boolean;
//     legacyMode?: boolean;
//     isolationPoolOptions?: PoolOptions;
// }
const redisClient = redis.createClient({
    url: redisURL,
    database: 1,
});
redisClient.on('error', (err) => {
    log.error(err);
});
redisClient.on('ready', function (res) {
    console.log('ready');
});

redisClient.on('end', function (err) {
    console.log('end');
});

redisClient.on('connect', function () {
    console.log('redis connect success!');
});

async function test() {
    await redisClient.connect();
    await redisClient.set('foo' + Date.now(), new Date().toLocaleTimeString());
    const fooValue = await redisClient.get('foo');
    log.info(fooValue);
}

test();
