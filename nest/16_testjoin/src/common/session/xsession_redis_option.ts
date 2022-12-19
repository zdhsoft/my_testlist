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
