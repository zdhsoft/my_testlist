"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
exports.__esModule = true;
exports.APIException = void 0;
/**
 * API调用的默认异常
 */
var APIException = /** @class */ (function (_super) {
    __extends(APIException, _super);
    function APIException(paramErrorCode, paramErrMsg, paramURL, paramMethod) {
        var _this = _super.call(this, paramErrMsg) || this;
        _this.m_ErrCode = paramErrorCode;
        _this.name = 'APIException';
        _this.m_URL = paramURL;
        _this.m_Method = paramMethod;
        return _this;
    }
    Object.defineProperty(APIException.prototype, "errCode", {
        get: function () {
            return this.m_ErrCode;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(APIException.prototype, "url", {
        get: function () {
            return this.m_URL;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(APIException.prototype, "method", {
        get: function () {
            return this.m_Method;
        },
        enumerable: false,
        configurable: true
    });
    APIException.prototype.toJSON = function () {
        return {
            errCode: this.m_ErrCode,
            message: this.message,
            url: this.m_URL,
            method: this.m_Method
        };
    };
    return APIException;
}(Error));
exports.APIException = APIException;
