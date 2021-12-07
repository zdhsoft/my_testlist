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
import { AuthModule } from './auth/auth.module';
import { UserModule } from './user/user.module';
import { LoginModule } from './login/login.module';

@Module({
    imports: [
        TypeOrmModule.forRoot({
            type: 'mysql',
            host: 'localhost',
            port: 3306,
            username: 'game',
            password: 'game123',
            database: 'orm',
            entities: ['dist/entify/*.js'],
            synchronize: false,
            logging: true,
        }),
        AuthModule,
        UserModule,
        LoginModule,
    ],
    controllers: [AppController],
    providers: [AppService],
    exports: [UserModule],
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3
    3+636
})
export class AppModule {}
