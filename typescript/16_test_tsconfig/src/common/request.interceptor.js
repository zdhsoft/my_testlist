"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
exports.__esModule = true;
exports.RequestInterceptor = void 0;
var common_1 = require("@nestjs/common");
var operators_1 = require("rxjs/operators");
var xmcommon_1 = require("xmcommon");
var ret_utils_1 = require("./ret_utils");
var constant_1 = require("./constant");
var log = (0, xmcommon_1.getLogger)(__filename);
/** 每次请求的记数器 */
var requestSeq = 0;
/**
 * 全局拦截器类
 */
var RequestInterceptor = /** @class */ (function () {
    function RequestInterceptor() {
    }
    /**
     * 拦截器入口
     * @param context 上下文对象
     * @param next 后续调用函数
     * @returns
     */
    RequestInterceptor.prototype.intercept = function (context, next) {
        /** 请求开始时间 */
        var start = Date.now();
        /** 当前环境 */
        var host = context.switchToHttp();
        /** 请求对象 */
        var req = host.getRequest();
        /** 响应对象 */
        var res = host.getResponse();
        /** 当前计数 */
        var seq = requestSeq++;
        /** 当前URL */
        var url = req.url; // req.path;
        /** 当前URL */
        var urlInfo = "".concat(req.method, " ").concat(url);
        log.info("[".concat(seq, "]==> ").concat(urlInfo));
        req['seq'] = seq;
        var isCheckAPI = url.startsWith(constant_1.urlPrefix.API);
        if (isCheckAPI) {
            return next
                .handle()
                .pipe((0, operators_1.map)(function (data) {
                /* 这里拦截POST返回的statusCode，它默认返回是201, 这里改为200 */
                if (res.statusCode === common_1.HttpStatus.CREATED && req.method === 'POST') {
                    res.statusCode = common_1.HttpStatus.OK;
                }
                // 这里要求所有的请求返回，都是XCommonRet
                if (data instanceof xmcommon_1.XCommonRet) {
                    return ret_utils_1.RetUtils.byCommonRet(data);
                }
                else if (data === undefined) {
                    log.error('--------- data is undefine!');
                    return data;
                }
                else {
                    var r = {
                        ret: -1,
                        msg: '这个请求返回的不是XCommonRet对象!',
                        url: req.originalUrl
                    };
                    log.error('返回错误:' + JSON.stringify(r));
                    return data;
                }
            }))
                .pipe(
            // 这里打印请求处理完成的信息
            (0, operators_1.tap)(function () { return log.info("[".concat(seq, "]<== ").concat(urlInfo, " ").concat(Date.now() - start, " ms")); }));
        }
        else {
            return next.handle().pipe(
            // 这里打印请求处理完成的信息
            (0, operators_1.tap)(function () { return log.info("[".concat(seq, "]<== ").concat(urlInfo, " ").concat(Date.now() - start, " ms")); }));
        }
    };
    RequestInterceptor = __decorate([
        (0, common_1.Injectable)()
    ], RequestInterceptor);
    return RequestInterceptor;
}());
exports.RequestInterceptor = RequestInterceptor;
