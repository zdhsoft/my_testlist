import { Body, Controller, HttpCode, HttpStatus, Post, Res, UploadedFile, UseInterceptors } from '@nestjs/common';
import { Response } from 'express';
import { FileInterceptor } from '@nestjs/platform-express';
import { utils, XCommonRet } from 'xmcommon';

@Controller('file')
export class FileController {
    // @Post('up')
    // @UseInterceptors(FileInterceptor('file'))
    // public up(@UploadedFile() file: Express.Multer.File, @Body() body) {
    //     const r = new XCommonRet<number>();
    //     do {
    //         //
    //         console.log(file);
    //         console.log(body);
    //     } while (false);
    //     return r;
    // }

    @Post('download')
    @HttpCode(HttpStatus.OK)
    public download(@Res() res: Response) {
        const filePath = 'D:/work/svn_doc/lr/04-学习库/01-技术规范/01-开发规范/希为科技TypeScript代码规范.docxf';
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
    @HttpCode(HttpStatus.OK)
    public async view(@Res() res: Response) {
        const filePath = 'D:/temp/企业微信截图_9df5fd96-30b0-4109-9b98-2fec7880fa07.pngg';
        const [err] = await utils.WaitClassFunctionEx(res, 'sendFile', filePath);
        if (err) {
            res.end();
            return new XCommonRet(-1, String(err));
        }

        // res.sendFile(filePath, (err) => {
        //     if (!err) {
        //         console.log('success', 'view', filePath);
        //         return;
        //     }
        //     console.error(err);
        //     const r = new XCommonRet(-1, String(err));
        //     res.send(r);
        //     // res.status(HttpStatus.OK).send({ ret: -1, msg: String(err) });
        // });
    }
}
