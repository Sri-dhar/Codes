import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static ArrayList<Student> students = new ArrayList<>();

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        while (true) {
            System.out.println("Enter an option:");
            System.out.println("1. Add a student");
            System.out.println("2. Get student details");
            System.out.println("3. Update student details");
            System.out.println("4. Get student GPA");
            System.out.println("5. Update student GPA");
            System.out.println("6. Print all student information");
            System.out.println("7. Compare GPAs of two students");
            System.out.println("8. Exit");

            int choice = scn.nextInt();
            scn.nextLine();

            switch (choice) {
                case 1:
                    Student student = new Student();
                    student.setDetails();
                    students.add(student);
                    break;
                case 2:
                    System.out.println("Enter Student ID to get details: ");
                    int id = scn.nextInt();
                    Student.getDetails(students, id);
                    break;
                case 3:
                    System.out.println("Enter Student ID to update details: ");
                    int updateId = scn.nextInt();
                    Student studentToUpdate = Student.getStudent(students, updateId);
                    if (studentToUpdate != null) {
                        studentToUpdate.updateDetails();
                    } else {
                        System.out.println("Student with ID " + updateId + " not found.");
                    }
                    break;
                case 4:
                    System.out.println("Enter Student ID to get GPA: ");
                    int gpaId = scn.nextInt();
                    float gpa = Student.getGPA(students, gpaId);
                    if (gpa >= 0) {
                        System.out.println("GPA of Student with ID " + gpaId + ": " + gpa);
                    }
                    break;
                case 5:
                    System.out.println("Enter Student ID to update GPA: ");
                    int updateGpaId = scn.nextInt();
                    System.out.println("Enter the new GPA: ");
                    float newGpa = scn.nextFloat();
                    Student.updateGPA(students, updateGpaId, newGpa);
                    break;
                case 6:
                    Student.printAllStudents(students);
                    break;
                case 7:
                    System.out.println("Enter Student ID 1 to compare GPAs: ");
                    int id1 = scn.nextInt();
                    System.out.println("Enter Student ID 2 to compare GPAs: ");
                    int id2 = scn.nextInt();
                    Student student1 = Student.getStudent(students, id1);
                    Student student2 = Student.getStudent(students, id2);
                    Student.compare(student1, student2, students);
                    break;
                case 8:
                    System.out.println("Exiting the program.");
                    scn.close();
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please enter a valid option (1-8).");
                    break;
            }
        }
    }
}
