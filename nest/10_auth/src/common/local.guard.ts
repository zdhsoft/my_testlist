import { ExecutionContext, Injectable } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { Observable } from 'rxjs';

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

@Injectable()
export class LocalGuard extends AuthGuard('local') {
    canActivate(context: ExecutionContext): boolean | Promise<boolean> | Observable<boolean> {
        log.info('0000000000000000000000000000000');
        return super.canActivate(context);
        // return true;
    }
}
