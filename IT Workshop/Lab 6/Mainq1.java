import java.util.ArrayList;
import java.util.Scanner;

public class Mainq1 {

    public static void main(String[] args) {
        ArrayList<Integer> arr = new ArrayList<>();
        Scanner scn = new Scanner(System.in);

        while (true) {
            System.out.println("Current ArrayList: " + arr);

            System.out.println("\nEnter an option:");
            System.out.println("1. Add an integer to the ArrayList");
            System.out.println("2. Remove an integer from the ArrayList");
            System.out.println("3. Search for an integer in the ArrayList");
            System.out.println("4. Replace all occurrences of an integer in the ArrayList");
            System.out.println("5. Exit");
            int c = scn.nextInt();
            int temp = 0;
            switch (c) {
                case 1:
                    System.out.println("Enter an integer to add:");
                    temp = scn.nextInt();
                    arr.add(temp);
                    break;

                case 2:
                    System.out.println("Enter the index to remove:");
                    temp = scn.nextInt();
                    if (temp >= 0 && temp < arr.size()) {
                        int removedNumber = arr.remove(temp);
                        System.out.println("Removed " + removedNumber + " from the ArrayList.");
                    } else {
                        System.out.println("Invalid index. No element removed.");
                    }
                    break;

                case 3:
                    System.out.println("Enter an integer to search for:");
                    temp = scn.nextInt();
                    int index = arr.indexOf(temp);
                    if (index != -1) {
                        System.out.println(temp + " found at index " + index);
                    } else {
                        System.out.println(temp + " not found");
                    }
                    break;

                case 4:
                    System.out.println("Enter an integer to replace all of its values:");
                    int target = scn.nextInt();
                    System.out.println("Enter the new integer:");
                    int replacement = scn.nextInt();
                    repAllOcc(arr, target, replacement);
                    break;

                case 5:
                    System.out.println("Exiting the program.");
                    scn.close();
                    System.exit(0);

                default:
                    System.out.println("Wrong input. Reenter the input");
            }
        }
    }

    public static void repAllOcc(ArrayList<Integer> arr, int target, int newval) {
        for (int i = 0; i < arr.size(); i++)
        {
            if(arr.get(i) == target) arr.set(i, newval);
        }
    }
}
