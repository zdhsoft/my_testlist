"use strict";
exports.__esModule = true;
exports.EnumErrorCode = void 0;
/** 项目的错误码 */
var EnumErrorCode;
(function (EnumErrorCode) {
    EnumErrorCode[EnumErrorCode["OK"] = 0] = "OK";
    /** 系统错误 */
    EnumErrorCode[EnumErrorCode["FAIL"] = 1] = "FAIL";
    /** 文件不存在 */
    EnumErrorCode[EnumErrorCode["FILE_NOT_EXISTS"] = 10000] = "FILE_NOT_EXISTS";
    /** 目录不存在 */
    EnumErrorCode[EnumErrorCode["DIR_NOT_EXISTS"] = 10001] = "DIR_NOT_EXISTS";
    /** 读取文件失败 */
    EnumErrorCode[EnumErrorCode["READ_FILE_FAIL"] = 10002] = "READ_FILE_FAIL";
    /** 解析文件失败 */
    EnumErrorCode[EnumErrorCode["PARSE_FILE_FAIL"] = 10003] = "PARSE_FILE_FAIL";
    /** 请求参数校验失败 */
    EnumErrorCode[EnumErrorCode["QUERY_PARAM_INVALID_FAIL"] = 10004] = "QUERY_PARAM_INVALID_FAIL";
    // /** 密码与密码确认不相等 */
    // PASSWORD_NOT_EQU_REPASSWORD = 10005,
    // /** TypeORM执行SQL语句报错 */
    // TYPEORM_SQL_ERROR = 10006,
    // /** 没有找到指定id的用户 */
    // NOT_FOUND_USER_BY_ID = 10007,
    // /** 没有找到指定account的用户 */
    // NOT_FOUND_USER_BY_ACCOUNT = 10008,
    // /** 不存在的环境 */
    // NOT_EXIST_ENV = 10009,
    /** 你还没有登录 */
    EnumErrorCode[EnumErrorCode["NOT_LOGIN"] = 10010] = "NOT_LOGIN";
})(EnumErrorCode = exports.EnumErrorCode || (exports.EnumErrorCode = {}));
