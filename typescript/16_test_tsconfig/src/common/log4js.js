"use strict";
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
exports.__esModule = true;
exports.EnumLogLevel = void 0;
var path = require("path");
var log4js = require("log4js");
var util = require("util");
var xmcommon_1 = require("xmcommon");
/** 普通日志文件输出 */
var normalLog;
/** 错误日志文件输出 */
var errorLog;
var consoleLog;
/** 日志级别枚举 */
var EnumLogLevel;
(function (EnumLogLevel) {
    EnumLogLevel["TRACE"] = "TRACE";
    EnumLogLevel["DEBUG"] = "DEBUG";
    EnumLogLevel["LOG"] = "  LOG";
    EnumLogLevel["INFO"] = " INFO";
    EnumLogLevel["ERROR"] = "ERROR";
    EnumLogLevel["WARN"] = " WARN";
})(EnumLogLevel = exports.EnumLogLevel || (exports.EnumLogLevel = {}));
/** 颜色样式 */
var styles = {
    // styles
    bold: [1, 22],
    italic: [3, 23],
    underline: [4, 24],
    inverse: [7, 27],
    // grayscale
    white: [37, 39],
    grey: [90, 39],
    black: [90, 39],
    // colors
    blue: [34, 39],
    cyan: [36, 39],
    green: [32, 39],
    magenta: [35, 39],
    red: [91, 39],
    yellow: [33, 39]
};
/**
 * 给日志的head上色
 * @param msg 日志消息
 * @param paramColorStyle 日志颜色
 * @return 上色后的日志
 */
function colored(msg, paramColorStyle) {
    if (paramColorStyle) {
        return "\u001B[".concat(paramColorStyle[0], "m").concat(msg.head, "\u001B[").concat(paramColorStyle[1], "m ").concat(msg.info);
    }
    else {
        return "".concat(msg.head, " ").concat(msg.info);
    }
}
/**
 * 生成日志
 * @param categoryName 类名名称
 * @param level 日志级别
 * @param data 日志参数内容
 * @return
 */
function buildLog(categoryName, level) {
    var data = [];
    for (var _i = 2; _i < arguments.length; _i++) {
        data[_i - 2] = arguments[_i];
    }
    return {
        head: "[".concat(xmcommon_1.datetimeUtils.nowDateString(), " ").concat(level, "][").concat(categoryName, "]"),
        info: util.format.apply(util, data)
    };
}
/**
 * 基于Log4js实际日志
 */
var XLogFor4js = /** @class */ (function () {
    function XLogFor4js(paramName) {
        this.m_name = paramName;
    }
    Object.defineProperty(XLogFor4js.prototype, "name", {
        get: function () {
            return this.m_name;
        },
        enumerable: false,
        configurable: true
    });
    XLogFor4js.prototype.trace = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.TRACE], paramLog, false));
        normalLog.trace(colored(logInfo));
        consoleLog.trace(colored(logInfo, styles.blue));
    };
    XLogFor4js.prototype.debug = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.DEBUG], paramLog, false));
        normalLog.debug(colored(logInfo));
        consoleLog.debug(colored(logInfo, styles.cyan));
    };
    XLogFor4js.prototype.log = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.LOG], paramLog, false));
        normalLog.info(colored(logInfo));
        consoleLog.info(colored(logInfo, styles.magenta));
    };
    XLogFor4js.prototype.info = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.INFO], paramLog, false));
        normalLog.info(colored(logInfo));
        consoleLog.info(colored(logInfo, styles.green));
    };
    XLogFor4js.prototype.error = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.ERROR], paramLog, false));
        var logMsg = colored(logInfo);
        normalLog.error(logMsg);
        errorLog.error(logMsg);
        consoleLog.error(colored(logInfo, styles.red));
    };
    XLogFor4js.prototype.warn = function () {
        var paramLog = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            paramLog[_i] = arguments[_i];
        }
        var logInfo = buildLog.apply(void 0, __spreadArray([this.name, EnumLogLevel.WARN], paramLog, false));
        var logMsg = colored(logInfo);
        normalLog.warn(logMsg);
        errorLog.warn(logMsg);
        consoleLog.warn(colored(logInfo, styles.yellow));
    };
    return XLogFor4js;
}());
/**
 * 初始化日志
 * @param paramConfigName 配置文件名（js文件）
 */
function InitLog(paramConfigName) {
    // eslint-disable-next-line @typescript-eslint/no-var-requires
    var cfg = require(paramConfigName);
    log4js.configure(cfg);
    normalLog = log4js.getLogger('default');
    errorLog = log4js.getLogger('error');
    consoleLog = log4js.getLogger('console');
    var LogManager = (0, xmcommon_1.GetLogManager)();
    LogManager.setCreateLog(function (paramTag) { return new XLogFor4js(paramTag); });
    LogManager.setDefaultLog(new XLogFor4js('default'));
    var conLog = LogManager.getLogger('console');
    // 绑定控制台的日志
    console.log = conLog.info.bind(conLog);
    console.error = conLog.error.bind(conLog);
    console.debug = conLog.debug.bind(conLog);
    console.warn = conLog.warn.bind(conLog);
    console.trace = conLog.trace.bind(conLog);
}
/** 生成绝对配置文件路径 */
var configFile = path.join(process.cwd(), 'config', 'log4js.js');
/* 执行初始化 */
InitLog(configFile);
