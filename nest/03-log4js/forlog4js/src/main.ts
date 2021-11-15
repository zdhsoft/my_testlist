import './log/log4js';

import {getLogger} from 'xmcommon';
const log = getLogger(__filename);
log.info('hello world!');
// import { NestFactory } from '@nestjs/core';
// import { AppModule } from './app.module';

// async function bootstrap() {
//     const app = await NestFactory.create(AppModule);
//     await app.listen(3000);
// }
// bootstrap();
