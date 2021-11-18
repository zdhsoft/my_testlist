# nest笔记二：使用log4js替换nest默认日志
- 个人比较喜欢log4js，nest自带的日志，时间格式又不是我想要的，所以我这里实现一个替换nest日志的日志
## 基本上要求
- 时间格式为： YYYY-MM-DD hh:mm:ss.ddd
- 可以明确知道输出日志的是哪一个源文件
- 日志文件支持数量配置，大小配置
- 日志文件支持自动压缩
- 有专门的普通的日志文件和错误日志文件以及彩色的控制台输出。
基于上述几点，我这里选择了log4js
## 配置说明
### log4js配置说明
- 具体如下，我这里是放工程的config/log4js.js文件里面，使用js可以支持注释，比较方便
```javascript
// config/log4js.js
/**
 * 这个是log4js文件配置，具体参数log4js官网
 */
module.exports = exports = {
    appenders: {
        log: {
            type       : 'file',             // 如果需要区分日期的，这个值可以改为datefile
            filename   : './logs/log.log',
            maxLogSize : 1024 * 1024 * 50,   // 日志文件的大小，我这里配置的是50M
            encoding   : 'utf-8',
            backups    : 100,
            compress   : true,      // 如果需要压缩，这个值改为true,是的话，这里会得到.gz格式的日志
            keepFileExt: true,      // 是否保持文件扩展名，不是的话，会成.1,.2,.3这样的日志文件
            layout     : {
                type: 'messagePassThrough'  //是直接跳过头部生成，我这里已经有自定义的头部生成, 所以就不需要这个了
            }
        },
        err: {
            type       : 'file',
            filename   : './logs/err.log',
            maxLogSize : 1024 * 1024 * 50,
            encoding   : 'utf-8',
            backups    : 100,
            compress   : true,
            keepFileExt: true,
            layout     : {
                type: 'messagePassThrough'
            }
        },
        console: {
            type: 'stdout',  // 使用标准输出，会比console的性能高
            layout: { type: "messagePassThrough"}
        }
    },
    categories: {
        default: { appenders: ['log'], level: 'ALL' },
        error  : { appenders: ['err'], level: 'ALL' },
        console: { appenders: ['console'], level: 'ALL' }
    }
}
```
### 日志类实现
- 我这里文件名是./src/log/log4js.ts
```typescript

import * as path from 'path';
import * as log4js from 'log4js';
import * as util from 'util';
import {GetLogManager, ILog, datetimeUtils} from 'xmcommon';
// xmcommon是我的一个开源node的代码库，欢迎大家使用 npm install xmcommon
// 在我的所有项目中，都使用了这个库, 目前还算比较稳定

/** 普通日志文件输出 */
let normalLog : log4js.Logger;
/** 错误日志文件输出 */
let errorLog  : log4js.Logger;
let consoleLog: log4js.Logger;
/** 日志级别枚举 */
export enum EnumLogLevel {
    TRACE = 'TRACE',
    DEBUG = 'DEBUG',
    LOG   = '  LOG',
    INFO  = ' INFO',
    ERROR = 'ERROR',
    WARN  = ' WARN',
}
/** 颜色样式 */
const styles = {
    // styles
    bold: [1, 22],
    italic: [3, 23],
    underline: [4, 24],
    inverse: [7, 27],
    // grayscale
    white: [37, 39],
    grey: [90, 39],
    black: [90, 39],
    // colors
    blue: [34, 39],
    cyan: [36, 39],
    green: [32, 39],
    magenta: [35, 39],
    red: [91, 39],
    yellow: [33, 39]
};

/**
 * 给日志的head上色
 * @param msg 日志消息
 * @param paramColorStyle 日志颜色
 * @return 上色后的日志
 */
function colored(msg: {head: string, info: string}, paramColorStyle?: number[]): string {
    if(paramColorStyle) {
        return `\x1B[${paramColorStyle[0]}m${msg.head}\x1B[${paramColorStyle[1]}m ${msg.info}`;
    } else {
        return `${msg.head} ${msg.info}`;
    }
}

/**
 * 生成日志
 * @param categoryName 类名名称
 * @param level 日志级别
 * @param data 日志参数内容
 * @return
 */
function buildLog(categoryName: string, level: string, ...data: any[]) {
    return {head:`[${datetimeUtils.nowDateString()} ${level}][${categoryName}]`, info: util.format(...data)};
}



/**
 * 基于Log4js实际日志
 */
class XLogFor4js implements ILog{
    private m_name: string;
    public constructor(paramName: string) {
        this.m_name = paramName;
    }

    public get name() {
        return this.m_name;
    }

    public trace(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.TRACE, ...paramLog)
        normalLog.trace(colored(logInfo));
        consoleLog.trace(colored(logInfo, styles.blue));
    }
    public debug(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.DEBUG, ...paramLog)
        normalLog.debug(colored(logInfo));
        consoleLog.debug(colored(logInfo, styles.cyan));
    }
    public log(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.LOG, ...paramLog)

        normalLog.info(colored(logInfo));
        consoleLog.info(colored(logInfo, styles.magenta));
    }
    public info(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.INFO, ...paramLog)

        normalLog.info(colored(logInfo));
        consoleLog.info(colored(logInfo, styles.green));
    }
    public error(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.ERROR, ...paramLog);
        const logMsg  = colored(logInfo);

        normalLog.error(logMsg);
        errorLog.error(logMsg)

        consoleLog.error(colored(logInfo, styles.red));
    }

    public warn(...paramLog: any[]): void {
        const logInfo = buildLog(this.name, EnumLogLevel.WARN, ...paramLog)
        const logMsg  = colored(logInfo);

        normalLog.warn(logMsg);
        errorLog.warn(logMsg)
        consoleLog.warn(colored(logInfo, styles.yellow));
    }
}
/**
 * 初始化日志
 * @param paramConfigName 配置文件名（js文件）
 */
function InitLog(paramConfigName: string) {
    const cfg = require(paramConfigName);
    log4js.configure(cfg);

    normalLog  = log4js.getLogger('default');
    errorLog   = log4js.getLogger('error');
    consoleLog = log4js.getLogger('console');

    // 这个是绑定xmcommon的getLogger方法
    const LogManager = GetLogManager();
    LogManager.setCreateLog((paramTag:string) => new XLogFor4js(paramTag));
    LogManager.setDefaultLog(new XLogFor4js('default'));

    // 默认控制台输出函数
    const conLog = LogManager.getLogger('console');

    // 绑定控制台的日志函数
    console.log   = conLog.info.bind(conLog);
    console.error = conLog.error.bind(conLog);
    console.debug = conLog.debug.bind(conLog);
    console.warn  = conLog.warn.bind(conLog);
    console.trace = conLog.trace.bind(conLog);
}

/** 生成绝对配置文件路径 */
const configFile = path.join(process.cwd(), 'config', 'log4js.js');
/* 执行初始化 */
InitLog(configFile);
```

## 替换nest的默认日志
- 在nest工程的启动文件src/main.ts，加入这个
- 在创建nest application的地方，指定日志文件
### 替换nest日志的类
- 文件是src/nest.logger.ts
```typescript
import { LoggerService } from '@nestjs/common';
import { getLogger } from 'xmcommon';

const log = getLogger('nest');
export class NestLogger implements LoggerService {
    log(...msg: any[]) {
        log.info(...msg);
    }
    error(...msg:any[]) {
        log.error(...msg);
    }
    warn(...msg:any[]) {
        log.warn(...msg);
    }
    debug(...msg:any[]) {
        log.debug(...msg);
    }
    verbose(...msg:any[]) {
        log.trace(...msg);
    }
}

```
### 在启动地方替换
```typescript
// main.ts
import './log/log4js';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { getLogger } from 'xmcommon';
import { NestLogger } from './nest.logger';
const log = getLogger(__filename);  // 这样构造日志，就可以在输出的地方，打印出对应的文件
log.info('程序开始启动...');
async function bootstrap() {
    const app = await NestFactory.create(AppModule,
    {
        logger: new NestLogger() // 这里指定了新的nest日志
    });
    await app.listen(3000);
    log.info('开始侦听:3000...')
}
bootstrap();
```
- 到这里，就实现了对日志文件的全替换。
## 相关文章列表
- [nest笔记一:创建工程并配置vscode调试环境](https://zdhsoft.blog.csdn.net/article/details/121258677)
- [nest笔记二:使用log4js替换nest默认日志](https://zdhsoft.blog.csdn.net/article/details/121359315)
- [nest笔记三:使用全局拦截器打印请求日志](https://zdhsoft.blog.csdn.net/article/details/121393584)
