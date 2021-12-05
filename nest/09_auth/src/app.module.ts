/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename app.module.ts
 * @summary：主模块加载入口
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-06
 *************************************************************************/

import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppController } from './app.controller';
import { AppService } from './app.service';

@Module({
    imports: [
        TypeOrmModule.forRoot({
            type: 'mysql',
            host: 'localhost',
            port: 3306,
            username: 'game',
            password: 'game123',
            database: 'orm',
            entities: ['dist/**/*.entity{.ts,.js}'],
            synchronize: false,
            logging: true,
        }),
    ],
    controllers: [AppController],
    providers: [AppService],
})
export class AppModule {}
