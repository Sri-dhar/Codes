import java.util.Arrays;
import java.util.Scanner;

public class q2 {

    public static void main(String[] args) {

        int[] arr1 = takeInput(1);
        int[] arr2 = takeInput(2);
        int[] arr3 = takeInput(3);
        Scanner scn = new Scanner(System.in);
        System.out.print("Enter the value of K : " );
        int k = scn.nextInt();

        printCommonK(arr1, arr2, arr3, k);

    }

    public static int[] takeInput(int n) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter size of array " + n + ": ");
        int size = sc.nextInt();
        int[] arr = new int[size];
        System.out.print("Enter elements in sorted order: ");
        for(int i=0; i<size; i++) {
            arr[i] = sc.nextInt();
        }
        return arr;

    }

    public static void printCommonK(int[] a, int[] b, int[] c, int k) 
    {
        int i=0, j=0, l=0;
        int count=0;
        while(i<a.length && j<b.length && l<c.length && count<k) 
        {
            if(a[i]==b[j] && b[j]==c[l]) {
                System.out.print(a[i] + " ");
                i++; j++; l++; count++;
            }
            else if(a[i] < b[j]) i++;
            else if(b[j] < c[l]) j++;
            else l++;
        }
    }

}