import { NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';
export declare class LoggerMiddleware implements NestMiddleware {
    use(req: Request, res: Response, next: NextFunction): Promise<void>;
}
export declare function logger(req: Request, res: Response, next: () => any): Promise<void>;
