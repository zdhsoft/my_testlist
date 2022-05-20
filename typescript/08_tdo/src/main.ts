import { getLogger, Queue, Stack } from 'xmcommon';
import { T } from './t';

const log = getLogger(__filename);
// const stack = new Stack<number>();
// const queue = new Queue<number>();

// for (let i = 0; i < 10; i++) {
//     stack.push(i);
//     queue.enqueue(i);
// }

// do {
//     const m = stack.pop();
//     if (m === undefined) {
//         break;
//     }
//     log.log('stack:' + m);
// } while (true);
// do {
//     const m = queue.dequeue();
//     if (m === undefined) {
//         break;
//     }
//     log.log('queue:' + m);
// } while (true);

function trimstring(paramV: string) {
    // return paramV.replace(/^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g, '');
    return paramV.replace(/[\s\uFEFF\xA0]/g, '');
}

const t = ['aaa', ' aaa', 'aaa ', '中!！ 中a a \n\t\r'];
t.forEach((v) => {
    log.info(`[${v}] => a:[${trimstring(v)}] , b:[${v.trim()}] c:{${v}}`);
});

const ttt: any = new T();
const sss = JSON.stringify(ttt);

log.info('--->' + sss);
const m = JSON.parse(sss);
log.info('--->' + typeof m.k + '\n' + JSON.stringify(m));
for (const kkk in m) {
    log.info(`**** ${kkk} => ${m[kkk]} => type ${typeof m[kkk]}`);
}
