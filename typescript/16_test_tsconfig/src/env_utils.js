"use strict";
exports.__esModule = true;
exports.EnvUtils = exports.EnumRuntimeEnv = void 0;
var xmcommon_1 = require("xmcommon");
var _ = require("lodash");
/** 可以环境常量定义 */
var EnumRuntimeEnv;
(function (EnumRuntimeEnv) {
    /** 缺省配置环境 */
    EnumRuntimeEnv["default"] = "default";
    /** 测试 */
    EnumRuntimeEnv["test"] = "test";
    /** 生产环境 */
    EnumRuntimeEnv["production"] = "production";
})(EnumRuntimeEnv = exports.EnumRuntimeEnv || (exports.EnumRuntimeEnv = {}));
/** 全局环境配置 */
var env = {
    env: EnumRuntimeEnv.test,
    isDev: true
};
/** 系统启动传入参数 */
var systemArgs = {};
/** 全局变量工具类 */
var EnvUtils = /** @class */ (function () {
    function EnvUtils() {
    }
    EnvUtils.getSystemArgs = function () {
        return _.clone(systemArgs);
    };
    /** 这个返回的是一个克隆的对象，修改它无意义 */
    EnvUtils.getEnv = function () {
        return _.clone(env);
    };
    Object.defineProperty(EnvUtils, "isDev", {
        /** 判断是否是开发环境 */
        get: function () {
            return env.isDev;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(EnvUtils, "env", {
        /** 取当前环境值 */
        get: function () {
            return env.env;
        },
        enumerable: false,
        configurable: true
    });
    return EnvUtils;
}());
exports.EnvUtils = EnvUtils;
/**
 * 初始化环境值
 */
function initEnv() {
    /** 初始化系统启动入参 */
    var opts = xmcommon_1.utils.options(process.argv);
    var args = opts.args;
    systemArgs.env = args.env;
    var envid = EnumRuntimeEnv.test;
    if (xmcommon_1.utils.isString(systemArgs.env) && EnumRuntimeEnv[systemArgs.env] !== systemArgs.env) {
        envid = systemArgs.env;
    }
    env.env = envid;
    // 除了生产环境，其它都是开发环境
    if (envid === EnumRuntimeEnv.production) {
        env.isDev = false;
    }
    else {
        env.isDev = true;
    }
}
initEnv();
