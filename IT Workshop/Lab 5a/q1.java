import java.util.Scanner;

public class q1{
    public static void main(String[] args)
    {
        Scanner scn = new Scanner(System.in);
        int[] arr = new int[5];
        System.out.println("Enter the 5 elements of the array: ");
        double sum = 0;
        for(int i=0; i<5; i++) 
        {
            arr[i] = scn.nextInt();
            sum += arr[i];
        }
        System.out.println("The sum of the numbers you entered is : "+sum);
        System.out.println("The average of the numbers you entered is : "+sum/5.0);
    }
}