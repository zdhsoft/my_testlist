package my.demo

val PI = 3.1415926
var xxx = 0

fun sum(a: Int, b: Int): Int {
    return a + b
}

fun incX() {
    xxx++
}

fun getX():Int {
    return xxx
}

fun testX() {
    for (i in 1..10) {
        println("xxx = " + getX())
        incX()
    }
}

fun sum1(a: Int, b:Int) = a + b


fun printSum() {
    println("sum1:1+2=" + sum1(1,2))
}

fun printSum2(a: Int, b: Int) {
    println("sum of $a and $b is ${a+b}")
}

fun simple() {
    val a = 2
    val b = 2
    val c = 3
    println("a=$a, b=$b, c=$c" + sss(999))
}

fun sss(a: Int) : Int {
    var x = 5
    x += 5
    return a + x
}