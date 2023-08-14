
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
    // Try adding program arguments via Run/Debug configuration.
    // Learn more about running applications: https://www.jetbrains.com/help/idea/running-applications.html.
    // println("Program arguments: ${args.joinToString()}")
}