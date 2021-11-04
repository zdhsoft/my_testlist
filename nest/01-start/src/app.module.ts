import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { PedantsTypeModule } from './pedants-type/pedants-type.module';

@Module({
  imports: [PedantsTypeModule],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
