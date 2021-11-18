/*
https://docs.nestjs.com/controllers#controllers
*/

import {
    Body,
    Controller,
    Post,
    UploadedFile,
    UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { XCommonRet } from 'xmcommon';

@Controller('upload')
export class UploadController {
    @Post('up')
    @UseInterceptors(FileInterceptor('file'))
    up(@UploadedFile() file: Express.Multer.File, @Body() body) {
        const r = new XCommonRet<number>();
        do {
            //
            console.log(file);
            console.log(body);
        } while (false);
        return r.toJSON();
    }
}
