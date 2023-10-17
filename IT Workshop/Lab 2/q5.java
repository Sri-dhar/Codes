import java.util.Scanner;

public class q5 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        System.out.println("Enter the size of the array : ");
        int n = scn.nextInt();
        int[] arr = new int[n];

        takeInput(arr,n);
        reverse(arr,n);
        printArray(arr,n);

    }
    static void reverse(int[] arr ,int n)
    {
        for(int i = 0; i < n/2; i++) {
            int temp = arr[i];
            arr[i] = arr[n-1-i];
            arr[n-1-i] = temp;
        }
    }

    static void takeInput(int[] arr , int n)
    {
        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the elements of the array : ");
        for(int i=0; i<n ; i++) arr[i] = scn.nextInt();
    }

    static void printArray(int[] arr, int n)
    {
        System.out.println("The elements of the array in reversed order are : ");
        for(int i=0;  i<n ; i++)
        {
            System.out.print(arr[i]+" ");
        }
    }
}
