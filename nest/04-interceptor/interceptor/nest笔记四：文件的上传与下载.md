# nest笔记四：文件的上传与下载
nest是基于express之上的，所以，其文件上传和下载的功能，实际上就是express的功能。
## 下载
文件下载有两种，一个是sendFile，一个是download。
- 其实download会在浏览器显示另存为...，它主要是在响应头里面加上了Content-Disposition: attachment; filename="xxxx" 告知浏览器需要下载。我用apifox测试，中文文件名乱码。抽空我再解决这个问题。
- 而sendFile会在浏览器显示文件，它主要是在Content-Type根据文件名的扩展名设置响应HTTP标头字段。

## 上传
- nest内建使用express的multer这个中间件，提交文件的格式是multipart/form-data，使用的http方法是post.
- Multer 无法处理非多部分格式（multipart/form-data）的数据
- 使用之前，先安装定义包：$ npm i -D @types/multer
- 官方参考：https://docs.nestjs.com/techniques/file-upload
## 实现的代码
- 下面是实现的具体代码
```typescript
    // 在当前工程目录下面，输入命令：nest g co upload
    // 我们就创建了一个src/upload/upload/controller.ts
    // 这里是文件的源码

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
            'c:\\temp\\测试.zip';
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
            'c:\\temp\\测试.jpg';
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

```

## 相关文章列表
- [nest笔记一:创建工程并配置vscode调试环境](https://zdhsoft.blog.csdn.net/article/details/121258677)
- [nest笔记二:使用log4js替换nest默认日志](https://zdhsoft.blog.csdn.net/article/details/121359315)
- [nest笔记三:使用全局拦截器打印请求日志](https://zdhsoft.blog.csdn.net/article/details/121393584)
- [nest笔记四:文件的上传与下载](https://zdhsoft.blog.csdn.net/article/details/121644432)
