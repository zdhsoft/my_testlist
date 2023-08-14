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