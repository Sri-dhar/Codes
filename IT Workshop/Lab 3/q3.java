import java.util.Scanner;

public class q3 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter string: ");
        String str = sc.next();

        System.out.print("Enter character to push to end: ");
        char key = sc.next().charAt(0);

        str = rearrange(str, key);
        System.out.print("Rearranged String: " + str);

    }

    public static String rearrange(String str, char key) {

        char[] arr = str.toCharArray();
        int i = 0;
        for(int j=0; j<arr.length; j++) if(arr[j] != key) arr[i++] = arr[j];
        while(i < arr.length) arr[i++] = key;
        return new String(arr);
    }

}