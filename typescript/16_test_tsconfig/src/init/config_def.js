"use strict";
exports.__esModule = true;
exports.ILRConfigSessionType = void 0;
/** 会话类型 */
var ILRConfigSessionType;
(function (ILRConfigSessionType) {
    /** 文件存储类型 */
    ILRConfigSessionType["file"] = "file";
    /** redis存放类型 */
    ILRConfigSessionType["redis"] = "redis";
    /** 这个是默认的 */
    ILRConfigSessionType["memory"] = "memory";
    /** 存放在mysql数据库 */
    ILRConfigSessionType["mysql"] = "mysql";
})(ILRConfigSessionType = exports.ILRConfigSessionType || (exports.ILRConfigSessionType = {}));
