import { Controller, Get } from '@nestjs/common';
import { getLogger, utils } from 'xmcommon';

const log = getLogger(__filename);
@Controller('pedants-type')
export class PedantsTypeController {
    public constructor() {
        log.info('------------PedantsTypeController');
    }
    @Get('test')
    async getPedantsType(): Promise<string> {
        log.info('---->pedants-type/test111');
        await utils.sleep(1000);
        log.info('---->pedants-type/test222');
        return '获取所有的挂件类型';
    }
}
