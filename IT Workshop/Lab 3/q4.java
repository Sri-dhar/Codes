import java.util.Scanner;

public class q4 {

    public static void main(String[] args) {

        int[] arr = takeInput();
        mergeSort(arr);
        System.out.println(findClosestSum(arr));
    }

    public static int[] takeInput() {
        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) arr[i] = sc.nextInt();
        return arr;
    }

    public static void mergeSort(int[] arr) {
        int n = arr.length;
        if (n < 2) return;
        int mid = n / 2;
        int[] left = new int[mid];
        int[] right = new int[n - mid];

        for (int i = 0; i < mid; i++) left[i] = arr[i];
        for (int i = mid; i < n; i++) right[i - mid] = arr[i];

        mergeSort(left);
        mergeSort(right);
        merge(arr, left, right);
    }

    public static void merge(int[] arr, int[] left, int[] right) {
        int n1 = left.length;
        int n2 = right.length;
        int i = 0, j = 0, k = 0;

        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) arr[k++] = left[i++];
            else arr[k++] = right[j++];
        }

        while (i < n1) arr[k++] = left[i++];
        while (j < n2) arr[k++] = right[j++];
    }

    public static int findClosestSum(int[] arr) {
        int l = 0;
        int r = arr.length - 1;
        int closestSum = arr[l] + arr[r];
        int minDiff = Math.abs(closestSum);

        while (l < r) {
            int sum = arr[l] + arr[r];
            int diff = Math.abs(sum);

            if (diff < minDiff) {
                minDiff = diff;
                closestSum = sum;
            }

            if (sum < 0) l++;
            else r--;
        }
        return closestSum;
    }

}
