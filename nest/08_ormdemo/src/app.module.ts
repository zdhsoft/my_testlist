import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from './user/user.module';
import { CatModule } from './cat/cat.module';

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
        UserModule,
        CatModule,
    ],
    controllers: [AppController],
    providers: [AppService],
})
export class AppModule {
    //
}
