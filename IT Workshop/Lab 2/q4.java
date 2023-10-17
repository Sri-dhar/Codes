import java.util.Scanner;

public class q4 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        System.out.println("We are dividing a by b");
        System.out.println("Enter the value of a: ");
        int a = scn.nextInt();
        System.out.println("Enter the value of b: ");
        int b = scn.nextInt();

        if (b == 0) {
            System.out.println("The value of b is zero");
            System.out.println("Re-enter the value of b");
            while (b == 0) {
                b = scn.nextInt();
                if (b == 0) {
                    System.out.println("The value of b is zero");
                    System.out.println("Re-enter the value of b");
                }
            }
        }

        if (a % b == 0) {
            System.out.println(a + " is divisible by " + b);
        } else {
            System.out.println(a + " is not divisible by " + b);
        }
    }
}
