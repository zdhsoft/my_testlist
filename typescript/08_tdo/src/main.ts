/*************************************************************************
 * Copyright(c) 2017-2022,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2022-01-22
 *************************************************************************/

import { getLogger, Queue, Stack } from 'xmcommon';

const log = getLogger(__filename);
const stack = new Stack<number>();
const queue = new Queue<number>();

for (let i = 0; i < 10; i++) {
    stack.push(i);
    queue.enqueue(i);
}

do {
    const m = stack.pop();
    if (m === undefined) {
        break;
    }
    log.log('stack:' + m);
} while (true);
do {
    const m = queue.dequeue();
    if (m === undefined) {
        break;
    }
    log.log('queue:' + m);
} while (true);
