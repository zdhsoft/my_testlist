# js笔记十四：Javascript的笔记Reflect
[TOC]
##  Reflect说明

- 从ES6开始，增加了Reflect
- Reflect顾名思意，反射的意思。通过它可以取到对象所有的属性、方法等内全容。
- Reflect 同Math一样，是一个内置的对象，它提供拦截 JavaScript 操作的方法。Reflect不是一个函数对象，因此它是不可构造的。Reflect对象是一个全局的普通的对象。Reflect的原型就是Object.。也就是Reflect是Object的简化版
### Reflect共有13个静态方法
```typescript
	1：Reflect.get(target, name, receiver)
	2：Reflect.set(target,name,value,receiver)
	3：Reflect.apply(target,thisArg,args) ==>OK
	4：Reflect.construct(target,args[, newTarget])
	5：Reflect.defineProperty(target,name,desc) ==>OK
	6：Reflect.deleteProperty(target,name)
	7：Reflect.has(target,name)
	8：Reflect.ownKeys(target)
	9：Reflect.preventExtensions(target)
	10：Reflect.isExtensible(target)
	11：Reflect.getOwnPropertyDescriptor(target, name) ==>OK
	12：Reflect.getPrototypeOf(target)
	13：Reflect.setPrototypeOf(target, prototype)
```

### PropertyDescriptor 属性描述信息
```typescript
    interface PropertyDescriptor {
        /** 当定义的属性可以被更改或可以被删除时为true */
        configurable?: boolean;
        /**
         * 是否可枚举的
         * 1、用for in这个循环以及Object.keys是访问不了enumerable = false的属性
         * 2、但是Reflect.ownKeys可以取到
         */
        enumerable?: boolean;
        /** 定义的属性值 */
        value?: any;
        /** 定义的属性值，是否可以更改 true表示可以，false表示不可以 */
        writable?: boolean;
        /** 访问属性的get方法 */
        get?(): any;
        /** 访问属性的set方法 */
        set?(v: any): void;
    }
```

### Reflect.get() 和 Reflect.set()分别是取属性与设置属性的值
这两个方法，比较简单，都是三个参数
- target 包含指定属性的目标
- propertyKey 属性的名称 类型只能是string | number | symbol这三种
- receiver 如果target对象中指定了getter，receiver则为getter调用时的this值。
```typescript
    /**
     * Gets the property of target, equivalent to `target[propertyKey]` when `receiver === target`.
     * @param target Object that contains the property on itself or in its prototype chain.
     * @param propertyKey The property name.
     * @param receiver The reference to use as the `this` value in the getter function,
     *        if `target[propertyKey]` is an accessor property.
     */
    function get(target: object, propertyKey: PropertyKey, receiver?: any): any;
    /**
     * Sets the property of target, equivalent to `target[propertyKey] = value` when `receiver === target`.
     * @param target Object that contains the property on itself or in its prototype chain.
     * @param propertyKey Name of the property.
     * @param receiver The reference to use as the `this` value in the setter function,
     *        if `target[propertyKey]` is an accessor property.
     */
    function set(target: object, propertyKey: PropertyKey, value: any, receiver?: any): boolean;

    let x = {p:1, foo: 'xxxxxx'};
    let y = {foo: 'yyyyy'};
    let obj = new Proxy(x, {
        // 这里提供了get方法，这样Reflect的第三个参数，就可以用了
        get(t, p, r) {
            return t[p] + r[p] + 'bar'
        }
    })

    console.log('xx:' + Reflect.get(x, 'foo', x));
    // 输出：xx:xxxxxx
    console.log('aa:' + Reflect.get(x, 'foo', y));
    // 输出：aa:xxxxxx
    // 执行到这里，大家会发现，第三个参数，没有发生做用
    // 下面的第三个参数是Proxy的对象，并供了get方法
    console.log('x:' + Reflect.get(obj, 'foo', x));
    // 输出：x:xxxxxxxxxxxxbar
    console.log('a:' + Reflect.get(obj, 'foo', y));
    // 输出：a:xxxxxxyyyyybar
    // 执行到这里，生效了。但是如果没有传入第三个参数，会出错
    Reflect.get(obj, 'foo')
    // 由于没有传入第三个参数，这里会报调用堆栈溢出...  因为默认Proxy中的get方法，是new Proxy()后对像，r[]会循环调用get方法，结果就调用堆栈溢出了。
    // Uncaught RangeError: Maximum call stack size exceeded

    // 下面是Reflect.set
    Reflect.set(obj, 'foo', 1999);
    console.log(`set(obj, 'foo', 1999) ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x1:' + Reflect.get(obj, 'foo',x));
    console.log('a1:' + Reflect.get(obj, 'foo', y));
    // 下面是输出结果
    // set(obj, 'foo', 1999) ==>x:{"p":1,"foo":1999} y:{"foo":"yyyyy"}
    // x1:3998bar
    // a1:1999yyyyybar
    Reflect.set(x, 'foo', 'new xxxx');
    console.log(`set(x, 'foo', 'new xxxx') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x2:' + Reflect.get(obj, 'foo',x));
    console.log('a2:' + Reflect.get(obj, 'foo', y));
    // set(x, 'foo', 'new xxxx') ==>x:{"p":1,"foo":"new xxxx"} y:{"foo":"yyyyy"}
    // x2:new xxxxnew xxxxbar
    // a2:new xxxxyyyyybar
    Reflect.set(y, 'foo', 'new yyyy');
    console.log(`set(y, 'foo', 'new yyyy') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x3:' + Reflect.get(obj, 'foo',x));
    console.log('a3:' + Reflect.get(obj, 'foo', y));
    // set(y, 'foo', 'new yyyy') ==>x:{"p":1,"foo":"new xxxx"} y:{"foo":"new yyyy"}
    // x3:new xxxxnew xxxxbar
    // a3:new xxxxnew yyyybar
    // 增加了reciver后，发现实际设置的是在y上面...
    Reflect.set(obj, 'foo', 1999, y);
    console.log(`set(obj, 'foo', 1999, y) ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x4:' + Reflect.get(obj, 'foo',x));
    console.log('a4:' + Reflect.get(obj, 'foo', y));
    // set(obj, 'foo', 1999, y) ==>x:{"p":1,"foo":"new xxxx"} y:{"foo":1999}
    // x4:new xxxxnew xxxxbar
    // a4:new xxxx1999bar
    Reflect.set(x, 'foo', 'new xxxx', y);
    console.log(`set(x, 'foo', 'new xxxx, y') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x4:' + Reflect.get(obj, 'foo',x));
    console.log('a4:' + Reflect.get(obj, 'foo', y));
    // set(x, 'foo', 'new xxxx, y') ==>x:{"p":1,"foo":"new xxxx"} y:{"foo":"new xxxx"}
    // x4:new xxxxnew xxxxbar
    // a4:new xxxxnew xxxxbar
    Reflect.set(y, 'foo', 'new yyyy', y);
    console.log(`set(y, 'foo', 'new yyyy, y') ==>x:${JSON.stringify(x)} y:${JSON.stringify(y)}`);
    console.log('x4:' + Reflect.get(obj, 'foo',x));
    console.log('a4:' + Reflect.get(obj, 'foo', y));
    // set(y, 'foo', 'new yyyy, y') ==>x:{"p":1,"foo":"new xxxx"} y:{"foo":"new yyyy"}
    // x4:new xxxxnew xxxxbar
    // a4:new xxxxnew yyyybar

```

### Reflect.apply() 应用指定的函数
静态- 方法 Reflect.apply() 通过指定的参数列表发起对目标(target)函数的调用。取支持async和await
```typescript
// 一个用于测试的类
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
console.log(Reflect.apply(testClass['getMMM'], undefined, [123]));// 输出: 2122

console.log(Reflect.apply(j.getKKK,  j, [10]));
// 输出：9990
let j = new testClass();
// 这个要在一个async的函数中才能调用
console.log(await Reflect.apply(j.mm,  j, [1,2,3,4,5,6]));
// 办出: mm:1,2,3,4,5,6

console.log(Reflect.apply(''.charAt, 'ponies', [3]));
// expected output: "i"
```


### Reflect.construct(target,args[, newTarget])
- Reflect.construct() 方法的行为相当于new 操作符 构造函数 ， 相当于运行 new target(...args).
- 这个和Object.create类似
```typescript
    /**
     * Constructs the target with the elements of specified array as the arguments
     * and the specified constructor as the `new.target` value.
     * @param target The constructor to invoke.
     * @param argumentsList An array of argument values to be passed to the constructor.
     * @param newTarget The constructor to be used as the `new.target` object.
     */
    function construct(target: Function, argumentsList: ArrayLike<any>, newTarget?: Function): any;


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

    // 普通使用例子

    let t = new testClass1();
    console.log(t.name); // 'testClass1'
    let t0 = Reflect.construct(testClass1, []);
    console.log(t0.name); // 'testClass1'
    // new与Reflect.construct的执行效果完成一样

    let o = Reflect.construct(testClass1, [], testClass2);
    console.log(o.name); // 'testClass1'
    console.log(o instanceof testClass1); // false
    console.log(o instanceof testClass2); // true
    // 相当于是testClass2构造的时候，实际上执行的是testClass1的构造函数，而不是testClass2的
    // 通过这个方法，可以实现，一个类，可以有多种构造的方式



```
### Reflect.defineProperty 给对像定义一个属性
- 静态方法 Reflect.defineProperty() 基本等同于 Object.defineProperty() 方法，唯一不同是返回 Boolean 值。
- Reflect.defineProperty 方法允许精确添加或修改对象上的属性。
- Object.defineProperty 方法，如果成功则返回一个对象，否则抛出一个 TypeError 。另外，当定义一个属性时，你也可以使用 try...catch 去捕获其中任何的错误。而因为 Reflect.defineProperty 返回 Boolean 值作为成功的标识，所以只能使用 if...else ：

```typescript
   /**
     * Adds a property to an object, or modifies attributes of an existing property.
     * @param target Object on which to add or modify the property. This can be a native JavaScript object
     *        (that is, a user-defined object or a built in object) or a DOM object.
     * @param propertyKey The property name.
     * @param attributes Descriptor for the property. It can be for a data property or an accessor property.
     */
    function defineProperty(target: object, propertyKey: PropertyKey, attributes: PropertyDescriptor): boolean;


```
  - target
	目标对象。

  - propertyKey
	要定义或修改的属性的名称
  - attributes
	要定义或修改的属性的描述。

  - 返回值 boolean
	指示了属性是否被成功定义。

  - 异常
	如果target不是 Object，抛出一个 TypeError。
#### 示例
```javascript
	let obj = {}
	Reflect.defineProperty(obj, 'a', {value: '中国'})  // true
	obj.x						   // 中国
```

### Reflect.getOwnPropertyDescriptor(): PropertyDescriptor  取拥有属性的描述信息
```javascript
    let test = {
        get testValue() { return 2021; },
        set testValue(v) {
            //
        }
    };
    let desc = Reflect.getOwnPropertyDescriptor(test, 'testValue');
    console.log(desc);
    // {get: ƒ, set: ƒ, enumerable: true, configurable: true}
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
