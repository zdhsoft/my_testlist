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
        System.out.println("" + n + " => " + f + " => " + d);
    }
}