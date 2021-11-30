import * as path from 'path';
import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';

import { TypeOrmModule, TypeOrmModuleOptions } from '@nestjs/typeorm';
import { CatModule } from './cat/cat.module';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);

/** 生成绝对配置文件路径 */
const ormConfigFile = path.join(process.cwd(), 'config', 'ormconfig');

// eslint-disable-next-line @typescript-eslint/no-var-requires
const cfg = require(ormConfigFile) as TypeOrmModuleOptions;
log.info(JSON.stringify(cfg, null, 2));
@Module({
    imports: [CatModule, TypeOrmModule.forRoot(cfg)],
    controllers: [AppController],
    providers: [AppService],
})
export class AppModule {}
