import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
@Injectable()
export class LoggerMiddleware implements NestMiddleware {
    async use(req: Request, res: Response, next: NextFunction) {
        next();
    }
}

// 函数式中间件
export async function logger(req: Request, res: Response, next: () => any) {
    log.info('---->>>', req.url);
    await next();
    log.info('----<<<', req.url);
}
