import { Body, Controller, Get, HttpCode, HttpStatus, Post, Res, UploadedFile, UseInterceptors } from '@nestjs/common';
import { Response } from 'express';
import { FileInterceptor } from '@nestjs/platform-express';
import { utils, XCommonRet } from 'xmcommon';
import { RetUtils } from 'src/common/ret_utils';
import * as path from 'path';
import * as url from 'url';

@Controller('file')
export class FileController {
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

    @Get('download')
    @HttpCode(HttpStatus.OK)
    public download(@Res() res: Response) {
        const filePath = 'D:/temp/测试.zip';
        const fileName = path.basename(filePath);

        console.log('----------', fileName);
        //fileName = 'aaa.zip';
        // res.setHeader('Content-Disposition', `attachment; filename="${fileName}"`);
        res.download(filePath, (err) => {
            if (!err) {
                console.log('success', 'download', filePath);
                return;
            }

            console.error(err);
            res.send(RetUtils.ret(-1, String(err)));
        });
    }

    @Post('view')
    @HttpCode(HttpStatus.OK)
    public async view(@Res() res: Response) {
        const filePath = 'D:/temp/测试.png';
        res.sendFile(filePath, (err) => {
            if (!err) {
                console.log('success', 'view', filePath);
                return;
            }
            console.error(err);
            res.send(RetUtils.ret(-1, String(err)));
        });
    }
}
