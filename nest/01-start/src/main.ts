import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { DdInterceptor } from './dd.interceptor';


async function bootstrap() {
    console.log('...', JSON.stringify(process.argv));
    const app = await NestFactory.create(AppModule);
    app.useGlobalInterceptors(new DdInterceptor());
    await app.listen(3000);
}
bootstrap();
