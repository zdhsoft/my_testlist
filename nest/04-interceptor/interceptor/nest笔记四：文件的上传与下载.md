# nestjs系列笔记 
[nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)

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

### 文件上传 nest有四种模式
- 文件上传虽然有多种模式，但是提交的文件要求是一个字段对一个文件，否则不能识别
如下图：虽然file字段对应多个文件，上传后这个字段不能被识别

#### 单个字段单一文件上传
- 例如form-data里面的 file字段上传了一个文件
```typescript
    @Post('up')
    @HttpCode(HttpStatus.OK)
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
```
#### 单个字段多文件上传
- 例如form-data里面的，有多个file字段，每个字段对应一个文件
- 注意，这个时候 装饰器FileInterceptor => FilesInterceptor， UploadedFile => UploadedFiles 都是复数的形式
```typescript
   @Post('upmult')
    @HttpCode(HttpStatus.OK)
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
```
#### 多个字段，每个字段多文件上传
- 例如form-data里面的，有多个file字段和多个pic字段，每个字段对应一个文件
- 注意，这个时候，使用的装饰器又所不同 FilesInterceptor => FileFieldsInterceptor，UploadedFiles还是不变，不过配置类型变了 { file?: Express.Multer.File[]; pic?: Express.Multer.File[] }

```typescript
    @Post('upmultex')
    @HttpCode(HttpStatus.OK)
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
```
#### 任意字段文件上传
- 顾名思义所有的上传的字段，是文件的，都能够取到
- 这个时候装饰器变成了AnyFilesInterceptor
```typescript
   @Post('upany')
    @HttpCode(HttpStatus.OK)
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
```
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
