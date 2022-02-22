/*
    这个文件主要负责根据当前的系统配置的环境，加载对应的配置文件。
    - 这里配置的文件都是yaml格式的，要放到工作目录的config目录下面，文件名的要求格式为：env.{环境名}.yaml
    - 如：test环境的配置文件是  env.test.yaml， dev环境的配置文件是: env.dev.yaml
    - 除此之外，还有一个默认的配置文件，如果是各环境都是同样的配置，则可以放到这个配置文件中。这个默认的配置文件名是env.default.yaml。
    - 对应的环境中的配置，会替换默认的配置。
    - 配置加载完成后，会在config目录生成一个finalConfig.{环境名}.json和finalConfig.{环境名}.yaml，这个当前环境运行的最新配置
 */

import * as yaml from 'js-yaml';
import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

import {
    ILRConfig,
    ILRConfigMySQL,
    ILRSessionMySQLStoreClumnNames,
    ILRSessionMySQLStoreOptions,
    ILRSessionMySQLStoreSchema,
    ILRSessionRedisStoreOptions,
} from './config_def';
import { getLogger, XCommonRet, utils } from 'xmcommon';
import { EnumErrorCode } from '../error/error_code';
import { EnumRuntimeEnv } from '../env_utils';

const log = getLogger(__filename);

/** 当前进程所在的工作目录 */
const currProcessPath = process.cwd();

/** 配置文件所在的目录 */
const configPath = 'config';
const finalPath = 'final';

/** 最终配置输出文件名 */
const finalConfigFileName = 'finalConfig';

/** 配置文件的扩展名 */
const configFileExt = '.yaml';

const cfg: ILRConfig = {};

let runtimePath = path.join(process.cwd(), 'runtime');

/** 配置相关的工具类 */
export class ConfigUtils {
    /**
     * 取当前的配置
     * - 为了防止，取到的配置被人为修改，取的配置是被clone的配置!
     */
    public static getConfig(): ILRConfig {
        return _.cloneDeep(cfg);
    }
    /**
     * 取指定称的配置
     * - 为了防止，取到的配置被人为修改，取的配置是被clone的配置!
     * @param paramName 配置的名称
     * @return 返回的配置对象
     *  - undefined 配置不存在时，返回undefined
     *  - object 配置存在的时候，返回相应的对象
     */
    public static getConfigByName<T = any>(paramName: string): T {
        const retCfg = cfg[paramName];
        if (utils.isNotNull(retCfg)) {
            return _.cloneDeep(retCfg) as T;
        } else {
            return undefined;
        }
    }

    public static stringOpts(paramValue: unknown, paramDefault: string): string {
        return _.isString(paramValue) ? (paramValue as string) : paramDefault;
    }

    public static intOpts(paramValue: unknown, paramDefault: number): number {
        return Number.isInteger(paramValue) ? (paramValue as number) : paramDefault;
    }

    public static numberOpts(paramValue: unknown, paramDefault: number): number {
        return _.isNumber(paramValue) ? (paramValue as number) : paramDefault;
    }

    public static boolOpts(paramValue: unknown, paramDefault: boolean): boolean {
        return _.isBoolean(paramValue) ? (paramValue as boolean) : paramDefault;
    }

    public static objectOpts(paramValue: unknown, paramDefault: unknown): unknown {
        return _.isObject(paramValue) ? paramValue : paramDefault;
    }

    /**
     * 取指定环境的配置文件名
     * @param paramEnv
     */
    private static getConfigNameByEnv(paramEnv: string): string {
        return path.join(currProcessPath, configPath, `env.${paramEnv}${configFileExt}`);
    }

    private static initMySQLStoreOptions(paramOptions: ILRSessionMySQLStoreOptions) {
        const ret: ILRSessionMySQLStoreOptions = {};

        ret.port = this.intOpts(paramOptions?.port, 3306);
        ret.host = this.stringOpts(paramOptions?.host, 'localhost');
        ret.database = this.stringOpts(paramOptions?.database, 'db_session');
        ret.user = this.stringOpts(paramOptions?.user, 'root');
        ret.password = this.stringOpts(paramOptions?.password, '');
        ret.createDatabaseTable = this.boolOpts(paramOptions?.createDatabaseTable, true);
        ret.connectionLimit = this.intOpts(paramOptions?.connectionLimit, 1);
        ret.chatset = this.stringOpts(paramOptions?.chatset, 'utf8mb4');
        const schema = this.objectOpts(paramOptions?.schema, {}) as ILRSessionMySQLStoreSchema;
        ret.schema = schema;
        schema.tableName = this.stringOpts(paramOptions?.schema?.tableName, 'sessions');
        schema.columnNames = this.objectOpts(paramOptions?.schema?.columnNames, {}) as ILRSessionMySQLStoreClumnNames;
        schema.columnNames.session_id = this.stringOpts(paramOptions?.schema?.columnNames?.session_id, 'session_id');
        schema.columnNames.expires = this.stringOpts(paramOptions?.schema?.columnNames?.expires, 'expires');
        schema.columnNames.data = this.stringOpts(paramOptions?.schema?.columnNames?.data, 'data');

        log.info('session mysql config:\n' + JSON.stringify(ret, null, 2));
        return ret;
    }

    /** 生成连接redis的选项 */
    private static initRedisOptions(paramOptions: ILRSessionRedisStoreOptions) {
        const port = Number.isSafeInteger(paramOptions?.port) ? paramOptions.port : 6379;
        const host = _.isString(paramOptions?.host) ? paramOptions.host : 'localhost';
        const mode = paramOptions?.mode === 'rediss' ? 'rediss' : 'redis';
        const url = `${mode}://${host}:${port}`;
        const database = Number.isSafeInteger(paramOptions?.database) ? paramOptions.database : 0;

        const redisOpts: Record<string, any> = {
            url,
            database,
            legacyMode: true,
            name: 'lrsession',
        };
        const connectRedisOpts: Record<string, any> = {};

        if (_.isString(paramOptions?.password)) {
            redisOpts.password = paramOptions.password;
        }

        if (_.isString(paramOptions?.username)) {
            redisOpts.username = paramOptions.username;
        }

        if (_.isString(paramOptions?.name)) {
            redisOpts.name = paramOptions.name;
        }

        connectRedisOpts.ttl = Number.isSafeInteger(paramOptions?.ttl) ? paramOptions.ttl : 1800;
        connectRedisOpts.prefix = _.isString(paramOptions?.prefix) ? paramOptions.prefix : 'lr_';
        log.info('redis config:\n' + JSON.stringify(redisOpts, null, 2));
        log.info('connect redis config:\n' + JSON.stringify(connectRedisOpts, null, 2));
        return { redisOpts, connectRedisOpts };
    }
    /**
     * 生成mysql的配置，如果不存在，则返回undefined
     * @returns
     */
    public static buildMySQLOption(): ILRConfigMySQL {
        const mysqlOpts = cfg?.mysql;
        if (utils.isNull(mysqlOpts)) {
            return undefined;
        }
        const retOpts: ILRConfigMySQL = { type: 'mysql' };
        retOpts.host = _.isString(mysqlOpts?.host) ? mysqlOpts.host : 'localhost';
        retOpts.port = Number.isSafeInteger(mysqlOpts?.port) ? mysqlOpts.port : 3306;
        retOpts.username = _.isString(mysqlOpts?.username) ? mysqlOpts.username : 'root';
        retOpts.password = _.isString(mysqlOpts.password) ? mysqlOpts.password : '';
        retOpts.database = _.isString(mysqlOpts?.database) ? mysqlOpts.database : 'test';
        retOpts.entities = Array.isArray(mysqlOpts?.entities) ? mysqlOpts.entities : ['dist/db/*{.ts,.js}'];
        retOpts.synchronize = _.isBoolean(mysqlOpts?.synchronize) ? mysqlOpts.synchronize : false;
        retOpts.logging = _.isBoolean(mysqlOpts?.logging) ? mysqlOpts.logging : false;
        log.info('mysqlOptions:' + JSON.stringify(retOpts, null, 4));
        return retOpts;
    }

    /** 生成指定的session选项 */
    public static buildSessionOptions(): any {
        const sessionConfig = cfg?.session;
        const type = sessionConfig?.type;
        let store: any;
        switch (type) {
            case 'mysql':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const session = require('express-session');
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const MySQLStore = require('express-mysql-session')(session);
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const mysql = require('mysql2/promise');

                    const opts = this.initMySQLStoreOptions(sessionConfig.mysqlStoreOptions);
                    const mysqlOpts = {
                        port: opts.port,
                        host: opts.host,
                        user: opts.user,
                        database: opts.database,
                        password: opts.password,
                    };
                    const pool = mysql.createPool(mysqlOpts);
                    store = new MySQLStore(opts, pool);
                }
                break;
            case 'file':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const session = require('express-session');
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const FileStore = require('session-file-store')(session);

                    store = new FileStore(sessionConfig.fileStoreOptions);
                }
                break;
            case 'redis':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const session = require('express-session');

                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const redis = require('redis');
                    const opts = this.initRedisOptions(sessionConfig.redisOptions);
                    const redisClient = redis.createClient(opts.redisOpts);
                    redisClient.connect();

                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    const RedisStore = require('connect-redis')(session);
                    store = new RedisStore({ client: redisClient, ...opts.connectRedisOpts });
                }
                break;
            default:
                break;
        }
        let retOptions: any = {};
        if (sessionConfig?.options) {
            retOptions = _.cloneDeep(sessionConfig.options);
        }
        log.info('session options:' + JSON.stringify(retOptions));
        if (utils.isNotNull(store)) {
            retOptions.store = store;
        }

        return retOptions;
    }

    /** 加载指定环境的配置 */
    public static loadByEnv(paramEnv: string): XCommonRet<ILRConfig> {
        let ret = new XCommonRet<ILRConfig>();
        do {
            const localCfg: ILRConfig = {
                port: 3000,
            };

            const loadDefaultResult = this.loadConfigByEnv(EnumRuntimeEnv.default);
            if (loadDefaultResult.isNotOK) {
                ret = loadDefaultResult;
                break;
            }

            const loadEnvResult = this.loadConfigByEnv(paramEnv);
            if (loadEnvResult.isNotOK) {
                ret = loadEnvResult;
                break;
            }

            utils.dataAssign(localCfg, loadDefaultResult.data);
            utils.dataAssign(localCfg, loadEnvResult.data);

            utils.dataAssign(cfg, localCfg);

            const finalConfig = cfg;

            const destPath = path.join(currProcessPath, configPath, finalPath);
            // 如果不存在，则创建一个
            if (!utils.fileExists(destPath)) {
                const result = utils.mkdirsSyncEx(destPath);
                if (!result.ret) {
                    ret.setError(-1, result.msg);
                    break;
                }
            }

            const destPathJson = path.join(
                currProcessPath,
                configPath,
                finalPath,
                `${finalConfigFileName}.${paramEnv}.json`,
            );

            this.initRuntimePath();

            const destPathYaml = path.join(
                currProcessPath,
                configPath,
                finalPath,
                `${finalConfigFileName}.${paramEnv}.yaml`,
            );

            fs.writeFileSync(destPathJson, JSON.stringify(finalConfig, null, 4));
            fs.writeFileSync(destPathYaml, yaml.dump(finalConfig));
        } while (false);
        return ret;
    }
    /** 实始化runtime路径 */
    private static initRuntimePath() {
        const rtPath = cfg.path?.runtime;
        if (!utils.isString(rtPath)) {
            return;
        }
        if (path.isAbsolute(rtPath)) {
            // 如果是绝对路径，则直接使用
            runtimePath = rtPath;
        } else {
            runtimePath = path.join(process.cwd(), rtPath);
        }
    }
    /** 取当前runtime时间 */
    public static getRuntimePath() {
        return runtimePath;
    }

    // }
    private static loadConfigByEnv(paramEnv: string): XCommonRet<ILRConfig> {
        const fileName = this.getConfigNameByEnv(paramEnv);
        return this.loadConfigByFileName(fileName);
    }

    private static loadConfigByFileName(paramFileName: string): XCommonRet<ILRConfig> {
        const ret = new XCommonRet<ILRConfig>();
        do {
            if (!fs.existsSync(paramFileName)) {
                ret.setError(EnumErrorCode.FILE_NOT_EXISTS, `配置文件:${paramFileName}不存在!`);
                log.error(ret.err);
                break;
            }

            let doc: string;

            try {
                doc = fs.readFileSync(paramFileName, 'utf8');
            } catch (e) {
                ret.setError(EnumErrorCode.READ_FILE_FAIL, `读取配置文件失败:${paramFileName}, err:${String(e)}`);
                break;
            }

            try {
                const cfg = yaml.load(doc);
                ret.setOK(cfg);
            } catch (e) {
                ret.setError(EnumErrorCode.PARSE_FILE_FAIL, `解析配置文件失败:${paramFileName}, err:${String(e)}`);
                break;
            }
        } while (false);
        return ret;
    }
}
