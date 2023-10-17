import java.util.Scanner;

public class account {
    private static int accountCount;
    public static int getTotalAccountCount() {
        return accountCount;
    }

    public int accountNumber;
    public String accountType;
    public String branchIFSC;
    public float minBal, avlBal;
    public int customerId;
    public String customerName;

    public void setDetails() {
        Scanner scn = new Scanner(System.in);

        System.out.print("Enter Account Number: ");
        this.accountNumber = scn.nextInt();
        scn.nextLine();

        System.out.print("Enter Account Type: ");
        this.accountType = scn.nextLine();

        System.out.print("Enter Branch IFSC: ");
        this.branchIFSC = scn.nextLine();

        System.out.print("Enter Minimum Balance: ");
        this.minBal = scn.nextFloat();

        System.out.print("Enter Available Balance: ");
        this.avlBal = scn.nextFloat();
        scn.nextLine();

        System.out.print("Enter Customer ID: ");
        this.customerId = scn.nextInt();
        scn.nextLine();

        System.out.print("Enter Customer Name: ");
        this.customerName = scn.nextLine();

        accountCount++;
    }

    public void getDetails(int accountNumber) {
        if (this.accountNumber == accountNumber) {
            System.out.println("Account Number: " + this.accountNumber);
            System.out.println("Account Type: " + this.accountType);
            System.out.println("Branch IFSC: " + this.branchIFSC);
            System.out.println("Minimum Balance: " + this.minBal);
            System.out.println("Available Balance: " + this.avlBal);
            System.out.println("Customer ID: " + this.customerId);
            System.out.println("Customer Name: " + this.customerName);

            if (this.avlBal < this.minBal) {
                System.out.println("Warning: Available balance is less than minimum balance.");
            }
        } else {
            System.out.println("Account not found.");
        }
    }


    public void updateDetails() {
        Scanner scn = new Scanner(System.in);

        System.out.println("Which field would you like to update?");
        System.out.println("1. Account Type");
        System.out.println("2. Branch IFSC");
        System.out.println("3. Minimum Balance");
        System.out.println("4. Available Balance");
        System.out.println("5. Customer Name");
        System.out.println("6. Exit");

        int choice = scn.nextInt();
        scn.nextLine();

        switch (choice) {
            case 1 -> {
                System.out.println("Enter the new Account Type: ");
                this.accountType = scn.nextLine();
            }
            case 2 -> {
                System.out.println("Enter the new Branch IFSC: ");
                this.branchIFSC = scn.nextLine();
            }
            case 3 -> {
                System.out.println("Enter the new Minimum Balance: ");
                this.minBal = scn.nextFloat();
                scn.nextLine();
            }
            case 4 -> {
                System.out.println("Enter the new Available Balance: ");
                this.avlBal = scn.nextFloat();
                scn.nextLine();
            }
            case 5 -> {
                System.out.println("Enter the new Customer Name: ");
                this.customerName = scn.nextLine();
            }
            case 6 -> System.out.println("Invalid Operation.");
            default -> System.out.println("Invalid choice. Please select a valid option.");
        }
    }

    public float getBalance(int accountNumberToGet) {
        if (this.accountNumber == accountNumberToGet) {
            return this.avlBal;
        } else {
            System.out.println("Account not found.");
            return -1;
        }
    }

    public void deposit(int accountNumberToDeposit, float amount) {
        if (this.accountNumber == accountNumberToDeposit) {
            if (amount > 0) {
                this.avlBal += amount;
                System.out.println("Deposit of Rs. " + amount + " done.");
            } else {
                System.out.println("Invalid deposit amount. Please Re-enter");
            }
        } else {
            System.out.println("Account not found.");
        }
    }

    public void withdraw(int accountNumberToWithdraw, float amount) {
        if (this.accountNumber == accountNumberToWithdraw) {
            if (amount > 0 && amount <= this.avlBal) {
                this.avlBal -= amount;
                System.out.println("Withdrawal of Rs. " + amount + " successful.");
            } else if (amount <= 0) {
                System.out.println("Invalid withdrawal amount. Please enter a positive amount.");
            } else {
                System.out.println("Insufficient balance for withdrawal.");
            }
        } else {
            System.out.println("Account not found.");
        }
    }


}
