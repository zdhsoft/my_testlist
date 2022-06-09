import { utils, getLogger, datetimeUtils } from 'xmcommon';
import * as redis from 'redis';
import { IRedisOptions, IRedisStoreOptions, XRedisStore } from './xredis_store';

const log = getLogger(__filename);

async function initStore() {
    const opts: IRedisOptions = {
        host: '127.0.0.1',
        port: 6379,
        ttl: 100,
        db: 5,
    };
    const redisClient = redis.createClient(opts);
    await redisClient.connect();

    const storeOpts: IRedisStoreOptions = {
        prefix: 'zdhsoft',
        client: redisClient as any,
    };

    const store = new XRedisStore(storeOpts);
    return store;
}

async function testStore() {
    const store = await initStore();
    for (let i = 0; i < 20; i++) {
        const s = await utils.WaitClassFunctionEx(store, 'set', `id${i}`, {
            name: 'test_' + i,
            d: datetimeUtils.getTimeString(new Date()),
        });
        const g = await utils.WaitClassFunctionEx(store, 'get', `id${i}`);
        log.info('s:' + JSON.stringify(s, null, 2));
        log.info('g:' + JSON.stringify(g, null, 2));
    }

    await utils.sleep(2000);
    const [, alldata] = await utils.WaitClassFunctionEx(store, 'all');
    log.info('alldata:' + JSON.stringify(alldata, null, 2));

    for (let i = 0; i < 20; i++) {
        await utils.sleep(10000);
        const [, data] = await utils.WaitClassFunctionEx(store, 'get', `id2`);
        // (data as any).d = datetimeUtils.getTimeString(new Date());
        const t = await utils.WaitClassFunctionEx(store, 'touch', 'id2', data);

        const [, data3] = await utils.WaitClassFunctionEx(store, 'get', `id3`);
        (data3 as any).d = datetimeUtils.getTimeString(new Date());
        const s = await utils.WaitClassFunctionEx(store, 'set', `id3`, data3);

        log.info('t:' + i + '>>' + JSON.stringify(t, null, 2));
        log.info('s:' + i + '>>' + JSON.stringify(s, null, 2));
    }
    log.info('test finish!');
    process.exit(0);
}
testStore();
