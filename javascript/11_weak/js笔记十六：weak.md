# weak相关的对象
[TOC]

## WeakMap

### Why WeakMap?
- [Why WeakMap](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/WeakMap)
在 JavaScript 里，map API 可以通过使其四个 API 方法共用两个数组(一个存放键,一个存放值)来实现。给这种 map 设置值时会同时将键和值添加到这两个数组的末尾。从而使得键和值的索引在两个数组中相对应。当从该 map 取值的时候，需要遍历所有的键，然后使用索引从存储值的数组中检索出相应的值。

但这样的实现会有两个很大的缺点，首先赋值和搜索操作都是 O(n) 的时间复杂度( n 是键值对的个数)，因为这两个操作都需要遍历全部整个数组来进行匹配。另外一个缺点是可能会导致内存泄漏，因为数组会一直引用着每个键和值。这种引用使得垃圾回收算法不能回收处理他们，即使没有其他任何引用存在了。

相比之下，原生的 WeakMap 持有的是每个键对象的“弱引用”，这意味着在没有其他引用存在时垃圾回收能正确进行。原生 WeakMap 的结构是特殊且有效的，其用于映射的 key 只有在其没有被回收时才是有效的。

正由于这样的弱引用，WeakMap 的 key 是不可枚举的 (没有方法能给出所有的 key)。如果key 是可枚举的话，其列表将会受垃圾回收机制的影响，从而得到不确定的结果。因此，如果你想要这种类型对象的 key 值的列表，你应该使用 Map。

基本上，如果你要往对象上添加数据，又不想干扰垃圾回收机制，就可以使用 WeakMap。


### 使用理解
- 看了一下很多示例，总的感觉是，这个Weak系列的对象是给前端用的。首先这里的key要求是对象，不能是基础数据类型：number, string等。其次不能遍历。后端用到的可能性应该要少一点吧。

```javascript
const {getLogger, utils} = require('xmcommon');
const log = getLogger(__filename);

// log.info('hello');
let m = new WeakMap();

log.info(process.argv);

function testWeakMap() {
    memoryInfo("****11>>>");
    global.gc();
    memoryInfo("****12>>>");
    let k = new Array(5 * 1024 * 1024);
    memoryInfo("****13>>>");
    m.set(k, '1999');
    memoryInfo("****15>>>");
    k = null;
    memoryInfo("****17>>>");
    global.gc();
    memoryInfo("****18>>>");
    // 在这里断点，会发现，m在key已经不存在了。里面，已经没有了任何元素了。相当于执行了WeakMap的delete方法。
    // 如果我在vscode里面断点调试，在global.gc之前，查看了m的内容，会现了key值会被引用，内存使用翻倍。
    // 所以大家使用的时候，要注意思。
}

function memoryInfo(paramPrompt) {
    log.info(`${paramPrompt}:${utils.formatMemory(process.memoryUsage().heapUsed)}`);
}

memoryInfo("0>>>");
log.info('length0:' + m.length);
memoryInfo("1>>>");
testWeakMap();
memoryInfo("2>>>");
log.info('length1:' + m.length);
memoryInfo("3>>>");

```

## WeakSet
- [引用](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/WeakSet)，这里的文档，举例说明一个应用，就是检查循环引用。
- 由于WeakSet在使用过程中，并不会增加对象的引用，所以用它来检查对象的引用，确定很方便。

```javascript
// 这里是原引用文档的代码
// 对 传入的subject对象 内部存储的所有内容执行回调
function execRecursively(fn, subject, _refs = null){
	if(!_refs)
		_refs = new WeakSet();

	// 避免无限递归
	if(_refs.has(subject))
		return;

	fn(subject);
	if("object" === typeof subject){
		_refs.add(subject);
		for(let key in subject)
			execRecursively(fn, subject[key], _refs);
	}
}

const foo = {
	foo: "Foo",
	bar: {
		bar: "Bar"
	}
};

foo.bar.baz = foo; // 循环引用!
execRecursively(obj => console.log(obj), foo);

```
## WeakRef
- [引用](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/WeakRef)
WeakRef对象包含对对象的弱引用，这个弱引用被称为该WeakRef对象的target或者是referent。对对象的弱引用是指当该对象应该被GC回收时不会阻止GC的回收行为。而与此相反的，一个普通的引用（默认是强引用）会将与之对应的对象保存在内存中。只有当该对象没有任何的强引用时，JavaScript引擎GC才会销毁该对象并且回收该对象所占的内存空间。如果上述情况发生了，那么你就无法通过任何的弱引用来获取该对象。
- 根据这个特性，我们可以跟进某个对象或数据，是否被回收，可以用于特定的情况，检查内存是否有内存泄露。

```javascript
// 原文中的示例
class Counter {
  constructor(element) {
    // Remember a weak reference to the DOM element
    this.ref = new WeakRef(element);
    this.start();
  }

  start() {
    if (this.timer) {
      return;
    }

    this.count = 0;

    const tick = () => {
      // Get the element from the weak reference, if it still exists
      const element = this.ref.deref();
      if (element) {
        element.textContent = ++this.count;
      } else {
        // The element doesn't exist anymore
        console.log("The element is gone.");
        this.stop();
        this.ref = null;
      }
    };

    tick();
    this.timer = setInterval(tick, 1000);
  }

  stop() {
    if (this.timer) {
      clearInterval(this.timer);
      this.timer = 0;
    }
  }
}

const counter = new Counter(document.getElementById("counter"));
counter.start();
setTimeout(() => {
  document.getElementById("counter").remove();
}, 5000);
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
