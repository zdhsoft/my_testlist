# nest笔记三：使用全局拦截器打印请求日志
- 调试的时候，希望能看到每个请求URL和方法以及耗时时间，好像nest默认没有，我暂时没有找到。
- 只好想，自己写一个。第一次是想使用中间件，结果比较尴尬的事情，它处理请求不是使用Promise同步的，不能正确获得请求处理的时间
- 看到官网，说是有一个拦截器，照着实现，果然可以。下面是实现内容。
- 这个就没有新建工程了，是基于[nest笔记二:使用log4js替换nest默认日志](https://zdhsoft.blog.csdn.net/article/details/121359315)的工程
## 插件
- 为了更好的编写nest，建议在家安装下面插件，然后就可以vscode的资源管理员的右键来创建nest相应的代码了

## 拦截器的实现
- 文件名: request.interceptor.ts
- 我这里增加一个计数器requestSeq， 每来一个请求，就是自增1，在打印URL的时候，可以与输入和输出请求，成对打印，这样就好区分请求。
```typescript
/*
https://docs.nestjs.com/interceptors#interceptors
*/
import {
    Injectable,
    NestInterceptor,
    ExecutionContext,
    CallHandler,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
let requestSeq = 0;

@Injectable()
export class RequestInterceptor implements NestInterceptor {
    intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
        const start = Date.now(); // 请求开始时间
        const host = context.switchToHttp();
        const request = host.getRequest<Request>();
        const seq = requestSeq++;
        const urlInfo = `${request.method} ${request.url}`;
        log.info(`[${seq}]==> ${urlInfo}`);
        return next
            .handle()
            .pipe(
                tap(() =>
                    log.info(`[${seq}]<== ${urlInfo} ${Date.now() - start} ms`),
                ),
            );
    }
}

```
## 设置全局的拦截器
- 在main.ts里面，引入这个拦截器, 然后设置为全局的就可以了
```typescript
import './log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './nest.logger';
import { RequestInterceptor } from './request.interceptor';
const log = getLogger(__filename);
log.info('程序开始启动...');
async function bootstrap() {
    const app = await NestFactory.create(AppModule, {
        logger: new NestLogger(),
    });
    app.useGlobalInterceptors(new RequestInterceptor());
    await app.listen(3000);
    log.info('开始侦听:3000...');
}
bootstrap();
```
## 相关文章列表
- [nest笔记一:创建工程并配置vscode调试环境](https://zdhsoft.blog.csdn.net/article/details/121258677)
- [nest笔记二:使用log4js替换nest默认日志](https://zdhsoft.blog.csdn.net/article/details/121359315)
- [nest笔记三:使用全局拦截器打印请求日志](https://zdhsoft.blog.csdn.net/article/details/121393584)
