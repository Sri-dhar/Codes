import java.util.Scanner;

public class q3 {
    public static void main(String[] args) {
        int[] arr = takeInput();
        int smallestElement = findSmallest(arr);
        System.out.println("The smallest element of the array is : "+smallestElement);
    }

    public static int[] takeInput()
    {
        System.out.println("Enter the size of the array : ");
        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        int[] arr = new int[n];
        for(int i=0; i<n ; i++) arr[i] = scn.nextInt();
        scn.close();
        return arr;
    }

    public static int findSmallest(int[] arr)
    {
        int mini = Integer.MAX_VALUE;
        for(int i=0; i<arr.length; i++)
        {
            if(arr[i]<mini) mini = arr[i];
        }
        return mini;
    }
}
