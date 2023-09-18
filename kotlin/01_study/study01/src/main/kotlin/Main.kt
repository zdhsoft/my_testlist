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

    args.forEach { x: String -> println("hello:$x for macß") }

    listOf(1,2,3,4,5).forEach { x -> println(x) }

    println("value MON :${t(Day.MON)}")
    println("value TUE :${t(Day.TUE)}")
    println("value WEN :${t(Day.WEN)}")
    println("value THU :${t(Day.THU)}")
    println("value FRI :${t(Day.FRI)}")
    println("value SAT :${t(Day.SAT)}")
    println("value SUN :${t(Day.SUN)}")

    for(i: Int in 1..10) {
        println(i*i+1)
    }
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

enum class Day {
    MON,
    TUE,
    WEN,
    THU,
    FRI,
    SAT,
    SUN

}

fun t(d: Day): Int {
    when(d) {
        Day.FRI -> return 5;
        Day.MON -> return 4;
        Day.TUE, Day.WEN -> return 9;
        else -> return 99;
    }
}