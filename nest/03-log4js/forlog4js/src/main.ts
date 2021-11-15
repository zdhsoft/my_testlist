import './log/log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './nest.logger';
const log = getLogger(__filename);
log.info('hello world!');

async function bootstrap() {
    const app = await NestFactory.create(AppModule, { logger: new NestLogger() });
    // const app = await NestFactory.create(AppModule);
    await app.listen(3000);
}
bootstrap();
