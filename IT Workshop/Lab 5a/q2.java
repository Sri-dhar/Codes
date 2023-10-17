import java.util.Scanner;

public class q2 {
    public static void main(String[] args) {

        int mini = -2147483648;

        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the size of the array: ");
        int n = scn.nextInt();
        int[] arr = new int[n];
        System.out.println("Enter the array elements: ");
        for (int i = 0; i < n; i++)
            arr[i] = scn.nextInt();

        int f = mini, s = mini ,t = mini;

        if (n < 3) t = mini;
        else {
            for (int i = 0; i < n; i++) {
                if (arr[i] > f) {
                    t = s;
                    s = f;
                    f = arr[i];
                } else if (arr[i] > s && arr[i] != f) {
                    t = s;
                    s = arr[i];
                } else if (arr[i] > t && arr[i] != s && arr[i] != f) {
                    t = arr[i];
                }
            }

            System.out.println("The third largest element in the array is: " + t);
        }
    }
}
