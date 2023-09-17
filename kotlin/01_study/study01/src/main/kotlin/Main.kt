fun main(args: Array<String>) {
    println("size:${args.size} => ")
    for(a in args) {
        println(a);
    }

    //System.out.println("hello world");
    var k = testType();
    println(k.javaClass.name);
    var mm = sum(1,2);
    println(mm);
    println(mm.javaClass.name);

    val ssss:(Int, Int) -> Int = { x, y -> x + y};
    val kkkk = { x: Int, y: Int -> x + y};

    println(ssss(99,100));
    println(kkkk(1111,9999));

    args.forEach { x: String -> println("hello:$x") }

    listOf(1,2,3,4,5).forEach { x -> println(x) }


}

fun sum(x: Int, y: Int) = x + y;

fun testType(): Int {
    val s = "我是一个字符串";
    var i = 1314;
    var l = 1413L;
    var f = 12.09f;
    var d = 13.9;
    var d2 = 10.1e6;

    println(s.javaClass.name)
    println(i.javaClass.name)
    println(l.javaClass.name)
    println(f.javaClass.name)
    println(d.javaClass.name)
    println(d2.javaClass.name)

    return i+100;
}