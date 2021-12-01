import { Body, Controller, HttpCode, HttpStatus, Post, Res, UploadedFile, UseInterceptors } from '@nestjs/common';
import { Response } from 'express';
import { FileInterceptor } from '@nestjs/platform-express';
import { getLogger, utils, XCommonRet } from 'xmcommon';
import { RetUtils } from 'src/common/ret_utils';

const log = getLogger(__filename);
@Controller('file')
export class FileController {
    /**
     * 文件上传示例
     * - 使用这个示例，要安装包: npm install @types/multer --save-dev
     */
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
    /** 文件下载示例 */
    @Post('download')
    @HttpCode(HttpStatus.OK)
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
    @HttpCode(HttpStatus.OK)
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
