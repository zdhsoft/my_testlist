"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.logger = exports.LoggerMiddleware = void 0;
const common_1 = require("@nestjs/common");
const xmcommon_1 = require("xmcommon");
const log = (0, xmcommon_1.getLogger)(__filename);
let LoggerMiddleware = class LoggerMiddleware {
    async use(req, res, next) {
        next();
    }
};
LoggerMiddleware = __decorate([
    (0, common_1.Injectable)()
], LoggerMiddleware);
exports.LoggerMiddleware = LoggerMiddleware;
async function logger(req, res, next) {
    log.info('---->>>', req.url);
    await next();
    log.info('----<<<', req.url);
}
exports.logger = logger;
//# sourceMappingURL=logger.middleware.js.map