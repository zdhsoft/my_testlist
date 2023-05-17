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
 * 1.0                 zdhsoft      创建文件            2023-05-17
 *************************************************************************/
import { Observable, debounceTime, distinctUntilChanged, of, switchMap, Subject } from 'rxjs';

const observable = of(1, 2, 3);

const s = new Subject<number>();

function touch(paramV: number) {
    console.log('touch...' + paramV);
    s.next(paramV);
}
const k = s.pipe(
    debounceTime(300),
    distinctUntilChanged(),
    switchMap((term) => {
        console.log('aaaa:' + term);
        return of(term * 10);
    }),
);
let i = 0;
let n = 0;
setInterval(() => {
    const dt = Date.now();
    if (dt > n) {
        touch(i);
        i++;
        n = dt + ((i % 5) + 1) * 100;
    }
}, 200);

setTimeout(() => {
    k.subscribe((_k) => {
        console.log('jjjjj', _k);
    });
}, 4000);

observable.subscribe((message) => {
    console.log('xxxx', message);
});

// k.subscribe((_k) => {
//     console.log('kkkk:', _k);
// });

console.log('hello world!');
