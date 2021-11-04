import { Test, TestingModule } from '@nestjs/testing';
import { PedantsTypeController } from './pedants-type.controller';

describe('PedantsTypeController', () => {
  let controller: PedantsTypeController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [PedantsTypeController],
    }).compile();

    controller = module.get<PedantsTypeController>(PedantsTypeController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
