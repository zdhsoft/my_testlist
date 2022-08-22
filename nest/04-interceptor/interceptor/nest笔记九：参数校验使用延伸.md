# nest笔记九：参数校验使用延伸
- [nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)
- 之前的笔记：[nest笔记七：参数校验](https://zdhsoft.blog.csdn.net/article/details/123576984)对nest的参数校验，做了大体的说明。这里在实践过程做了些更进一步的了解。

## 要求专入参数是DTO已经定义的
- 默认的呢况下，参数校验只针对DTO中已经存在的参数，进行校验。而未在DTO中定义的属性，则会被忽略，不去校验。
- 如果要校验参数，只能是DTO的属性，我们只要增加校验选项就可以了。
### whitelist 白名单
- 如果设置为 true，validator 将删除任何没有任何装饰器的属性的已验证对象。如果没有合适的装饰器，则用@Alloc这个装饰器。
- 示例：DTO的定义
```typescript
    @ApiTags('这是一个sample')
    class DTOSample {
        @IsInt()
        id: number

        @IsString()
        name: string
    }
```
- 传入的参数
```JSON
    这个时候如果传参是
    {
        "id":1,
        "name": "sample name",
        "age": 18
    }
```
- 最终的结果
```javascript
{
    id: 1,
    name: 'sample name'
};
    // age这个属性没有了
```
### forbidNonWhitelisted 禁用非白名单的
- 如果设置为 true，则非白名单属性会被检查出错误。
- 如上例，一个age则返回属age是一个非必要的属错误。
- 一般情况下，我会要求将不必要的参数都检查出来。减少不要的错误

### nest使用校验管道的具体实现
```typescript
// validation_pipe.ts
import { Injectable, PipeTransform, ArgumentMetadata, ValidationError } from '@nestjs/common';
import { plainToClass } from 'class-transformer';
import { validate } from 'class-validator';
import { EnumErrorCode } from '../error/error_code';

/**
 * 这是一个全局的参数验证管道，基于class-transformer
 * 如果失败，则会抛出Error
 * 在main.ts的nestApp要将它设为全局的
 */

@Injectable()
export class ValidationPipe implements PipeTransform {
    async transform(paramValue: any, { metatype: paramMetatype }: ArgumentMetadata) {
        if (!paramMetatype || !this.toValidate(paramMetatype)) {
            return paramValue;
        }
        const object = plainToClass(paramMetatype, paramValue);
        const errors = await validate(object, {
            whitelist: true, // 白名单选项
            forbidNonWhitelisted: true, // 禁用非白名单属性选项
            stopAtFirstError: true, // 碰到第一个错误就返回
            forbidUnknownValues: true, // 禁用未知的值
        });
        const errorList: string[] = [];
        const errObjList: ValidationError[] = [...errors];

        do {
            const e = errObjList.shift();
            if (!e) {
                break;
            }
            if (e.constraints) {
                for (const item in e.constraints) {
                    if (item === 'whitelistValidation') {
                        // 如果是白名单校验错误的，使用自定义的错误语句描述。
                        errorList.push(`属性 ${e.property} 未定义!`);
                    } else {
                        errorList.push(e.constraints[item]);
                    }
                }
            }
            if (e.children) {
                errObjList.push(...e.children);
            }
        } while (true);
        if (errorList.length > 0) {
            throw new Error(`Error:请求参数校验错误: ${errorList.join()}`);
        }
        return object;
    }

    private toValidate(paramMetatype: Function): boolean {
        const types: Function[] = [String, Boolean, Number, Array, Object];
        return !types.includes(paramMetatype);
    }
}

```
### 在启动的时候，设置全局校验管道
```typescript
// 在main.ts中的bootstrap函数中
async function bootstrap() {
    const globalConfig = XConfigUtils.getConfig();

    app.enableCors({
        origin: true,
        methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
        credentials: true,
    });
    app.useGlobalPipes(new ValidationPipe());  // 这里设置全局管道
    await app.listen(globalConfig.port as number);
    log.info(`开始侦听:${globalConfig.port}...`);
}
```
## 对象中的数据校验
- 如果某个属性是某个对象，并且对象中的属性也是需要校验的话，就需要使用装饰器
## 数组中，基本数据类型校验
## 数组中，对象数据校验
