import java.util.Scanner;

public class q2 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the size of the array : ");
        int n = scn.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements of the array : ");
        for (int i = 0; i < n; i++) arr[i] = scn.nextInt();
        int[][] freq = new int[n][2];
        int freqCount = 0;

        for (int i = 0; i < n; i++)
        {
            boolean newNo = true;
            for (int j = 0; j < freqCount; j++)
                if (freq[j][0] == arr[i]) {
                    freq[j][1]++;
                    newNo = false;
                    break;
                }
            if (newNo) {
                freq[freqCount][0] = arr[i];
                freq[freqCount][1]++;
                freqCount++;
            }
        }
        for (int i = 0; i < freqCount; i++) {
            System.out.println("The frequency of " + freq[i][0] + " is " + freq[i][1]);
        }
    }
}
