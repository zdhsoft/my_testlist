/*************************************************************************
 * Copyright(c) 2017-2021, 深圳市链融科技有限公司
 * Shenzhen Lianrong Technology Co., Ltd.
 * All rights reserved.
 *
 * @filename app.service.ts
 * @summary：主模块服务
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-06
 *************************************************************************/
import { Injectable } from '@nestjs/common';

@Injectable()
export class AppService {
    getHello(): string {
        return 'Hello World!';
    }
}
