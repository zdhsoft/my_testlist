import { Body, Controller, HttpCode, HttpStatus, Post, Res, UploadedFile, UploadedFiles, UseInterceptors } from '@nestjs/common';
import { Response } from 'express';
import { AnyFilesInterceptor, FileFieldsInterceptor, FileInterceptor, FilesInterceptor } from '@nestjs/platform-express';
import { getLogger, utils, XCommonRet } from 'xmcommon';
import { RetUtils } from 'src/common/ret_utils';

const log = getLogger(__filename);
@Controller('file')
export class FileController {
    /**
     * 文件上传示例 单个文件上传，上传的字段是file
     * - 使用这个示例，要安装包: npm install @types/multer --save-dev
     */
    @Post('up')
    @UseInterceptors(FileInterceptor('file'))
    public up(@UploadedFile() file: Express.Multer.File, @Body() body) {
        const r = new XCommonRet<number>();
        do {
            //
            delete file.buffer;
            log.info(JSON.stringify(file, null, 2));
            log.info(JSON.stringify(body, null, 2));
        } while (false);
        return r;
    }
    /**
     * 多文件上传示例, 会存在多个file的文件字段。
     * - 使用这个示例，要安装包: npm install @types/multer --save-dev
     */
    @Post('upmult')
    @UseInterceptors(FilesInterceptor('file'))
    public upMult(@UploadedFiles() files: Express.Multer.File[], @Body() body) {
        const r = new XCommonRet<number>();
        do {
            let cnt = 0;
            for (const f of files) {
                delete f.buffer;
                cnt++;
                log.info(`[${cnt}]=${JSON.stringify(f)}`);
            }
            log.info(JSON.stringify(body, null, 2));
        } while (false);
        return r;
    }
    /**
     * 多文件上传示例, 会存在多个file的文件字段和多个pic字段
     * - 使用这个示例，要安装包: npm install @types/multer --save-dev
     */
    @Post('upmultex')
    @UseInterceptors(FileFieldsInterceptor([{ name: 'file' }, { name: 'pic' }]))
    public upMultEx(@UploadedFiles() files: { file?: Express.Multer.File[]; pic?: Express.Multer.File[] }, @Body() body) {
        const r = new XCommonRet<number>();
        do {
            let cnt = 0;
            files?.file?.forEach((f) => {
                delete f.buffer;
                cnt++;
                log.info(`[${cnt}]=${JSON.stringify(f)}`);
            });
            files?.pic?.forEach((f) => {
                delete f.buffer;
                cnt++;
                log.info(`[${cnt}]=${JSON.stringify(f)}`);
            });
            log.info(JSON.stringify(body, null, 2));
        } while (false);
        return r;
    }

    /**
     * 多文件上传示例, 会存在多个file的文件字段。
     * - 使用这个示例，要安装包: npm install @types/multer --save-dev
     */
    @Post('upany')
    @UseInterceptors(AnyFilesInterceptor())
    public upAny(@UploadedFiles() files: Express.Multer.File[], @Body() body) {
        const r = new XCommonRet<number>();
        do {
            let cnt = 0;
            for (const f of files) {
                delete f.buffer;
                cnt++;
                log.info(`[${cnt}]=${JSON.stringify(f)}`);
            }
            log.info(JSON.stringify(body, null, 2));
        } while (false);
        return r;
    }

    /** 文件下载示例 */
    @Post('download')
    public async download(@Res() res: Response) {
        const filePath = 'D:/temp/测试.zip';
        const [err] = await utils.WaitClassFunctionEx(res, 'download', filePath);
        const r = new XCommonRet();
        if (err) {
            r.setError(-1, String(err));
            log.error('下载文件失败：' + r.msg);
            res.send(RetUtils.byCommonRet(r));
            return r;
        } else {
            log.info('下载文件成功:' + filePath);
            return r;
        }
    }
    /** 文件查看 */
    @Post('view')
    public async view(@Res() res: Response) {
        const filePath = 'D:/temp/测试.png';
        const [err] = await utils.WaitClassFunctionEx(res, 'sendFile', filePath);
        const r = new XCommonRet();
        if (err) {
            r.setError(-1, String(err));
            log.error('查看文件失败：' + r.msg);
            res.send(RetUtils.byCommonRet(r));
            return r;
        } else {
            log.info('查看文件成功:' + filePath);
            return r;
        }
    }
}
