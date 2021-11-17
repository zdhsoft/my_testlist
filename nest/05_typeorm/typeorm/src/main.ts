import './log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { NestLogger } from './nest.logger';

async function bootstrap() {
    const app = await NestFactory.create(AppModule, {
        logger: new NestLogger(),
    });
    const port = 3000;
    await app.listen(port);
    console.log('start listen: ' + port);
}
bootstrap();
