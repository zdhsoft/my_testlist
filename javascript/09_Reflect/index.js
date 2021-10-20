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

//t2();
//t3();
t4();
// t1();
// log.info('hello world');
