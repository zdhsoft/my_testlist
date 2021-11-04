# js笔记十五：Proxy
[TOC]
##  Proxy说明
- Proxy 对象用于创建一个对象的代理，从而实现基本操作的拦截和自定义（如属性查找、赋值、枚举、函数调用等）。
### 语法
#### Proxy构造函数接口的定义
```typescript
// Proxy构造接口定义
interface ProxyConstructor {
    // 创建可以取消的Proxy对象
    revocable<T extends object>(target: T, handler: ProxyHandler<T>): { proxy: T; revoke: () => void; };
    // 使用new方法创建Proxy对象
    new <T extends object>(target: T, handler: ProxyHandler<T>): T;
}
```
#### ProxyHandler接口的定义
```typescript
// 大家看到接口的定义，就会发现，这些其实都有Reflect中方法类型
// proxy通过再实现这里的方法，达到拦截和自定义的能力
interface ProxyHandler<T extends object> {
    apply?(target: T, thisArg: any, argArray: any[]): any;
    construct?(target: T, argArray: any[], newTarget: Function): object;
    defineProperty?(target: T, p: string | symbol, attributes: PropertyDescriptor): boolean;
    deleteProperty?(target: T, p: string | symbol): boolean;
    get?(target: T, p: string | symbol, receiver: any): any;
    getOwnPropertyDescriptor?(target: T, p: string | symbol): PropertyDescriptor | undefined;
    getPrototypeOf?(target: T): object | null;
    has?(target: T, p: string | symbol): boolean;
    isExtensible?(target: T): boolean;
    ownKeys?(target: T): ArrayLike<string | symbol>;
    preventExtensions?(target: T): boolean;
    set?(target: T, p: string | symbol, value: any, receiver: any): boolean;
    setPrototypeOf?(target: T, v: object | null): boolean;
}
```

### 测试例子
```javascript
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

```
## 历史笔记列表
- [js笔记一:js中forEach，for in，for of循环的用法](https://blog.csdn.net/zdhsoft/article/details/54017183)
- [js笔记二:node.js的npm使用理解](https://blog.csdn.net/zdhsoft/article/details/54171647)
- [js笔记三:Set](https://blog.csdn.net/zdhsoft/article/details/54343212)
- [js笔记四:node 6.9.x for gulp完整配置过程](https://blog.csdn.net/zdhsoft/article/details/54571623)
- [js笔记五:数组基础篇](https://blog.csdn.net/zdhsoft/article/details/60139339)
- [js笔记六:数组功能篇](https://blog.csdn.net/zdhsoft/article/details/60773237)
- [js笔记七:数组的解构与变参](https://blog.csdn.net/zdhsoft/article/details/68067163)
- [js笔记八:class](https://blog.csdn.net/zdhsoft/article/details/75221104)
- [js笔记九:当运行脚本](https://blog.csdn.net/zdhsoft/article/details/78630854)
- [js笔记十:vscode代码提示](https://blog.csdn.net/zdhsoft/article/details/79305847)
- [js笔记十一:js监测变化并动态加载](https://blog.csdn.net/zdhsoft/article/details/79469553)
- [js笔记十二:利用await和async，将回调函数变成同步的处理的办法](https://blog.csdn.net/zdhsoft/article/details/79469622)
- [js笔记十三:nodejs 原生BigInt](https://blog.csdn.net/zdhsoft/article/details/89670901)
- [js笔记十四:Reflect 反射](https://zdhsoft.blog.csdn.net/article/details/121014342)
- [js笔记十五:Proxy 代理](https://zdhsoft.blog.csdn.net/article/details/121014342)
- [js笔记十六:Weak对象](https://zdhsoft.blog.csdn.net/article/details/121144555)
