/* eslint-disable no-unused-vars */
const {getLogger} = require('xmcommon');
const log = getLogger(__filename);

class testClass {
    constructor() {
        this.kkk = 999;
    }
    static getMMM(d) {
        return testClass.mmm + d;
    }

    getKKK(s) {
        return this.kkk * s;
    }

    async mm(...args) {
        return 'mm:' + args.join();
    }
}

testClass.mmm = 1999;



function t1() {
    let obj = {};
    log.info(Reflect.__proto__ === Object.prototype); // true
    log.info(obj.__proto__ === Reflect.__proto__); // true

    let str = '111';

    log.info(str.__proto__); // String {"", length: 0, constructor: ƒ, anchor: ƒ, big: ƒ, blink: ƒ, …}
}

class testClass1 {
    constructor() {
        this.name = 'testClass1';
        console.log('----testClass1');
    }
}

class testClass2 {
    constructor() {
        this.name = 'testClass2';
        console.log('----testClass2');
    }
}



function t6() {
    let t = new testClass1();
    console.log(t.name); // 'testClass1'


    let t0 = Reflect.construct(testClass1, []);
    console.log(t0.name); // 'testClass1'
    // 创建一个对象:
    let o = Reflect.construct(testClass1, [], testClass2);
    console.log(o.name); // 'testClass1'
    console.log(o instanceof testClass1); // false
    console.log(o instanceof testClass2); // true
    // 相当于是testClass2构造的时候，实际上执行的是testClass1的构造函数，而不是testClass2的
    // 通过这个方法，可以实现，一个类，可以有多种构造的方式
}

function t5() {
    log.info('验证：Reflect.get');

    let x = {p:1, foo: 'xxxxxx'};
    let y = {foo: 'yyyyy'};
    // let o = new Proxy(x, {
    //     get(t, p, r) {
    //         return r[p] + 'aaaaa';
    //     }
    // });
    let obj = new Proxy(x, {
        get(t, prop, receiver) {
            return t[prop] + receiver[prop] + 'bar'
        }
    })
    log.info('xx:' + Reflect.get(x, 'foo', x));
    log.info('aa:' + Reflect.get(x, 'foo', y));

    log.info('x:' + Reflect.get(obj, 'foo',x));
    log.info('a:' + Reflect.get(obj, 'foo', y));

    Reflect.set(obj, 'foo', 1999);
    log.info(`set(obj, 'foo', 1999) ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    log.info('x1:' + Reflect.get(obj, 'foo',x));
    log.info('a1:' + Reflect.get(obj, 'foo', y));

    Reflect.set(x, 'foo', 'new xxxx');
    log.info(`set(x, 'foo', 'new xxxx') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    log.info('x2:' + Reflect.get(obj, 'foo',x));
    log.info('a2:' + Reflect.get(obj, 'foo', y));

    Reflect.set(y, 'foo', 'new yyyy');
    log.info(`set(y, 'foo', 'new yyyy') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    log.info('x3:' + Reflect.get(obj, 'foo',x));
    log.info('a3:' + Reflect.get(obj, 'foo', y));

    // 增加了reciver后，发现实际设置的是在y上面...
    Reflect.set(obj, 'foo', 1999, y);
    log.info(`set(obj, 'foo', 1999, y) ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);

    log.info('x4:' + Reflect.get(obj, 'foo',x));
    log.info('a4:' + Reflect.get(obj, 'foo', y));
    Reflect.set(x, 'foo', 'new xxxx', y);
    log.info(`set(x, 'foo', 'new xxxx, y') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);

    log.info('x4:' + Reflect.get(obj, 'foo',x));
    log.info('a4:' + Reflect.get(obj, 'foo', y));
    Reflect.set(y, 'foo', 'new yyyy', y);
    log.info(`set(y, 'foo', 'new yyyy, y') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);

    log.info('x4:' + Reflect.get(obj, 'foo',x));
    log.info('a4:' + Reflect.get(obj, 'foo', y));

// // Object
// let obj = { x: 1, y: 2 }
// Reflect.get(obj, 'x')  // 1

// // Array
// Reflect.get(['zero', 'one'], 1)  // "one"

// // Proxy with a get handler
// let x = {p: 1};

// let obj = new Proxy(x, {
//   get(t, k, r) {
//     return k + 'bar'
//   }
// })
// Reflect.get(obj, 'foo')  // "foobar"

// //Proxy with get handler and receiver
// let x = {p: 1, foo: 2};
// let y = {foo: 3};

// let obj = new Proxy(x, {
//   get(t, prop, receiver) {
//     return receiver[prop] + 'bar'
//   }
// })
// Reflect.get(obj, 'foo', y) // "3bar"
}

async function t4() {
    // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Reflect/apply
    log.info('验证：Reflect.apply');
    log.info(Reflect.apply(testClass['getMMM'], undefined, [123]));

    // expected output: 1

    // log.info(Reflect.apply(String.fromCharCode, undefined, [104, 101, 108, 108, 111]));
    // // expected output: "hello"

    // log.info(Reflect.apply(RegExp.prototype.exec, /ab/, ['confabulation']).index);
    // // expected output: 4

    let j = new testClass();
    log.info(Reflect.apply(j.getKKK,  j, [10]));
    log.info(await Reflect.apply(j.mm,  j, [1,2,3,4,5,6]));

    Reflect.set()
    // expected output: "i"

}

function t3() {
    log.info('验证：Reflect.getOwnPropertyDescriptor');
    let test = {
        get testValue() { return 1024; },
        set testValue(v) {
            //
        }
    };
    let desc = Reflect.getOwnPropertyDescriptor(test, 'testValue');
    log.info(JSON.stringify(desc));
    // {get: ƒ, set: undefined, enumerable: true, configurable: true}
    test = { testValue: 2021 };
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    log.info(JSON.stringify(desc));
    // {value: 2021, writable: true, enumerable: true, configurable: true}

    test = { [Symbol.for('testValue')]: 2021 }
    desc = Object.getOwnPropertyDescriptor(test, Symbol.for('testValue'));
    log.info(JSON.stringify(desc));
    // {value: 2021, writable: true, enumerable: true, configurable: true}
    test = { a:100, k:"aaaaa"};
    Object.defineProperty(test, 'testValue', {
    value: 2021,
    writable: false,
    enumerable: false
    });
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    log.info(JSON.stringify(desc));
    // {value: 2021, writable: false, enumerable: false, configurable: false}

    test.testValue = 2222;
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    log.info(JSON.stringify(desc));
    // testValue值没有变化 {value: 2021, writable: false, enumerable: false, configurable: false}
    log.info('----验证：enumerable的影响, 当enumerable=false');
    for(let k in test) {
        log.info('k1>',k, '===>' ,test[k]);
    }
    log.info("k2>", Object.keys(test));
    log.info("k3>", test.testValue);
    log.info("k4>", Reflect.ownKeys(test));
    log.info('----验证：enumerable的影响, 当enumerable=true');
    delete test.testValue;
    Object.defineProperty(test, 'testValue2', {
        value: 2022,
        writable: true,
        enumerable: true
        });
    for(let k in test) {
        log.info('m1>',k, '===>' ,test[k]);
    }
    log.info("m2>", Object.keys(test));
    log.info("m3>", test.testValue);
    log.info("m4>", Reflect.ownKeys(test));

    delete test.testValue;
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    log.info(JSON.stringify(desc));

}

function t2() {
    log.info('验证：Reflect.defineProperty');
    let n = { property: 99 };
    try {
        // 新写法
        if (Reflect.defineProperty(n, 'property', {value: '中国'})) {
            // success
            log.info('--------- OK', n.property);
        } else {
            // failure
            log.info('--------- false');
        }
    } catch(e) {
        log.error(e);
    }
}
t6();
// t5();
//t2();
//t3();
//t4();
// t1();
// log.info('hello world');
