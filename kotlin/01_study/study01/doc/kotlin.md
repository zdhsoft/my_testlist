# kotlin学习笔记
## 基本知识
### 变量的定义
- var 变量
- val 不可变量（常量） 类似Java中final修饰的变量
### 函数
- 使用fun开头
- 与typescript看函数定义相似
### 注释
```kotlin
// 这是一个单行注释

/* 这是一个多行的
   块注释。 */
```
### 字符串模板
- $ 表示一个变量名或者变量值
- $varName 表示变量值
- ${varName.fun()} 表示变量的方法返回值:
```kotlin
    // 字符串模板
    var a = 1999;
    val s1 = "a is $a calc=${allsum(9,4,3,2)}";
    println(s1);
```

## 基本数据类型
### 数字
| 类型     | 位宽度    |
|:-------|:-------|
| Double | 	64    |
| Float  | 	32    |
| Long   | 	64    |
| Int    | 	32    |
| Short  | 	16    |
| Byte   | 	8     |
### 类型转换
每种数据类型都有下面的这些方法，可以转化为其它的类型：
- toByte(): Byte
- toShort(): Short
- toInt(): Int
- toLong(): Long
- toFloat(): Float
- toDouble(): Double
- toChar(): Char
### 位操作符
对于Int和Long类型，还有一系列的位操作符可以使用，分别是：
```kotlin
//shl(bits) – 左移位 (Java’s <<)
//shr(bits) – 右移位 (Java’s >>)
//ushr(bits) – 无符号右移位 (Java’s >>>)
//and(bits) – 与
//or(bits) – 或
//xor(bits) – 异或
//inv() – 反向
```
### 字符
和 Java 不一样，Kotlin 中的 Char 不能直接和数字操作，Char 必需是单引号 ' 包含起来的。比如普通字符 '0'，'a'。
```kotlin
fun check(c: Char) {
    if (c == 1) { // 错误：类型不兼容
        // ……
    }
}

```

字符字面值用单引号括起来: '1'。 特殊字符可以用反斜杠转义。 支持这几个转义序列：\t、 \b、\n、\r、\'、\"、\\ 和 \$。 编码其他字符要用 Unicode 转义序列语法：'\uFF00'。

我们可以显式把字符转换为 Int 数字：
```kotlin
    fun decimalDigitValue(c: Char): Int {
        if (c !in '0'..'9')
            throw IllegalArgumentException("Out of range")
        return c.toInt() - '0'.toInt() // 显式转换为数字
    }
```

### 布尔
- 布尔用 Boolean 类型表示，它有两个值：true 和 false。
- 若需要可空引用布尔会被装箱。
#### 内置的布尔运算有：
- || – 短路逻辑或
- && – 短路逻辑与
- ! - 逻辑非
### 数组
- 数组用类 Array 实现，并且还有一个 size 属性及 get 和 set 方法，由于使用 [] 重载了 get 和 set 方法，所以我们可以通过下标很方便的获取或者设置数组对应位置的值。

- 数组的创建两种方式：一种是使用函数arrayOf()；另外一种是使用工厂函数。如下所示，我们分别是两种方式创建了两个数组：
```kotlin

fun main(args: Array<String>) {
//[1,2,3]
val a = arrayOf(1, 2, 3)
//[0,2,4]
val b = Array(3, { i -> (i * 2) })

    //读取数组内容
    println(a[0])    // 输出结果：1
    println(b[1])    // 输出结果：2
}
```
- 如上所述，[] 运算符代表调用成员函数 get() 和 set()。
- 注意: 与 Java 不同的是，Kotlin 中数组是不协变的（invariant）。
- 除了类Array，还有ByteArray, ShortArray, IntArray，用来表示各个类型的数组，省去了装箱操作，因此效率更高，其用法同Array一样：
```kotlin
val x: IntArray = intArrayOf(1, 2, 3)
x[0] = x[1] + x[2]
```

### 字符串
- 和 Java 一样，String 是不可变的。方括号 [] 语法可以很方便的获取字符串中的某个字符，也可以通过 for 循环来遍历：
```kotlin
for (c in str) {
    println(c)
}
```
- Kotlin 支持三个引号 """ 扩起来的字符串，支持多行字符串，比如：
```kotlin
fun main(args: Array<String>) {
    val text = """
    多行字符串
    多行字符串
    """
    println(text)   // 输出有一些前置空格
}
```
- String 可以通过 trimMargin() 方法来删除多余的空白。
```kotlin

fun main(args: Array<String>) {
    val text = """
        |多行字符串
        |菜鸟教程
        |多行字符串
        |Runoob
    """.trimMargin()
    println(text)    // 前置空格删除了
}
```
- 默认 | 用作边界前缀，但你可以选择其他字符并作为参数传入，比如 trimMargin(">")。

### 字符串模板
- 字符串可以包含模板表达式 ，即一些小段代码，会求值并把结果合并到字符串中。 模板表达式以美元符（$）开头，由一个简单的名字构成:
```kotlin
fun main(args: Array<String>) {
    val i = 10
    val s = "i = $i" // 求值结果为 "i = 10"
    println(s)
}
```
- 或者用花括号扩起来的任意表达式:
```kotlin
fun main(args: Array<String>) {
    val s = "runoob"
    val str = "$s.length is ${s.length}" // 求值结果为 "runoob.length is 6"
    println(str)
}
```
- 原生字符串和转义字符串内部都支持模板。 如果你需要在原生字符串中表示字面值 $ 字符（它不支持反斜杠转义），你可以用下列语法：
```kotlin
fun main(args: Array<String>) {
    val price = """
    ${'$'}9.99
    """
    println(price)  // 求值结果为 $9.99
}
```
## 条件控制
### IF 表达式
- 一个 if 语句包含一个布尔表达式和一条或多条语句。
```kotlin
// 传统用法
var max = a
if (a < b) max = b

// 使用 else
var max: Int
if (a > b) {
    max = a
} else {
    max = b
}

// 作为表达式
val max = if (a > b) a else b
```
- 我们也可以把 IF 表达式的结果赋值给一个变量。
```kotlin
val max = if (a > b) {
    print("Choose a")
    a
} else {
    print("Choose b")
    b
}
```
- 这也说明我也不需要像Java那种有一个三元操作符，因为我们可以使用它来简单实现：
```kotlin
val c = if (condition) a else b
实例
fun main(args: Array<String>) {
    var x = 0
    if(x>0){
        println("x 大于 0")
    }else if(x==0){
        println("x 等于 0")
    }else{
        println("x 小于 0")
    }

    var a = 1
    var b = 2
    val c = if (a>=b) a else b
    println("c 的值为 $c")
}
```
输出结果为：
```text
x 等于 0
c 的值为 2
```
### 使用区间
- 使用 in 运算符来检测某个数字是否在指定区间内，区间格式为 x..y ：
- 实例
```kotlin
fun main(args: Array<String>) {
    val x = 5
    val y = 9
    if (x in 1..8) {
        println("x 在区间内")
    }
}
```
- 输出结果为：
```text
x 在区间内
```
### When 表达式
- when 将它的参数和所有的分支条件顺序比较，直到某个分支满足条件。
- when 既可以被当做表达式使用也可以被当做语句使用。如果它被当做表达式，符合条件的分支的值就是整个表达式的值，如果当做语句使用， 则忽略个别分支的值。
- when 类似其他语言的 switch 操作符。其最简单的形式如下：
```kotlin
when (x) {
    1 -> print("x == 1")
    2 -> print("x == 2")
    else -> { // 注意这个块
        print("x 不是 1 ，也不是 2")
    }
}
```
- 在 when 中，else 同 switch 的 default。如果其他分支都不满足条件将会求值 else 分支。
- 如果很多分支需要用相同的方式处理，则可以把多个分支条件放在一起，用逗号分隔：
```kotlin
when (x) {
    0, 1 -> print("x == 0 or x == 1")
    else -> print("otherwise")
}
```
- 我们也可以检测一个值在（in）或者不在（!in）一个区间或者集合中：
```kotlin
when (x) {
    in 1..10 -> print("x is in the range")
    in validNumbers -> print("x is valid")
    !in 10..20 -> print("x is outside the range")
    else -> print("none of the above")
}
```
- 另一种可能性是检测一个值是（is）或者不是（!is）一个特定类型的值。注意： 由于智能转换，你可以访问该类型的方法和属性而无需 任何额外的检测。
```kotlin
fun hasPrefix(x: Any) = when(x) {
    is String -> x.startsWith("prefix")
    else -> false
}
```
- when 也可以用来取代 if-else if链。 如果不提供参数，所有的分支条件都是简单的布尔表达式，而当一个分支的条件为真时则执行该分支：
```kotlin
when {
x.isOdd() -> print("x is odd")
x.isEven() -> print("x is even")
else -> print("x is funny")
}
// 实例
fun main(args: Array<String>) {
var x = 0
when (x) {
0, 1 -> println("x == 0 or x == 1")
else -> println("otherwise")
}

    when (x) {
        1 -> println("x == 1")
        2 -> println("x == 2")
        else -> { // 注意这个块
            println("x 不是 1 ，也不是 2")
        }
    }

    when (x) {
        in 0..10 -> println("x 在该区间范围内")
        else -> println("x 不在该区间范围内")
    }
}
```
- 输出结果：
```text
x == 0 or x == 1
x 不是 1 ，也不是 2
x 在该区间范围内

```
- when 中使用 in 运算符来判断集合内是否包含某实例：
```kotlin
fun main(args: Array<String>) {
    val items = setOf("apple", "banana", "kiwi")
    when {
        "orange" in items -> println("juicy")
        "apple" in items -> println("apple is fine too")
    }
}
```

输出结果：
```text
apple is fine too
```

## java vs kotlin
### 什么是Kotlin？
- Kotlin是一种可以在 Java 虚拟机 (JVM) 上运行的开源编程语言。该语言可以在许多平台上运行。

- 它是一种将面向对象编程 (OOP) 和函数式编程结合在一个不受限制、自给自足且与众不同的平台中的语言。

### 什么是Java？
- Java 是一种多平台、面向对象、以网络为中心的编程语言。它是最常用的编程语言之一。它也用作计算平台，最早由 Sun Microsystem 于 1995 年发布，后来被 Oracle 公司收购。

### 主要区别：
- Kotlin 结合了面向对象和函数式编程的特性，而 Java 仅限于面向对象编程。
- Kotlin 允许用户创建扩展函数，而 Java 不提供任何扩展函数。
- Kotlin 不提供隐式转换，而 Java 支持隐式转换。
- 另一方面，Kotlin 中没有空变量或对象，空变量或对象是 Java 语言的一部分。
- Kotlin 不支持静态成员，而 Java 使用静态成员。
- 在，原始类型的 Kotlin 变量是对象，而在 Java 中，原始类型的变量不是对象
- Kotlin 支持 Lambda 表达式，而 Java 不支持 Lambda 表达式。
- Kotlin 不需要任何可变数据类型规范，而 Java 需要可变数据类型规范。
- Kotlin 不需要任何可变数据类型规范，但 Java 需要可变数据类型规范。
- Kotlin 程序不需要分号，而 Java 程序需要分号。
- 语言脚本功能允许您直接在 Gradle 构建脚本中使用 Kotlin，而 Java 不提供语言脚本功能。
### Kotlin 的特点
#### 这里是 Kotlin 的重要特性

- Kotlin 使用JVM，它结合了 OOP 和面向函数式编程的特性。
- 提供快速编译
- Kotlin 无需对代码做任何改动即可支持多种扩展功能
- 您可以使用 IDE 或使用命令行界面编写 Kotlin 代码
### Java的特点
- 以下是 Java 的重要特性。

- 编写一次代码，几乎可以在任何计算平台上运行
- 它旨在构建面向对象的应用程序。
- 它是一种允许自动内存管理的多线程语言。
- 以网络为中心促进分布式计算。
### Kotlin 的历史
以下是 Kotlin 历史上的重要里程碑：

- 2016年，Kotlin v1.0上线
- 2017年，谷歌关于Android对Kotlin的一流支持的公告
- 2018 年，Kotlin v1.3 版本发布了异步编程的协程。
- 2019 年，谷歌宣布 Kotlin 作为其 Android 应用程序开发人员的首选编程语言
### JAVA的历史
这里，是 Java 语言历史上的重要里程碑

- 在Java语言最初称为OAK。最初，它是为处理便携式设备和机顶盒而开发的。奥克是一个巨大的失败。
- 1995 年，Sun 将名称更改为“Java”并修改了语言以利用迅速发展的 www（万维网）开发业务。
- 2009 年晚些时候，甲骨文公司收购了 Sun Microsystems 并获得了三个主要 Sun 软件资产的所有权：Java、MySQL和 Solaris。
