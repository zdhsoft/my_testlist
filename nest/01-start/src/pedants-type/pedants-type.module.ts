import { Module } from '@nestjs/common';
import { PedantsTypeController } from './pedants-type.controller';

@Module({
  controllers: [PedantsTypeController],
})
export class PedantsTypeModule {}
