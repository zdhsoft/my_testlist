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

### Reflect.get() 取属性值

### Reflect.set() 设置属性值

### Reflect.apply() 应用指定的函数
静态- 方法 Reflect.apply() 通过指定的参数列表发起对目标(target)函数的调用。
```typescript
console.log(Reflect.apply(Math.floor, undefined, [1.75]));
// expected output: 1

console.log(Reflect.apply(String.fromCharCode, undefined, [104, 101, 108, 108, 111]));
// expected output: "hello"

console.log(Reflect.apply(RegExp.prototype.exec, /ab/, ['confabulation']).index);
// expected output: 4

console.log(Reflect.apply(''.charAt, 'ponies', [3]));
// expected output: "i"
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
