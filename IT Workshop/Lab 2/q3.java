import java.util.Scanner;

public class q3 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the size of the array : ");
        int n = scn.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements of the array : ");
        for(int i = 0; i < n; i++) arr[i] = scn.nextInt();

        boolean isPalin = true;

        for(int i=0; i<n/2 ;i++) if(arr[i] != arr[n-i-1]) isPalin = false;
        if(isPalin) System.out.println("The array is a Palindrome");
        else System.out.println("The array is not a Palindrome");
    }

}
