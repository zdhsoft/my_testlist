import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function bootstrap() {
    console.log('...', JSON.stringify(process.argv));
    const app = await NestFactory.create(AppModule);
    await app.listen(3000);
}
bootstrap();
