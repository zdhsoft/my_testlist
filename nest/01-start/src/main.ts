import { NestFactory } from '@nestjs/core';
import { getLogger } from 'xmcommon';
import { AppModule } from './app.module';
import { DdInterceptor } from './dd.interceptor';

const log = getLogger(__filename);

async function bootstrap() {
    log.info('...', JSON.stringify(process.argv));
    const app = await NestFactory.create(AppModule);
    app.useGlobalInterceptors(new DdInterceptor());
    await app.listen(3000);
}
bootstrap();
