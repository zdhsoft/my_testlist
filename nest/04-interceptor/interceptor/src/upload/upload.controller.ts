/*
https://docs.nestjs.com/controllers#controllers
*/

import {
    Body,
    Controller,
    Post,
    Res,
    UploadedFile,
    UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { XCommonRet } from 'xmcommon';
import { Response } from 'express';

@Controller('upload')
export class UploadController {
    @Post('up')
    @UseInterceptors(FileInterceptor('file'))
    public up(@UploadedFile() file: Express.Multer.File, @Body() body) {
        const r = new XCommonRet<number>();
        do {
            //
            console.log(file);
            console.log(body);
        } while (false);
        return r;
    }

    @Post('download')
    public download(@Res() res: Response) {
        const filePath =
            'D:/work/svn_doc/lr/04-学习库/01-技术规范/01-开发规范/希为科技TypeScript代码规范.docx';
        res.download(filePath, (err) => {
            if (!err) {
                console.log('success', 'download', filePath);
                return;
            }

            console.error(err);
            res.send({ err: -1, msg: String(err) });
        });
    }

    @Post('view')
    public view(@Res() res: Response) {
        const filePath =
            'D:/temp/企业微信截图_9df5fd96-30b0-4109-9b98-2fec7880fa07.png';
        res.sendFile(filePath, (err) => {
            if (!err) {
                console.log('success', 'view', filePath);
                return;
            }
            console.error(err);
            res.send({ err: -1, msg: String(err) });
        });
    }
}
