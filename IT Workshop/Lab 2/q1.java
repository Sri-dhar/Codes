import java.util.Scanner;

public class q1 {
    public static void main(String[] args) {
        System.out.print("Enter the elements of array : ");
        Scanner scn = new Scanner(System.in);
        int[] arr = new int[5];
        int sum = 0;
        for(int i=0 ;i<5 ; i++)
        {
            arr[i] = scn.nextInt();
            sum += arr[i];
        }
        System.out.println("The sum of the elements of array is : "+sum);
    }
}

