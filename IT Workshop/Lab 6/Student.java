import java.util.ArrayList;
import java.util.Scanner;

public class Student {

    private static int studentCounter = 0;

    private final int studentId;
    private String name;
    private int studentAge;
    private String studentMajor;
    private float studentGPA;

    public Student() {
        this.studentId = ++studentCounter;
    }

    public void setDetails() {
        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the name of the Student: ");
        this.name = scn.nextLine();
        System.out.println("Enter the age of the student: ");
        this.studentAge = scn.nextInt();
        scn.nextLine();
        System.out.println("Enter the Student's Major: ");
        this.studentMajor = scn.nextLine();
        System.out.println("Enter the Student's GPA: ");
        this.studentGPA = scn.nextFloat();
    }

    public void updateDetails() {
        Scanner scn = new Scanner(System.in);
        System.out.println("Updating details for Student ID: " + this.studentId);
        System.out.println("Enter the new name of the Student: ");
        this.name = scn.nextLine();
        System.out.println("Enter the new age of the student: ");
        this.studentAge = scn.nextInt();
        scn.nextLine();
        System.out.println("Enter the new Student's Major: ");
        this.studentMajor = scn.nextLine();
        System.out.println("Enter the new Student's GPA: ");
        this.studentGPA = scn.nextFloat();
        System.out.println("Details updated successfully.");
    }

    public static void getDetails(ArrayList<Student> students, int id) {
        Student stud = getStudent(students, id);
        if (stud != null) {
            System.out.println();
            System.out.println("Student ID: " + stud.studentId);
            System.out.println("Name: " + stud.name);
            System.out.println("Age: " + stud.studentAge);
            System.out.println("Major: " + stud.studentMajor);
            System.out.println("GPA: " + stud.studentGPA);
            System.out.println();
        } else {
            System.out.println();
            System.out.println("Student with ID " + id + " not found.");
            System.out.println();
        }
    }

    public static Student getStudent(ArrayList<Student> students, int id) {
        for (Student student : students) {
            if (student.studentId == id) {
                return student;
            }
        }
        return null;
    }

    public static float getGPA(ArrayList<Student> students, int id) {
        Student stud = getStudent(students, id);
        if (stud != null) {
            return stud.studentGPA;
        } else {
            System.out.println("Student with ID " + id + " not found.");
            return -1.0f;
        }
    }

    public static void printAllStudents(ArrayList<Student> students) {
        System.out.println("List of all students:");
        for (Student student : students) {
            System.out.println("Student ID: " + student.studentId);
            System.out.println("Name: " + student.name);
            System.out.println("Age: " + student.studentAge);
            System.out.println("Major: " + student.studentMajor);
            System.out.println("GPA: " + student.studentGPA);
            System.out.println();
        }
    }

    public static void updateGPA(ArrayList<Student> students, int id, float newGPA) {
        Student stud = getStudent(students, id);
        if (stud != null) {
            stud.studentGPA = newGPA;
            System.out.println("GPA updated successfully for Student ID: " + stud.studentId);
        } else {
            System.out.println("Student with ID " + id + " not found.");
        }
    }

    public static void compare(Student student1, Student student2,ArrayList<Student> students) {
        if (student1 == null || student2 == null) {
            System.out.println("One or both of the students do not exist.");
        } else if (student1.studentGPA > student2.studentGPA) {
            System.out.println("Student with higher GPA:");
            Student.getDetails(students,student1.studentId);
        } else if (student2.studentGPA > student1.studentGPA) {
            System.out.println("Student with higher GPA:");
            Student.getDetails(students,student2.studentId);
        } else {
            System.out.println("Both students have the same GPA.");
        }
    }


}
