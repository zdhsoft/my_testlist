fun main(args: Array<String>) {

    for(a in args) {
        System.out.println(a);
    }

    //System.out.println("hello world");
    var k = testType();
    System.out.println(k.javaClass.name);
    var mm = sum(1,2);
    System.out.println(mm);
    System.out.println(mm.javaClass.name);

    val ssss:(Int, Int) -> Int = { x, y -> x + y};
    val kkkk = { x: Int, y: Int -> x + y};

    System.out.println(ssss(99,100));
    System.out.println(kkkk(1111,9999));


}

fun sum(x: Int, y: Int) = x + y;

fun testType(): Int {
    val s = "我是一个字符串";
    var i = 1314;
    var l = 1413L;
    var f = 12.09f;
    var d = 13.9;
    var d2 = 10.1e6;

    System.out.println(s.javaClass.name)
    System.out.println(i.javaClass.name)
    System.out.println(l.javaClass.name)
    System.out.println(f.javaClass.name)
    System.out.println(d.javaClass.name)
    System.out.println(d2.javaClass.name)

    return i+100;
}