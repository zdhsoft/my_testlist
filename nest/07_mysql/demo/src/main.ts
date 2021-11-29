import './common/log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './common/nest.logger';
const log = getLogger(__filename);
log.info('程序开始启动...');
async function bootstrap() {
    const app = await NestFactory.create(AppModule, {
        logger: new NestLogger(),
    });
    await app.listen(3000);
    log.info('开始侦听:3000...');
}
bootstrap();
