public class addNo {
    public static void main(String[] args) {
        int sum = 0;
        if (args.length == 0) {
            System.out.println("Enter numbers");
        } else if (!args[0].equals("add")) {
            System.out.println("Enter 'add' to add the numbers");
        } else if (args.length == 1) {
            System.out.println("Enter at least 2 numbers");
        } else if (args.length == 2) {
            System.out.println("Enter the other number");
        }else {
            for (int i = 1; i < args.length; i++) {
                sum += Integer.parseInt(args[i]);
            }
            System.out.println("Result: " + sum);
        }
    }
}
