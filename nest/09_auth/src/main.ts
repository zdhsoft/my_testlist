/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：程序入口
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-06
 *************************************************************************/

import './common/log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './common/nest.logger';
import { RequestInterceptor } from './common/request.interceptor';
import { HttpFilterFilter } from './common/http_filter.filter';

const log = getLogger(__filename);
log.info('程序开始启动...');
async function bootstrap() {
    const app = await NestFactory.create(AppModule, {
        logger: new NestLogger(),
    });
    app.useGlobalInterceptors(new RequestInterceptor());
    app.useGlobalFilters(new HttpFilterFilter());
    await app.listen(3000);
    log.info('开始侦听:3000...');
}
bootstrap();
