"use strict";
exports.__esModule = true;
exports.NestLogger = void 0;
var xmcommon_1 = require("xmcommon");
var log = (0, xmcommon_1.getLogger)('nest');
/**
 * nest的日志类
 */
var NestLogger = /** @class */ (function () {
    function NestLogger() {
    }
    NestLogger.prototype.log = function () {
        var msg = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            msg[_i] = arguments[_i];
        }
        log.info.apply(log, msg);
    };
    NestLogger.prototype.error = function () {
        var msg = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            msg[_i] = arguments[_i];
        }
        log.error.apply(log, msg);
    };
    NestLogger.prototype.warn = function () {
        var msg = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            msg[_i] = arguments[_i];
        }
        log.warn.apply(log, msg);
    };
    NestLogger.prototype.debug = function () {
        var msg = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            msg[_i] = arguments[_i];
        }
        log.debug.apply(log, msg);
    };
    NestLogger.prototype.verbose = function () {
        var msg = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            msg[_i] = arguments[_i];
        }
        log.trace.apply(log, msg);
    };
    return NestLogger;
}());
exports.NestLogger = NestLogger;
