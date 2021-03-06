import { SessionData, Store } from 'express-session';
import { RedisClientType } from 'redis';
import { ISessionSerializer } from './session_serializer';
import { utils } from 'xmcommon';

/**
 * Redis的socket配置
 */
export interface IRedisStoreSocketOptions {
    /** redis服务器端口 */
    port: number;
    /** redis服务器主机名或ip地址， 默认为localhost */
    host?: string;
    /** IP Stack version (one of 4 | 6 | 0)，默认为0 */
    family?: number;
    /** Path to the UNIX Socket */
    path?: string;
    /** 连接超时时间，单位毫秒，默认为5000 */
    connectTimeout?: number;
    /** 无延时 默认:true */
    noDelay?: boolean;
    /** 保活时间:单位毫秒，默认为5000 */
    keepAlive?: number | false;
    /**
     * 重连策略
     * - 你可以自定义重连策略
     *   - 接收重试次数
     *   - 返回number | Error
     *     - 重连间隔的毫少数
     *     - 关闭客户端并刷新内部命令队列
     */
    reconnectStrategy?(retries: number): number | Error;

    tls?: true | false;
    // 下面的配置，源于nodejs的CommonConnectionOptions,
    // import { CommonConnectionOptions } from 'tls';
    // 只有当tls为true的时候，才需要设置
    /**
     * Optionally override the trusted CA certificates. Default is to trust
     * the well-known CAs curated by Mozilla. Mozilla's CAs are completely
     * replaced when CAs are explicitly specified using this option.
     */
    ca?: string | Buffer | Array<string | Buffer>;
    /**
     *  Cert chains in PEM format. One cert chain should be provided per
     *  private key. Each cert chain should consist of the PEM formatted
     *  certificate for a provided private key, followed by the PEM
     *  formatted intermediate certificates (if any), in order, and not
     *  including the root CA (the root CA must be pre-known to the peer,
     *  see ca). When providing multiple cert chains, they do not have to
     *  be in the same order as their private keys in key. If the
     *  intermediate certificates are not provided, the peer will not be
     *  able to validate the certificate, and the handshake will fail.
     */
    cert?: string | Buffer | Array<string | Buffer>;
    /**
     * If true the server will reject any connection which is not
     * authorized with the list of supplied CAs. This option only has an
     * effect if requestCert is true.
     * @default true
     */
    rejectUnauthorized?: boolean;
}

// prettier-ignore
/** RedisSession的选项 */
export interface IRedisOptions {
    /** 连接URL redis[s]://[[username][:password]@][host][:port][/db-number] */
    url?         : string;
    /**
     * socket 属性
     */
    socket?: IRedisStoreSocketOptions;
    /** ACL username */
    username?: string;
    /** ACL password or the old "--requirepass" password */
    password?: string;
    /** 连接名称 */
    name?: string;
    /** 数据库编号 */
    database?: number;
}

// prettier-ignore
/**
 * 这个是Store用到的选项
 */
export interface IRedisStoreOptions {
    /** session id在 redis中的key前缀 默认为"session" */
    prefix?      : string;
    /** 每次扫描redis key的数量 默认100 */
    scanCount?   : number;
    /** 序列化对象，默认为JSON */
    serializer?  : ISessionSerializer;
    /** Redis Client 要确保已经连接 */
    client?      : RedisClientType;
    /** session有效时间，默认为86400 单位秒 */
    ttl?         : number;
    /** 禁止ttl的标志，默认false */
    disableTTL?  : boolean;
    /** 禁止touch标志，默认false */
    disableTouch?: boolean;
    /**
     * Enables automatic capturing of promise rejection.
     * - 启用自动捕获的Promise的rejection
     * - 默认为undefined
     */
    captureRejections?: boolean | undefined;
}
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const noop = (_err?: any, _value?: any) => {
    //
};

/** 将Promise转换成回调 */
function PromiseCallBack(paramResult: Promise<any>, paramCallBack = noop) {
    paramResult
        .then(
            (...args) => {
                paramCallBack(undefined, ...args);
            },
            (err) => {
                paramCallBack(err);
            },
        )
        .catch((err) => {
            paramCallBack(err);
        });
}
/** 基于redis的session存储类 */
export class XRedisStore extends Store {
    /** 存储key的前缀 */
    private m_Prefix?: string;
    /** 每次取key的个数 */
    private m_ScanCount?: number;
    /**
     *  序列化反序列化对象
     * - 默认使用JS自带的JSON对象
     */
    private m_Serializer?: ISessionSerializer;
    /**
     * redis连接客户端
     */
    private m_Client: RedisClientType;
    /**
     * session超时的时间
     */
    private m_TTL?: number;
    /**
     * 是否禁止TTL
     */
    private m_DisableTTL?: boolean;
    /** 是否禁止touch方法 */
    private m_DisableTouch?: boolean;

    /**
     * 生成session id对应key的方案
     * @param paramSessionId session id
     * @returns 返回生成的key
     */
    private key(paramSessionId: string) {
        return this.m_Prefix + paramSessionId;
    }
    /**
     * 构造函数
     * @param paramOpts store相关的选项
     */
    public constructor(paramOpts: IRedisStoreOptions) {
        super(paramOpts);
        if (!paramOpts.client) {
            throw new Error('选择参数没有提供redis client实例!');
        }
        // prettier-ignore
        {
            this.m_ScanCount    = Number(paramOpts.scanCount) || 100;
            this.m_Serializer   = paramOpts.serializer || JSON;
            this.m_Client       = paramOpts.client;
            this.m_TTL          = paramOpts.ttl || 86400 ;
            this.m_Prefix       = utils.stringOpts(paramOpts.prefix, 'session');
            this.m_DisableTTL   = paramOpts.disableTTL || false;
            this.m_DisableTouch = paramOpts.disableTouch || false;
        }
    }
    /**
     * 取session
     * @param paramSessionId 指定的sessionId
     * @param paramCallBack 取到数据后的回调
     */
    get(paramSessionId: string, paramCallBack = noop): void {
        const r = this.m_Client.get(this.key(paramSessionId));
        r.then(
            (value) => {
                const s = utils.JsonParse(value as unknown as string);
                paramCallBack(undefined, s);
            },
            (err) => {
                paramCallBack(err, undefined);
            },
        );
    }
    /**
     * 取当前session的TTL时间
     * - 单位秒
     * - 如果paramSession中有存在cookie，并指定了过期时间 ，则用它计算session的TTL
     * - 否则用配置中的ttl时间
     * @param paramSession
     * @returns
     */
    private _getTTL(paramSession: any) {
        let ttl: number;
        if (paramSession && paramSession.cookie && paramSession.cookie.expires) {
            // 如果存在cookie并有超时时间
            const ms = Number(new Date(paramSession.cookie.expires)) - Date.now();
            ttl = Math.ceil(ms / 1000);
        } else {
            ttl = this.m_TTL || -1;
        }
        return ttl;
    }
    /**
     * 设置session的内容
     * @param paramSessionId 对应的session id
     * @param paramSession session数据
     * @param paramCallBack 设成完成后的回调
     */
    public set(paramSessionId: string, paramSession: SessionData, paramCallBack = noop): void {
        const value = this.m_Serializer!.stringify(paramSession);

        let ttl = 1;
        if (!this.m_DisableTTL) {
            ttl = this._getTTL(paramSession);
        }

        if (ttl > 0) {
            const r = this.m_Client.set(this.key(paramSessionId), value, { EX: ttl });
            PromiseCallBack(r, paramCallBack);
        } else {
            this.destroy(paramSessionId, paramCallBack);
        }
    }
    /**
     * 触控session
     * 这里传入的session数据主要是取cookie带入的超时数据，然后用它更新TTL，否则用配置的ttl
     * @param paramSessionId 对应的session id
     * @param paramSession session数据
     * @param paramCallBack 设成完成后的回调
     * @returns
     */
    public touch(paramSessionId: string, paramSession: SessionData, paramCallBack = noop): void {
        if (this.m_DisableTouch || this.m_DisableTTL) return paramCallBack();
        const r = this.m_Client.expire(this.key(paramSessionId), this._getTTL(paramSession));
        r.then(
            (ret) => {
                if (utils.isNotNull(paramCallBack)) {
                    if (ret) {
                        paramCallBack(undefined, 'OK');
                    } else {
                        paramCallBack(undefined, 'EXPIRED');
                    }
                }
            },
            (err) => {
                if (utils.isNotNull(paramCallBack)) {
                    paramCallBack(err);
                }
            },
        ).catch((reason: any) => {
            paramCallBack(reason);
        });
    }
    /**
     * 删除指定的session
     * @param paramSessionId 对应的session id
     * @param paramCallBack 设成完成后的回调
     */
    public destroy(paramSessionId: string, paramCallBack: (err?: any) => void): void {
        const r = this.m_Client.del(this.key(paramSessionId));
        PromiseCallBack(r, paramCallBack);
    }

    /**
     * 清除所有的session
     * @param paramCallBack 完成后的回调
     */
    public clear(paramCallBack = noop): void {
        const r = this._getAllKeys();
        const callback = (err?: any, keys?: string[]) => {
            if (utils.isNotNull(err)) {
                paramCallBack(err);
            } else {
                if (Array.isArray(keys) && keys!.length > 0) {
                    const delR = this.m_Client.del(keys as string[]);
                    PromiseCallBack(delR, paramCallBack);
                } else {
                    paramCallBack(undefined, 0);
                }
            }
        };
        PromiseCallBack(r, callback);
    }
    /**
     * 计算当前session的数量
     * @param paramCallBack 完成后的回调
     */
    public length(paramCallBack = noop): void {
        const r = this._getAllKeys();
        const callback = (err?: any, keys?: string[]) => {
            if (utils.isNotNull(err)) {
                paramCallBack(err);
            } else {
                if (Array.isArray(keys) && keys!.length > 0) {
                    paramCallBack(undefined, keys!.length);
                } else {
                    paramCallBack(undefined, 0);
                }
            }
        };
        PromiseCallBack(r, callback);
    }
    /**
     * 取所有session的id
     * @param paramCallBack 完成后的回调, 回调中返回所有的id
     */
    public ids(paramCallBack = noop) {
        const prefixLen = this.m_Prefix!.length;
        const r = this._getAllKeys();
        const callback = (err?: any, keys?: string[]) => {
            if (utils.isNotNull(err)) {
                paramCallBack(err);
            } else {
                if (Array.isArray(keys) && keys!.length > 0) {
                    const retKeys: string[] = [];
                    for (const k of keys) {
                        retKeys.push(k.substring(prefixLen));
                    }
                    paramCallBack(undefined, retKeys);
                } else {
                    paramCallBack(undefined, []);
                }
            }
        };
        PromiseCallBack(r, callback);
    }
    /**
     * 取所有session数据，包括id
     * @param paramCallBack 完成后的回调, 回调中返回所有的session数据和id
     */
    public all(paramCallBack = noop) {
        const prefixLen = this.m_Prefix!.length;
        const r = this._getAllKeys();
        let sessionKeys: string[] = [];

        const mgetCallback = (err?: any, sessions?: string[]) => {
            if (utils.isNotNull(err)) {
                paramCallBack(err);
            } else if (Array.isArray(sessions) && sessions.length > 0) {
                const sd: any[] = [];
                const serializer = this.m_Serializer;
                for (let i = 0; i < sessions.length; i++) {
                    const d = sessions[i];
                    if (utils.isNull(d)) {
                        continue;
                    }
                    const data: any = serializer?.parse(d);
                    if (utils.isNull(data)) {
                        continue;
                    }
                    data.id = sessionKeys[i].substring(prefixLen);
                    sd.push(data);
                }
                paramCallBack(undefined, sd);
            } else {
                paramCallBack(undefined, []);
            }
        };

        const allkeyCallback = (err?: any, keys?: string[]) => {
            if (utils.isNotNull(err)) {
                paramCallBack(err);
            } else if (Array.isArray(keys) && keys.length > 0) {
                //
                sessionKeys = [...keys];
                const mgetr = this.m_Client.mGet(sessionKeys);
                PromiseCallBack(mgetr, mgetCallback);
            } else {
                sessionKeys = [];
                paramCallBack(undefined, []);
            }
        };
        PromiseCallBack(r, allkeyCallback);
    }
    /**
     * 取Session中，所有的id
     * @returns 返回的所有的id
     */
    private async _getAllKeys() {
        return this._scanKeys(this.key('*'), 0, this.m_ScanCount);
    }
    /**
     * 扫描session id
     * - redis的光标说明，第一次开始的时候，传入后。调用scan后，每次都会返回新的光标, 在下次调用它的时候要传入。当返回的光标为0的时候，表示全部扫描完成。
     * @param pattern id匹配模式
     * @param cursor 当前光标
     * @param count 每次扫描的数量
     * @returns
     */
    private async _scanKeys(pattern: string, cursor = 0, count = 100) {
        const keys: any = {};
        let currCursor = cursor;
        do {
            const r = await this.m_Client.scan(currCursor, { MATCH: pattern, COUNT: count });
            currCursor = r.cursor;
            for (const k of r.keys) {
                keys[k] = true;
            }
        } while (currCursor !== 0);
        return Object.keys(keys);
    }
}
