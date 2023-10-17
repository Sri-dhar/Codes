import java.util.Scanner;

public class q4_2 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        System.out.println("We are dividing a by b");

        System.out.println("Enter the value of a: ");
        int a = scn.nextInt();
        System.out.println("Enter the value of b: ");
        int b = scn.nextInt();

        b = (b == 0) ? reAskForB(scn) : b;

        String result = (a % b == 0) ? (a + " is divisible by " + b) : (a + " is not divisible by " + b);
        System.out.println(result);
    }

    static int reAskForB(Scanner scn) {
        System.out.println("The value of b is zero");
        System.out.println("Re-enter the value of b");
        int newB = scn.nextInt();
        return (newB == 0) ? reAskForB(scn) : newB;
    }
}
