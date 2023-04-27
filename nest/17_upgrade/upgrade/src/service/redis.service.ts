/*************************************************************************
 * Copyright(c) 2017-2022, 深圳市链融科技股份有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename redis.service.ts
 * @summary: 这里提供redis存取服务，这里只提供了get和set两个方法，其它功能，需要自行扩展
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                  祝冬华             创建文件            2022-06-09
 *************************************************************************/
import { Injectable } from '@nestjs/common';
import type Redis from 'ioredis';
import { XConfigUtils } from '../init/config_utils';
import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Injectable()
export class XRedisService {
    private m_RedisClient: Redis;
    constructor() {
        // eslint-disable-next-line @typescript-eslint/no-var-requires
        const redisClass = require('ioredis');
        const opts = XConfigUtils.buildRedisOption(XConfigUtils.getConfig().redis);
        let redis: Redis;

        if (opts.url) {
            redis = new redisClass(opts.url);
        } else if (opts.opts) {
            redis = new redisClass(opts.opts);
        } else {
            redis = new redisClass();
        }
        redis.on('error', (paramError: any) => {
            if (paramError) {
                if (paramError.code !== 'ECONNRESET') {
                    log.error('getRedis >>>----------', JSON.stringify(paramError));
                } else {
                    log.error('getRedis aaa >>>----------', JSON.stringify(paramError));
                    // 因为这个日志，打出来非常多，所以就不用打印了
                    // 大概是每隔65秒，会打印一次这个log，连接会ECONNRESET一次
                    // log.error('----------ECONNRESET', JSON.stringify(error));
                }
            }
        });

        this.m_RedisClient = redis;
    }

    public async get(paramKey: string) {
        return this.m_RedisClient.get(paramKey);
    }

    public async set(paramKey: string, paramValue: string, paramTTL = -1) {
        if (paramTTL > 0) {
            return this.m_RedisClient.set(paramKey, paramValue, 'EX', paramTTL);
        } else {
            return this.m_RedisClient.set(paramKey, paramValue);
        }
    }
}
