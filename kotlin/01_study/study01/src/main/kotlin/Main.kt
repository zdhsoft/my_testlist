
fun sum(a: Int, b: Int): Int {   // Int 参数，返回值 Int
    return a + b
}

fun allsum(vararg a:Int): Int {
    var m: Int = 0;
    for(mm in a) {
        m = m + mm;
    }
    return m;
}

fun parseInt(str: String): Int? {
    return str.toIntOrNull()
}

fun printProduct(arg1: String, arg2: String) {
    val x = parseInt(arg1)
    val y = parseInt(arg2)

    // 直接使用 `x * y` 会导致错误, 因为它们可能为 null
    if (x != null && y != null) {
        // 在进行过 null 值检查之后, x 和 y 的类型会被自动转换为非 null 变量
        println(x * y)
    }
    else {
        println("'$arg1' or '$arg2' is not a number")
    }
}

// 这是一个单行注释

/* 这是一个多行的
   块注释。 */
fun main(args: Array<String>) {
    println("Hello World!" + "zdhsoft")
    println("calc: 1 + 2 = " + sum(1,2))
    println("calc: 1 + 2 = " + allsum(1, 2, 3, 4, 5))
    // 字符串模板
    var a = 1999;
    val s1 = "a is $a calc=${allsum(9,4,3,2)}";
    println(s1);

//类型后面加?表示可为空
    var age: String? = "23"
//抛出空指针异常
    val ages = age!!.toInt()
//不做处理返回 null
    val ages1 = age?.toInt()
//age为空返回-1
    val ages2 = age?.toInt() ?: -1

    println("$age,$ages1,$ages2, $ages")
    printProduct("6", "7")
    printProduct("a", "7")
    printProduct("a", "b")
    // Try adding program arguments via Run/Debug configuration.
    // Learn more about running applications: https://www.jetbrains.com/help/idea/running-applications.html.
    // println("Program arguments: ${args.joinToString()}")
}