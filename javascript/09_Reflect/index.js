/* eslint-disable no-unused-vars */
const {getLogger} = require('xmcommon');
const log = getLogger(__filename);


function t1() {
    let obj = {};
    log.info(Reflect.__proto__ === Object.prototype); // true
    log.info(obj.__proto__ === Reflect.__proto__); // true

    let str = '111';

    log.info(str.__proto__); // String {"", length: 0, constructor: ƒ, anchor: ƒ, big: ƒ, blink: ƒ, …}
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
    console.log(desc);
    // {get: ƒ, set: undefined, enumerable: true, configurable: true}
    test = { testValue: 2021 };
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    console.log(desc);
    // {value: 2021, writable: true, enumerable: true, configurable: true}

    test = { [Symbol.for('testValue')]: 2021 }
    desc = Object.getOwnPropertyDescriptor(test, Symbol.for('testValue'));
    console.log(desc);
    // {value: 2021, writable: true, enumerable: true, configurable: true}
    test = {};
    Object.defineProperty(test, 'testValue', {
    value: 2021,
    writable: false,
    enumerable: false
    });
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    console.log(desc);
    // {value: 2021, writable: false, enumerable: false, configurable: false}

    test.testValue = 2222;
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    console.log(desc);
    // testValue值没有变化 {value: 2021, writable: false, enumerable: false, configurable: false}

    delete test.testValue;
    desc = Object.getOwnPropertyDescriptor(test, 'testValue');
    console.log(desc);
    // testValue没有被删除 {value: 2021, writable: false, enumerable: false, configurable: false}


    // d is {
//   value: 8675309,
//   writable: false,
//   enumerable: false,
//   configurable: false
// }

}

function t2() {
    log.info('验证：Reflect.defineProperty');
    let n = { property: 99 };
    // try {
    //     Object.defineProperty(n, 'property', 'attributes');
    // } catch (e) {
    //     // 失败
    //     log.info('--------- exception!');
    // }
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

t2();
t3();
// t1();
// log.info('hello world');
