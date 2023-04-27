/*************************************************************************
 * Copyright(c) 2017-2022, 深圳市链融科技股份有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename redis.service.ts
 * @summary: 这里提供redis存取服务
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                  祝冬华             创建文件            2022-06-09
 *************************************************************************/
import { Injectable } from '@nestjs/common';
import { RedisClientType } from '@redis/client';
import { createClient } from 'redis';
import { XConfigUtils } from '../init/config_utils';
@Injectable()
export class XRedisService {
    private m_RedisClient: RedisClientType;
    constructor() {
        const redisOpts = XConfigUtils.buildRedisOption(XConfigUtils.getConfig().redis);
        const redisClient = createClient(redisOpts);
        redisClient.connect();
        this.m_RedisClient = redisClient as any;
    }

    public async get(paramKey: string) {
        return this.m_RedisClient.get(paramKey);
    }

    public async set(paramKey: string, paramValue: string, paramTTL = -1) {
        if (paramTTL > 0) {
            return this.m_RedisClient.set(paramKey, paramValue, { EX: paramTTL });
        } else {
            return this.m_RedisClient.set(paramKey, paramValue);
        }
    }
}
