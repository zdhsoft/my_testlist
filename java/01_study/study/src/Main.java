public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
        final double CM_PER_INCH = 2.54;
        double paperWidth = 8.5;
        double peperHeight = 11;
        System.out.println("Paper size in centimeters:" + paperWidth * CM_PER_INCH + " by " + peperHeight * CM_PER_INCH);
    }
}