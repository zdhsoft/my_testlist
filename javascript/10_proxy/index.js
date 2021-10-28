//npm install xmcommon
const {getLogger} = require('xmcommon');
const log = getLogger(__filename);

let handle  = {
    // 捕捉 defineProperty
    defineProperty: (target, p, attributes) =>{
        log.info('defineProperty ----', p, attributes);
        target[p] = attributes.value;
    },
    // 捕捉 deleteProperty
    deleteProperty: (target, p) => {
        log.info('deleteProperty ==>', p);
        delete target[p];
    },
    // 捕捉 in 方法
    has: (target, p)=> {
        log.info('has ---->>>', p );
        return p in target;
    }
}
// 测试的对方
let m = {};

let v = new Proxy(m, handle);
// 定义属输性

v.aaa = 1999;
// 输出：defineProperty ---- aaa { value: 1999, writable: true, enumerable: true, configurable: true }

v.bbb = 'aaaa';
// 输出：defineProperty ---- bbb { value: 'aaaa', writable: true, enumerable: true, configurable: true }

Reflect.defineProperty(v, 'kkkk', {value: 'kkkkkkkkkkkkkkkkkk'});
// 输出：defineProperty ---- kkkk { value: 'kkkkkkkkkkkkkkkkkk' }

if ('aaa' in v) {
    // 输出：has ---->>> aaa
    log.info('nice!!!');
    // 输出: nice!!!
}
log.info('======>1', JSON.stringify(v));
// 输出: ======>1 {"aaa":1999,"bbb":"aaaa","kkkk":"kkkkkkkkkkkkkkkkkk"}
delete v.bbb;
// 输出: deleteProperty ==> bbb
log.info('======>2', JSON.stringify(v));
// 输出: ======>2 {"aaa":1999,"kkkk":"kkkkkkkkkkkkkkkkkk"}
Reflect.deleteProperty(v, 'aaa');
// 输出: deleteProperty ==> aaa
log.info('======>3', JSON.stringify(v));
// 输出: ======>3 {"kkkk":"kkkkkkkkkkkkkkkkkk"}
