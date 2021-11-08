"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const core_1 = require("@nestjs/core");
const app_module_1 = require("./app.module");
const loglist = ['log', 'error', 'warn', 'debug', 'verbose'];
async function bootstrap() {
    console.log('...', JSON.stringify(process.argv));
    const app = await core_1.NestFactory.create(app_module_1.AppModule, { logger: loglist });
    await app.listen(3000);
}
bootstrap();
//# sourceMappingURL=main.js.map