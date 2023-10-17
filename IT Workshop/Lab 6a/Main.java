import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        ArrayList<account> accounts = new ArrayList<>();

        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Create a new account");
            System.out.println("2. Update account details");
            System.out.println("3. Deposit funds");
            System.out.println("4. Withdraw funds");
            System.out.println("5. Display all accounts");
            System.out.println("6. Get account balance");
            System.out.println("7. Total number of accounts");
            System.out.println("8. Exit");
            System.out.print("Enter your choice: ");

            int choice = scn.nextInt();
            scn.nextLine();

            switch (choice) {
                case 1 -> {
                    account newAccount = new account();
                    newAccount.setDetails();
                    accounts.add(newAccount);
                }
                case 2 -> {
                    System.out.print("Enter the account number to update: ");
                    int accountNumberToUpdate = scn.nextInt();
                    scn.nextLine();
                    for (account acc : accounts) {
                        if (acc.accountNumber == accountNumberToUpdate) {
                            acc.updateDetails();
                            break;
                        }
                    }
                }
                case 3 -> {
                    System.out.print("Enter the account number to deposit into: ");
                    int accountNumberToDeposit = scn.nextInt();
                    scn.nextLine();
                    System.out.print("Enter the deposit amount: ");
                    float depositAmount = scn.nextFloat();
                    scn.nextLine();
                    for (account acc : accounts) {
                        if (acc.accountNumber == accountNumberToDeposit) {
                            acc.deposit(accountNumberToDeposit, depositAmount);
                            break;
                        }
                    }
                }
                case 4 -> {
                    System.out.print("Enter the account number to withdraw from: ");
                    int accountNumberToWithdraw = scn.nextInt();
                    scn.nextLine();
                    System.out.print("Enter the withdrawal amount: ");
                    float withdrawalAmount = scn.nextFloat();
                    scn.nextLine();
                    for (account acc : accounts) {
                        if (acc.accountNumber == accountNumberToWithdraw) {
                            acc.withdraw(accountNumberToWithdraw, withdrawalAmount);
                            break;
                        }
                    }
                }
                case 5 -> {
                    System.out.println("All Accounts:");
                    for (account acc : accounts) {
                        acc.getDetails(acc.accountNumber);
                        System.out.println();
                    }
                }
                case 6 -> {
                    System.out.print("Enter the account number to get balance: ");
                    int accountNumberToGetBalance = scn.nextInt();
                    scn.nextLine();
                    for (account acc : accounts) {
                        if (acc.accountNumber == accountNumberToGetBalance) {
                            float balance = acc.getBalance(accountNumberToGetBalance);
                            if (balance != -1) {
                                System.out.println("Balance for Account " + accountNumberToGetBalance + ": " + balance);
                            }
                            break;
                        }
                    }
                }
                case 7 -> System.out.println("Total number of accounts: " + account.getTotalAccountCount());
                case 8 -> {
                    System.out.println("Exiting...");
                    scn.close();
                    System.exit(0);
                }
                default -> System.out.println("Invalid choice. Please select a valid option.");
            }
        }
    }
}
