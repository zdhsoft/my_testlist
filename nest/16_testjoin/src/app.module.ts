import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { XAppController } from './app.controller';
import { XAppService } from './app.service';
import { Account } from './db/account';
import { App } from './db/app';
import { User } from './db/user';
import { XConfigUtils } from './init/config_utils';
import { XRedisService } from './service/redis.service';

const TypeOrmConfig = XConfigUtils.buildMySQLOption();

@Module({
    imports: [
        // TypeOrmModule.forRoot({
        //     type: 'mysql',
        //     host: 'localhost',
        //     port: 3306,
        //     username: 'game',
        //     password: 'game123',
        //     database: 'orm',
        //     entities: ['dist/**/*.entity{.ts,.js}'],
        //     synchronize: false,
        //     logging: true,
        // }),
        TypeOrmModule.forRoot(TypeOrmConfig),
        TypeOrmModule.forFeature([Account, User, App]),
    ],
    controllers: [XAppController],
    providers: [XAppService, XRedisService],
    exports: [XRedisService],
})
export class XAppModule {}
