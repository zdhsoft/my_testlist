"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.DdInterceptor = void 0;
const common_1 = require("@nestjs/common");
const operators_1 = require("rxjs/operators");
const xmcommon_1 = require("xmcommon");
const log = (0, xmcommon_1.getLogger)(__filename);
let DdInterceptor = class DdInterceptor {
    intercept(context, next) {
        const start = Date.now();
        const host = context.switchToHttp();
        const request = host.getRequest();
        const urlInfo = `${request.method} ${request.url}`;
        log.info(`==> ${urlInfo}`);
        return next.handle().pipe((0, operators_1.tap)(() => {
            log.info(`<== ${urlInfo} ${Date.now() - start} ms`);
        }));
    }
};
DdInterceptor = __decorate([
    (0, common_1.Injectable)()
], DdInterceptor);
exports.DdInterceptor = DdInterceptor;
//# sourceMappingURL=dd.interceptor.js.map