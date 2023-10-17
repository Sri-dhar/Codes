    import java.util.Scanner;

    public class q1 {
        public static void main(String[] args) {
            int[] arr = inputArr(1);
            int[] arr2 = inputArr(2);
            int[] arrFinal = merger(arr, arr2);

            System.out.println("The merged array is :\n ");
            for (int num : arrFinal) System.out.print(num + " ");
        }

        public static int[] inputArr(int a) {
            System.out.println("Enter the size of the array " + a + " :");
            Scanner scn = new Scanner(System.in);
            int n = scn.nextInt();
            int[] arr = new int[n];
            System.out.println("Enter the elements of the array in sorted order :");
            for (int i = 0; i < n; i++) arr[i] = scn.nextInt();
            return arr;
        }

        public static int[] merger(int[] arr, int[] arr2) {
            int n = arr.length;
            int m = arr2.length;
            int[] ans = new int[m + n];
            int ptr = 0, ptr2 = 0, idx = 0;
            while (ptr < n && ptr2 < m)
                if (arr[ptr] < arr2[ptr2]) ans[idx++] = arr[ptr++];
                else ans[idx++] = arr2[ptr2++];
            while (ptr < n) ans[idx++] = arr[ptr++];
            while (ptr2 < m) ans[idx++] = arr2[ptr2++];
            return ans;
        }
    }
