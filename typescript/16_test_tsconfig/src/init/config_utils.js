"use strict";
/*
    这个文件主要负责根据当前的系统配置的环境，加载对应的配置文件。
    - 这里配置的文件都是yaml格式的，要放到工作目录的config目录下面，文件名的要求格式为：env.{环境名}.yaml
    - 如：test环境的配置文件是  env.test.yaml， dev环境的配置文件是: env.dev.yaml
    - 除此之外，还有一个默认的配置文件，如果是各环境都是同样的配置，则可以放到这个配置文件中。这个默认的配置文件名是env.default.yaml。
    - 对应的环境中的配置，会替换默认的配置。
    - 配置加载完成后，会在config目录生成一个finalConfig.{环境名}.json和finalConfig.{环境名}.yaml，这个当前环境运行的最新配置
 */
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
exports.__esModule = true;
exports.ConfigUtils = void 0;
var yaml = require("js-yaml");
var fs = require("fs");
var path = require("path");
var _ = require("lodash");
var xmcommon_1 = require("xmcommon");
var error_code_1 = require("../error/error_code");
var env_utils_1 = require("../env_utils");
var log = (0, xmcommon_1.getLogger)(__filename);
/** 当前进程所在的工作目录 */
var currProcessPath = process.cwd();
/** 配置文件所在的目录 */
var configPath = 'config';
var finalPath = 'final';
/** 最终配置输出文件名 */
var finalConfigFileName = 'finalConfig';
/** 配置文件的扩展名 */
var configFileExt = '.yaml';
var cfg = {};
var runtimePath = path.join(process.cwd(), 'runtime');
/** 配置相关的工具类 */
var ConfigUtils = /** @class */ (function () {
    function ConfigUtils() {
    }
    /**
     * 取当前的配置
     * - 为了防止，取到的配置被人为修改，取的配置是被clone的配置!
     */
    ConfigUtils.getConfig = function () {
        return _.cloneDeep(cfg);
    };
    /**
     * 取指定称的配置
     * - 为了防止，取到的配置被人为修改，取的配置是被clone的配置!
     * @param paramName 配置的名称
     * @return 返回的配置对象
     *  - undefined 配置不存在时，返回undefined
     *  - object 配置存在的时候，返回相应的对象
     */
    ConfigUtils.getConfigByName = function (paramName) {
        var retCfg = cfg[paramName];
        if (xmcommon_1.utils.isNotNull(retCfg)) {
            return _.cloneDeep(retCfg);
        }
        else {
            return undefined;
        }
    };
    ConfigUtils.stringOpts = function (paramValue, paramDefault) {
        return _.isString(paramValue) ? paramValue : paramDefault;
    };
    ConfigUtils.intOpts = function (paramValue, paramDefault) {
        return Number.isInteger(paramValue) ? paramValue : paramDefault;
    };
    ConfigUtils.numberOpts = function (paramValue, paramDefault) {
        return _.isNumber(paramValue) ? paramValue : paramDefault;
    };
    ConfigUtils.boolOpts = function (paramValue, paramDefault) {
        return _.isBoolean(paramValue) ? paramValue : paramDefault;
    };
    ConfigUtils.objectOpts = function (paramValue, paramDefault) {
        return _.isObject(paramValue) ? paramValue : paramDefault;
    };
    /**
     * 取指定环境的配置文件名
     * @param paramEnv
     */
    ConfigUtils.getConfigNameByEnv = function (paramEnv) {
        return path.join(currProcessPath, configPath, "env.".concat(paramEnv).concat(configFileExt));
    };
    ConfigUtils.initMySQLStoreOptions = function (paramOptions) {
        var _a, _b, _c, _d, _e, _f, _g, _h;
        var ret = {};
        ret.port = this.intOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.port, 3306);
        ret.host = this.stringOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.host, 'localhost');
        ret.database = this.stringOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.database, 'db_session');
        ret.user = this.stringOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.user, 'root');
        ret.password = this.stringOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.password, '');
        ret.createDatabaseTable = this.boolOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.createDatabaseTable, true);
        ret.connectionLimit = this.intOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.connectionLimit, 1);
        ret.chatset = this.stringOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.chatset, 'utf8mb4');
        var schema = this.objectOpts(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema, {});
        ret.schema = schema;
        schema.tableName = this.stringOpts((_a = paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema) === null || _a === void 0 ? void 0 : _a.tableName, 'sessions');
        schema.columnNames = this.objectOpts((_b = paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema) === null || _b === void 0 ? void 0 : _b.columnNames, {});
        schema.columnNames.session_id = this.stringOpts((_d = (_c = paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema) === null || _c === void 0 ? void 0 : _c.columnNames) === null || _d === void 0 ? void 0 : _d.session_id, 'session_id');
        schema.columnNames.expires = this.stringOpts((_f = (_e = paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema) === null || _e === void 0 ? void 0 : _e.columnNames) === null || _f === void 0 ? void 0 : _f.expires, 'expires');
        schema.columnNames.data = this.stringOpts((_h = (_g = paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.schema) === null || _g === void 0 ? void 0 : _g.columnNames) === null || _h === void 0 ? void 0 : _h.data, 'data');
        log.info('session mysql config:\n' + JSON.stringify(ret, null, 2));
        return ret;
    };
    /** 生成连接redis的选项 */
    ConfigUtils.initRedisOptions = function (paramOptions) {
        var port = Number.isSafeInteger(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.port) ? paramOptions.port : 6379;
        var host = _.isString(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.host) ? paramOptions.host : 'localhost';
        var mode = (paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.mode) === 'rediss' ? 'rediss' : 'redis';
        var url = "".concat(mode, "://").concat(host, ":").concat(port);
        var database = Number.isSafeInteger(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.database) ? paramOptions.database : 0;
        var redisOpts = {
            url: url,
            database: database,
            legacyMode: true,
            name: 'lrsession'
        };
        var connectRedisOpts = {};
        if (_.isString(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.password)) {
            redisOpts.password = paramOptions.password;
        }
        if (_.isString(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.username)) {
            redisOpts.username = paramOptions.username;
        }
        if (_.isString(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.name)) {
            redisOpts.name = paramOptions.name;
        }
        connectRedisOpts.ttl = Number.isSafeInteger(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.ttl) ? paramOptions.ttl : 1800;
        connectRedisOpts.prefix = _.isString(paramOptions === null || paramOptions === void 0 ? void 0 : paramOptions.prefix) ? paramOptions.prefix : 'lr_';
        log.info('redis config:\n' + JSON.stringify(redisOpts, null, 2));
        log.info('connect redis config:\n' + JSON.stringify(connectRedisOpts, null, 2));
        return { redisOpts: redisOpts, connectRedisOpts: connectRedisOpts };
    };
    /**
     * 生成mysql的配置，如果不存在，则返回undefined
     * @returns
     */
    ConfigUtils.buildMySQLOption = function () {
        var mysqlOpts = cfg === null || cfg === void 0 ? void 0 : cfg.mysql;
        if (xmcommon_1.utils.isNull(mysqlOpts)) {
            return undefined;
        }
        var retOpts = { type: 'mysql' };
        retOpts.host = _.isString(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.host) ? mysqlOpts.host : 'localhost';
        retOpts.port = Number.isSafeInteger(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.port) ? mysqlOpts.port : 3306;
        retOpts.username = _.isString(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.username) ? mysqlOpts.username : 'root';
        retOpts.password = _.isString(mysqlOpts.password) ? mysqlOpts.password : '';
        retOpts.database = _.isString(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.database) ? mysqlOpts.database : 'test';
        retOpts.entities = Array.isArray(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.entities) ? mysqlOpts.entities : ['dist/db/*{.ts,.js}'];
        retOpts.synchronize = _.isBoolean(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.synchronize) ? mysqlOpts.synchronize : false;
        retOpts.logging = _.isBoolean(mysqlOpts === null || mysqlOpts === void 0 ? void 0 : mysqlOpts.logging) ? mysqlOpts.logging : false;
        log.info('mysqlOptions:' + JSON.stringify(retOpts, null, 4));
        return retOpts;
    };
    /** 生成指定的session选项 */
    ConfigUtils.buildSessionOptions = function () {
        var sessionConfig = cfg === null || cfg === void 0 ? void 0 : cfg.session;
        var type = sessionConfig === null || sessionConfig === void 0 ? void 0 : sessionConfig.type;
        var store;
        switch (type) {
            case 'mysql':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var session = require('express-session');
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var MySQLStore = require('express-mysql-session')(session);
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var mysql = require('mysql2/promise');
                    var opts = this.initMySQLStoreOptions(sessionConfig.mysqlStoreOptions);
                    var mysqlOpts = {
                        port: opts.port,
                        host: opts.host,
                        user: opts.user,
                        database: opts.database,
                        password: opts.password
                    };
                    var pool = mysql.createPool(mysqlOpts);
                    store = new MySQLStore(opts, pool);
                }
                break;
            case 'file':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var session = require('express-session');
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var FileStore = require('session-file-store')(session);
                    store = new FileStore(sessionConfig.fileStoreOptions);
                }
                break;
            case 'redis':
                {
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var session = require('express-session');
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var redis = require('redis');
                    var opts = this.initRedisOptions(sessionConfig.redisOptions);
                    var redisClient = redis.createClient(opts.redisOpts);
                    redisClient.connect();
                    // eslint-disable-next-line @typescript-eslint/no-var-requires
                    var RedisStore = require('connect-redis')(session);
                    store = new RedisStore(__assign({ client: redisClient }, opts.connectRedisOpts));
                }
                break;
            default:
                break;
        }
        var retOptions = {};
        if (sessionConfig === null || sessionConfig === void 0 ? void 0 : sessionConfig.options) {
            retOptions = _.cloneDeep(sessionConfig.options);
        }
        log.info('session options:' + JSON.stringify(retOptions));
        if (xmcommon_1.utils.isNotNull(store)) {
            retOptions.store = store;
        }
        return retOptions;
    };
    /** 加载指定环境的配置 */
    ConfigUtils.loadByEnv = function (paramEnv) {
        var ret = new xmcommon_1.XCommonRet();
        do {
            var localCfg = {
                port: 3000
            };
            var loadDefaultResult = this.loadConfigByEnv(env_utils_1.EnumRuntimeEnv["default"]);
            if (loadDefaultResult.isNotOK) {
                ret = loadDefaultResult;
                break;
            }
            var loadEnvResult = this.loadConfigByEnv(paramEnv);
            if (loadEnvResult.isNotOK) {
                ret = loadEnvResult;
                break;
            }
            xmcommon_1.utils.dataAssign(localCfg, loadDefaultResult.data);
            xmcommon_1.utils.dataAssign(localCfg, loadEnvResult.data);
            xmcommon_1.utils.dataAssign(cfg, localCfg);
            var finalConfig = cfg;
            var destPath = path.join(currProcessPath, configPath, finalPath);
            // 如果不存在，则创建一个
            if (!xmcommon_1.utils.fileExists(destPath)) {
                var result = xmcommon_1.utils.mkdirsSyncEx(destPath);
                if (!result.ret) {
                    ret.setError(-1, result.msg);
                    break;
                }
            }
            var destPathJson = path.join(currProcessPath, configPath, finalPath, "".concat(finalConfigFileName, ".").concat(paramEnv, ".json"));
            this.initRuntimePath();
            var destPathYaml = path.join(currProcessPath, configPath, finalPath, "".concat(finalConfigFileName, ".").concat(paramEnv, ".yaml"));
            fs.writeFileSync(destPathJson, JSON.stringify(finalConfig, null, 4));
            fs.writeFileSync(destPathYaml, yaml.dump(finalConfig));
        } while (false);
        return ret;
    };
    /** 实始化runtime路径 */
    ConfigUtils.initRuntimePath = function () {
        var _a;
        var rtPath = (_a = cfg.path) === null || _a === void 0 ? void 0 : _a.runtime;
        if (!xmcommon_1.utils.isString(rtPath)) {
            return;
        }
        if (path.isAbsolute(rtPath)) {
            // 如果是绝对路径，则直接使用
            runtimePath = rtPath;
        }
        else {
            runtimePath = path.join(process.cwd(), rtPath);
        }
    };
    /** 取当前runtime时间 */
    ConfigUtils.getRuntimePath = function () {
        return runtimePath;
    };
    // }
    ConfigUtils.loadConfigByEnv = function (paramEnv) {
        var fileName = this.getConfigNameByEnv(paramEnv);
        return this.loadConfigByFileName(fileName);
    };
    ConfigUtils.loadConfigByFileName = function (paramFileName) {
        var ret = new xmcommon_1.XCommonRet();
        do {
            if (!fs.existsSync(paramFileName)) {
                ret.setError(error_code_1.EnumErrorCode.FILE_NOT_EXISTS, "\u914D\u7F6E\u6587\u4EF6:".concat(paramFileName, "\u4E0D\u5B58\u5728!"));
                log.error(ret.err);
                break;
            }
            var doc = void 0;
            try {
                doc = fs.readFileSync(paramFileName, 'utf8');
            }
            catch (e) {
                ret.setError(error_code_1.EnumErrorCode.READ_FILE_FAIL, "\u8BFB\u53D6\u914D\u7F6E\u6587\u4EF6\u5931\u8D25:".concat(paramFileName, ", err:").concat(String(e)));
                break;
            }
            try {
                var cfg_1 = yaml.load(doc);
                ret.setOK(cfg_1);
            }
            catch (e) {
                ret.setError(error_code_1.EnumErrorCode.PARSE_FILE_FAIL, "\u89E3\u6790\u914D\u7F6E\u6587\u4EF6\u5931\u8D25:".concat(paramFileName, ", err:").concat(String(e)));
                break;
            }
        } while (false);
        return ret;
    };
    return ConfigUtils;
}());
exports.ConfigUtils = ConfigUtils;
