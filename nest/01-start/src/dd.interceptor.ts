import {
    CallHandler,
    ExecutionContext,
    Injectable,
    NestInterceptor,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';
import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
@Injectable()
export class DdInterceptor implements NestInterceptor {
    intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
        const start = Date.now(); // 请求开始时间
        const host = context.switchToHttp();
        const request = host.getRequest<Request>();
        const urlInfo = `${request.method} ${request.url}`;
        log.info(`==> ${urlInfo}`);
        return next.handle().pipe(
            tap(() => {
                log.info(`<== ${urlInfo} ${Date.now() - start} ms`);
            }),
        );
    }
}
