import './log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './nest.logger';
import { RequestInterceptor } from './request.interceptor';
const log = getLogger(__filename);
log.info('程序开始启动...');
async function bootstrap() {
    const app = await NestFactory.create(AppModule, {
        logger: new NestLogger(),
    });
    app.useGlobalInterceptors(new RequestInterceptor());
    await app.listen(3000);
    log.info('开始侦听:3000...');
}
bootstrap();
