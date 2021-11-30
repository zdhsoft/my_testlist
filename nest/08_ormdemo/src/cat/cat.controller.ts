import { Controller, HttpException, Post } from '@nestjs/common';

@Controller('cat')
export class CatController {
    @Post('count')
    async Count() {
        // throw new Error('aaaaaaaaaaaaa');
        throw new HttpException('aaaaaaaaaaaaa', 399);
    }
}
