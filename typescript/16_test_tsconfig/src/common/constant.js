"use strict";
exports.__esModule = true;
exports.GlobalConst = exports.EnumErrType = exports.urlPrefix = void 0;
/** URL 前缀 */
exports.urlPrefix = {
    /** 所有需要拦载的api前缀 */
    API: '/api/',
    /** 本地调用的api，这里不需要做用户登录验证 */
    LOCAL_API: '/api/local/',
    /** 需要检查的api */
    CHECK_API: '/api/fun/'
};
var EnumErrType;
(function (EnumErrType) {
    EnumErrType[EnumErrType["OK"] = 0] = "OK";
    EnumErrType[EnumErrType["Error"] = -1] = "Error";
    EnumErrType[EnumErrType["NeedAdmin"] = 1] = "NeedAdmin";
    EnumErrType[EnumErrType["NeedLogin"] = 2] = "NeedLogin";
    EnumErrType[EnumErrType["RegisterFail"] = 3] = "RegisterFail";
    EnumErrType[EnumErrType["AccountList"] = 4] = "AccountList";
    EnumErrType[EnumErrType["ChangePassword"] = 5] = "ChangePassword";
    EnumErrType[EnumErrType["ChangeInfo"] = 6] = "ChangeInfo";
})(EnumErrType = exports.EnumErrType || (exports.EnumErrType = {}));
exports.GlobalConst = {
    admin: 'admin'
};
