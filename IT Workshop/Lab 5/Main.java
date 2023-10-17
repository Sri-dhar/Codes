import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int choice = 0;
        Scanner scn = new Scanner(System.in);

        while (true) {
            System.out.println("Enter 1 to set details of a Student");
            System.out.println("Enter 2 to get details of a Student");
            System.out.println("Enter 3 to update details of a Student");
            System.out.println("Enter 4 to get GPA of a Student");
            System.out.println("Enter 5 to update GPA of a Student");
            System.out.println("Enter 6 to print all student information");
            System.out.println("Enter 7 to get the total number of students");
            System.out.println("Enter 8 to compare GPAs of two students");
            System.out.println("Enter 9 to exit");

            choice = scn.nextInt();

            switch (choice) {
                case 1:
                    Student stud = new Student(Student.studentCounter + 1, "", 0, "", 0.0f);
                    stud.setDetails();
                    break;
                case 2:
                    System.out.println("Enter Student ID to get details: ");
                    int id = scn.nextInt();
                    Student.getDetails(id);
                    break;
                case 3:
                    System.out.println("Enter Student ID to update details: ");
                    int updateId = scn.nextInt();
                    Student studentToUpdate = Student.studentMap.get(updateId);
                    if (studentToUpdate != null) {
                        Student.updateDetails(updateId);
                    } else {
                        System.out.println("Student with ID " + updateId + " not found.");
                    }
                    break;
                case 4:
                    System.out.println("Enter Student ID to get GPA: ");
                    int gpaId = scn.nextInt();
                    float gpa = Student.getGPA(gpaId);
                    if (gpa >= 0) {
                        System.out.println("GPA of Student with ID " + gpaId + ": " + gpa);
                    }
                    break;
                case 5:
                    System.out.println("Enter Student ID to update GPA: ");
                    int updateGpaId = scn.nextInt();
                    System.out.println("Enter the new GPA: ");
                    float newGpa = scn.nextFloat();
                    Student.updateGPA(updateGpaId, newGpa);
                    break;
                case 6:
                    Student.printAllStudents();
                    break;
                case 7:
                    System.out.println("Total number of students: " + Student.totalStudents);
                    break;
                case 8:
                    System.out.println("Enter Student ID 1 to compare GPAs: ");
                    int id1 = scn.nextInt();
                    System.out.println("Enter Student ID 2 to compare GPAs: ");
                    int id2 = scn.nextInt();
                    Student student1 = Student.studentMap.get(id1);
                    Student student2 = Student.studentMap.get(id2);
                    Student.compare(student1, student2);
                    break;
                case 9:
                    System.out.println("Exiting the program.");
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a valid option (1-9).");
                    break;
            }
        }
    }
}
