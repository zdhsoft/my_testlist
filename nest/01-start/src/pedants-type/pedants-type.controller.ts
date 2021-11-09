import { Controller, Get } from '@nestjs/common';

@Controller('pedants-type')
export class PedantsTypeController {
    @Get('test')
    getPedantsType(): string {
        return '获取所有的挂件类型';
    }
}
