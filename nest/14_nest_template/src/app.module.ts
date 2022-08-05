import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { ConfigUtils } from './init/config_utils';
import { XRedisService } from './service/redis.service';

const TypeOrmConfig = ConfigUtils.buildMySQLOption();

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
    ],
    controllers: [AppController],
    providers: [AppService, XRedisService],
    exports: [XRedisService],
})
export class AppModule {}
