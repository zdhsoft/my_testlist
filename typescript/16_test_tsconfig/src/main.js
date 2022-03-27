"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
exports.__esModule = true;
require("./init/init");
var core_1 = require("@nestjs/core");
var app_module_1 = require("./app.module");
var xmcommon_1 = require("xmcommon");
var nest_logger_1 = require("./common/nest.logger");
var request_interceptor_1 = require("./common/request.interceptor");
var http_filter_filter_1 = require("./common/http_filter.filter");
var session = require("express-session");
var path = require("path");
var auth_guard_1 = require("./common/auth.guard");
var env_utils_1 = require("./env_utils");
var config_utils_1 = require("./init/config_utils");
var validation_pipe_1 = require("./common/validation_pipe");
var log = (0, xmcommon_1.getLogger)(__filename);
log.info('程序开始启动... 当前环境:' + env_utils_1.EnvUtils.env + ' 开发环境:' + env_utils_1.EnvUtils.isDev);
function bootstrap() {
    return __awaiter(this, void 0, void 0, function () {
        var globalConfig, app, _a, DocumentBuilder, SwaggerModule, config, document_1;
        return __generator(this, function (_b) {
            switch (_b.label) {
                case 0:
                    globalConfig = config_utils_1.ConfigUtils.getConfig();
                    return [4 /*yield*/, core_1.NestFactory.create(app_module_1.AppModule, {
                            logger: new nest_logger_1.NestLogger()
                        })];
                case 1:
                    app = _b.sent();
                    app.use(session(config_utils_1.ConfigUtils.buildSessionOptions()));
                    // app.useStaticAssets(path.join(process.cwd(), 'public'), { prefix: '/static/' });
                    app.useStaticAssets(path.join(process.cwd(), 'public'), {});
                    app.setBaseViewsDir(path.join(process.cwd(), 'view')); // 放视图的文件
                    app.setViewEngine('ejs');
                    app.useGlobalPipes(new validation_pipe_1.ValidationPipe());
                    app.useGlobalInterceptors(new request_interceptor_1.RequestInterceptor());
                    app.useGlobalFilters(new http_filter_filter_1.HttpFilterFilter());
                    app.useGlobalGuards(new auth_guard_1.AuthGuard());
                    if (env_utils_1.EnvUtils.isDev) {
                        _a = require('@nestjs/swagger'), DocumentBuilder = _a.DocumentBuilder, SwaggerModule = _a.SwaggerModule;
                        config = new DocumentBuilder()
                            .setTitle('Cats example')
                            .setDescription('The cats API description')
                            .setVersion('1.0')
                            .addTag('cats')
                            .build();
                        document_1 = SwaggerModule.createDocument(app, config);
                        SwaggerModule.setup('apidoc', app, document_1);
                        log.info('swagger url: /apidoc');
                    }
                    return [4 /*yield*/, app.listen(globalConfig.port)];
                case 2:
                    _b.sent();
                    log.info("\u5F00\u59CB\u4FA6\u542C:".concat(globalConfig.port, "..."));
                    return [2 /*return*/];
            }
        });
    });
}
bootstrap();
