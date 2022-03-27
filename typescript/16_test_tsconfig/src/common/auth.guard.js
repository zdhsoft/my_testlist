"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
exports.__esModule = true;
exports.AuthGuard = void 0;
var common_1 = require("@nestjs/common");
// import { getLogger } from 'xmcommon';
var constant_1 = require("./constant");
var api_exception_1 = require("./api_exception");
var error_code_1 = require("../../../../../../../../src/error/error_code");
// const log = getLogger(__filename);
var AuthGuard = /** @class */ (function () {
    function AuthGuard() {
    }
    AuthGuard.prototype.canActivate = function (context) {
        var _a;
        var host = context.switchToHttp();
        var req = host.getRequest();
        var url = req.path;
        var ret = false;
        do {
            if (url.startsWith(constant_1.urlPrefix.API)) {
                if (url.startsWith(constant_1.urlPrefix.LOCAL_API)) {
                    ret = true;
                }
                else {
                    if (((_a = req.session) === null || _a === void 0 ? void 0 : _a.isLogin) === true) {
                        ret = true;
                    }
                    else {
                        // 如果没有登录，则这里返回false
                        ret = false;
                    }
                }
            }
            else {
                ret = true;
            }
        } while (false);
        if (!ret) {
            throw new api_exception_1.APIException(error_code_1.EnumErrorCode.NOT_LOGIN, '您还没有登录!', url);
        }
        return ret;
    };
    AuthGuard = __decorate([
        (0, common_1.Injectable)()
    ], AuthGuard);
    return AuthGuard;
}());
exports.AuthGuard = AuthGuard;
