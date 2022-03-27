"use strict";
exports.__esModule = true;
exports.RetUtils = void 0;
var xmcommon_1 = require("xmcommon");
/**
 * 返回值工具类
 */
var RetUtils = /** @class */ (function () {
    function RetUtils() {
    }
    /**
     * 生成返回对象
     * @param paramErr 错误码
     * @param paramErrMsg 错误信息
     * @param paramData 返回的数据
     * @param paramURL 请求时的url
     * @returns 请求返回的数据对象
     */
    RetUtils.ret = function (paramErr, paramErrMsg, paramData, paramURL) {
        return {
            ret: paramErr,
            msg: paramErrMsg,
            data: paramData,
            url: paramURL
        };
    };
    /**
     * 根据XCommonRet的对象生成返回对象
     * @param paramRet XCommonRet对象实例
     * @returns 请求返回的数据对象
     */
    RetUtils.byCommonRet = function (paramRet) {
        var data = xmcommon_1.utils.isNull(paramRet.data) ? undefined : paramRet.data;
        return {
            ret: paramRet.err,
            msg: paramRet.msg,
            data: data
        };
    };
    return RetUtils;
}());
exports.RetUtils = RetUtils;
