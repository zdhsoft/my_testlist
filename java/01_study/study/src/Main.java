public class Main {
    public static final double CM_PER_INCH = 2.54;
    public static void main(String[] args) {
        System.out.println("Hello world!");
        // final double CM_PER_INCH = 2.54;
        double paperWidth = 8.5;
        double peperHeight = 11;
        System.out.println("Paper size in centimeters:" + paperWidth * CM_PER_INCH + " by " + peperHeight * CM_PER_INCH);

        double x = 4;
        double y = Math.sqrt(x);
        double z = Math.pow(x, 2);
        System.out.println("" + y + "," + z);

        int n = 123456789;
        float f = n;
        double d = n;
        int n1 = (int)f;
        int n2 = (int)d;
        System.out.println("" + n + " => " + f + " => " + d);
        System.out.println("" + n1 + ", " + n2 +" float存在精度丢失!");

        Main t = new Main();
        t.test();
    }

    private void test() {
        String a = "Expletive";
        String b = "deleted";
        String c = "message";
        String m = a + b + c;
        System.out.println(m);

        int age = 10;
        String mm = "you age is " +age;
        System.out.println(mm);
    }
}