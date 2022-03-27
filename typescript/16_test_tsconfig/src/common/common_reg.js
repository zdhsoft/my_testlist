"use strict";
exports.__esModule = true;
exports.RegExpUtils = exports.CommonRegExp = void 0;
var xmcommon_1 = require("xmcommon");
/** 常用正则表达式 */
exports.CommonRegExp = {
    /** YYYY-MM-DD hh:mm:ss 格式的正则表达式 */
    dateTime: /^[1-2]\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\d):[0-5]\d:[0-5]\d$/,
    /** 货币类正则表达式 */
    curreny: /^\d+(?:\.\d{0,2})?$/,
    /** YYYY-MM-DD 支持 . - / \ 空格分隔符 格式 */
    baseDate: /^([1-2]\d{3})[./\-\\\ ](0[1-9]|1[0-2])[./\-\\\ ](0[1-9]|[1-2][0-9]|3[0-1])$/,
    /** YYYY-MM-DD 格式的日期正则表达式 */
    simpleDate: /^([1-2]\d{3})(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])$/,
    /** hh:mm:ss的正则表达式 */
    baseTime: /^([0-1]\d{1}|2[0-3]):([0-5]\d{1}):([0-5]\d{1})$/,
    /** hhmmss的正则表达式 */
    simpleTime: /^([0-1]\d{1}|2[0-3])([0-5]\d{1})([0-5]\d{1})$/
};
/** 正则表达式相关工具 */
var RegExpUtils = /** @class */ (function () {
    function RegExpUtils() {
    }
    RegExpUtils.date = function (paramValue) {
        var v = String(paramValue);
        var r = exports.CommonRegExp.baseDate.exec(v);
        if (xmcommon_1.utils.isNull(r)) {
            r = exports.CommonRegExp.simpleDate.exec(v);
        }
        if (xmcommon_1.utils.isNotNull(r)) {
            r.splice(0, 1);
        }
        return r;
    };
    return RegExpUtils;
}());
exports.RegExpUtils = RegExpUtils;
