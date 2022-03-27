"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
exports.__esModule = true;
exports.HttpFilterFilter = void 0;
var common_1 = require("@nestjs/common");
var error_code_1 = require("../../../../../../../../src/error/error_code");
var xmcommon_1 = require("xmcommon");
var api_exception_1 = require("./api_exception");
var log = (0, xmcommon_1.getLogger)('HttpException');
var HttpFilterFilter = /** @class */ (function () {
    function HttpFilterFilter() {
    }
    HttpFilterFilter.prototype["catch"] = function (paramException, paramHost) {
        var ctx = paramHost.switchToHttp();
        var response = ctx.getResponse();
        var request = ctx.getRequest();
        var message = paramException.message;
        log.error("\u8BF7\u6C42\u53D1\u751F\u5F02\u5E38: [".concat(request['seq'], "]<== ").concat(request.method, " ").concat(request.path, " ").concat(message));
        var retCode = error_code_1.EnumErrorCode.FAIL;
        var status = common_1.HttpStatus.OK;
        if (paramException instanceof api_exception_1.APIException) {
            retCode = paramException.errCode;
        }
        else if (paramException instanceof common_1.HttpException) {
            status = paramException.getStatus();
        }
        else {
            status = common_1.HttpStatus.INTERNAL_SERVER_ERROR;
        }
        var errorResponse = {
            msg: message,
            ret: retCode,
            statusCode: status,
            url: request.originalUrl
        };
        // 设置返回的状态码、请求头、发送错误信息
        response.status(common_1.HttpStatus.OK);
        response.header('Content-Type', 'application/json; charset=utf-8');
        response.send(errorResponse);
    };
    HttpFilterFilter = __decorate([
        (0, common_1.Catch)(Error)
    ], HttpFilterFilter);
    return HttpFilterFilter;
}());
exports.HttpFilterFilter = HttpFilterFilter;
