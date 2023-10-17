import java.util.Scanner;
public class q6 {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        String str = scn.nextLine();
        System.out.println("Enter the sentence : ");
        printLongestWord(str);
        if(isPangram(str)) System.out.println("The sentence is a Pangram");
        else System.out.println("The sentence is not a Pangram");
    }

    static boolean isPangram(String str) {
        str = str.toLowerCase();
        boolean[] present = new boolean[26];
        for (char c : str.toCharArray()) if (Character.isLetter(c)) present[c - 'a'] = true;
        for (boolean p : present) if (!p) return false;
        return true;
    }

    static void printLongestWord(String str) {
        int maxi = 0;
        String[] arr = str.split(" ");
        int maxIdx = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].length() > maxi) {
                maxi = arr[i].length();
                maxIdx = i;
            }
        }
        System.out.println("The longest word is \"" + arr[maxIdx] + "\" with " + maxi + " letters.");
    }

}
