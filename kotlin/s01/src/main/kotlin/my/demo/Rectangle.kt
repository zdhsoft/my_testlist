package my.demo

open class Shape {
    var name = "shape"
}

class Rectangle(var height: Double, var length: Double) : Shape() {
    var perimeter = (height + length) * 2


}
fun testClass() {
    val r = Rectangle(5.00, 2.00)
    val maxValue = if (r.height > r.length) r.height else r.length
    println("矩形的高:${r.height}, 长:${r.length}的周长:${r.perimeter}, name:${r.name}, maxValue=$maxValue")
}

fun testFor() {
    val items = listOf(1,2,3,4,5,6)
    val items1 = listOf("a", "b", "c")
    for (item in items) println("---> $item")
    for (item in items1) println("===>$item")

    for(idx in items.indices) {
        val item = items[idx]
        println("item[$idx]=$item")

        val k = when(idx) {
            1 -> "111"
            2 -> "222"
            3 -> "unknow"
            else -> "aaaaaaa"
        }

        println("---->idx=$idx => $k")
    }
}