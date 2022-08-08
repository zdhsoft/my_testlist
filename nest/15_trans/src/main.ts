import './init/init';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './common/nest.logger';
import { RequestInterceptor } from './common/request.interceptor';
import { HttpFilterFilter } from './common/http_filter.filter';
import { NestExpressApplication } from '@nestjs/platform-express';
import session from 'express-session';
import path from 'path';
import { AuthGuard } from './common/auth.guard';
import { EnvUtils } from './env_utils';
import { ConfigUtils } from './init/config_utils';
import { ValidationPipe } from './common/validation_pipe';

const log = getLogger(__filename);
log.info('程序开始启动... 当前环境:' + EnvUtils.env + ' 开发环境:' + EnvUtils.isDev);
async function bootstrap() {
    const globalConfig = ConfigUtils.getConfig();

    const app = await NestFactory.create<NestExpressApplication>(AppModule, {
        logger: new NestLogger(),
    });
    app.use(session(ConfigUtils.buildSessionOptions()));
    // app.useStaticAssets(path.join(process.cwd(), 'public'), { prefix: '/static/' });
    app.useStaticAssets(path.join(process.cwd(), 'public'), {});
    app.setBaseViewsDir(path.join(process.cwd(), 'view')); // 放视图的文件
    app.setViewEngine('ejs');
    app.useGlobalPipes(new ValidationPipe());
    app.useGlobalInterceptors(new RequestInterceptor());
    app.useGlobalFilters(new HttpFilterFilter());
    app.useGlobalGuards(new AuthGuard());

    if (EnvUtils.isDev) {
        // 如果是开发模式，则加载文档
        // eslint-disable-next-line @typescript-eslint/no-var-requires
        const { DocumentBuilder, SwaggerModule } = require('@nestjs/swagger');
        const config = new DocumentBuilder()
            .setTitle('Cats example')
            .setDescription('The cats API description')
            .setVersion('1.0')
            .addTag('cats')
            .build();
        const document = SwaggerModule.createDocument(app, config);
        SwaggerModule.setup('apidoc', app, document);
        log.info('swagger url: /apidoc');
    }

    await app.listen(globalConfig.port as number);
    log.info(`开始侦听:${globalConfig.port}...`);
}
bootstrap();
