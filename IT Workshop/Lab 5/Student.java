import java.util.Scanner;
import java.util.HashMap;

public class Student {

    static final HashMap<Integer, Student> studentMap = new HashMap<>();
    static int studentCounter = 0;
    static int totalStudents = 0;

    private int studentId;
    private String name;
    private int studentAge;
    private String studentMajor;
    private float studentGPA;

    public Student(int id, String name, int age, String major, float GPA) {
        this.studentId = id;
        this.name = name;
        this.studentAge = age;
        this.studentMajor = major;
        this.studentGPA = GPA;
        studentMap.put(id, this);
        totalStudents++;
    }

    public void setDetails() {
        Scanner scn = new Scanner(System.in);
        this.studentId = studentCounter + 1;
        System.out.println("Enter the name of the Student: ");
        this.name = scn.nextLine();
        System.out.println("Enter the age of the student: ");
        this.studentAge = scn.nextInt();
        scn.nextLine();
        System.out.println("Enter the Student's Major: ");
        this.studentMajor = scn.nextLine();
        System.out.println("Enter the Student's GPA: ");
        this.studentGPA = scn.nextFloat();
        studentCounter++;
        studentMap.put(this.studentId, this);
    }

    public static void getDetails(int id) {
        Student stud = studentMap.get(id);
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

    public static void updateDetails(int id) {
        Scanner scn = new Scanner(System.in);
        if (studentMap.containsKey(id)) {
            Student stud = studentMap.get(id);
            System.out.println("Updating details for Student ID: " + stud.studentId);
            System.out.println("Enter the new name of the Student: ");
            stud.name = scn.nextLine();
            System.out.println("Enter the new age of the student: ");
            stud.studentAge = scn.nextInt();
            scn.nextLine();
            System.out.println("Enter the new Student's Major: ");
            stud.studentMajor = scn.nextLine();
            System.out.println("Enter the new Student's GPA: ");
            stud.studentGPA = scn.nextFloat();
            System.out.println("Details updated successfully.");
        } else {
            System.out.println("Student with ID " + id + " not found.");
        }
    }

    public static float getGPA(int id) {
        if (studentMap.containsKey(id)) {
            Student stud = studentMap.get(id);
            return stud.studentGPA;
        } else {
            System.out.println("Student with ID " + id + " not found.");
            return (float) -1;
        }
    }

    public static void printAllStudents() {
        System.out.println("List of all students:");
        for (Student student : studentMap.values()) {
            System.out.println("Student ID: " + student.studentId);
            System.out.println("Name: " + student.name);
            System.out.println("Age: " + student.studentAge);
            System.out.println("Major: " + student.studentMajor);
            System.out.println("GPA: " + student.studentGPA);
            System.out.println();
        }
    }

    public static void updateGPA(int id, float newGPA) {
        if (studentMap.containsKey(id)) {
            Student stud = studentMap.get(id);
            stud.studentGPA = newGPA;
            System.out.println("GPA updated successfully for Student ID: " + stud.studentId);
        } else {
            System.out.println("Student with ID " + id + " not found.");
        }
    }

    public static void compare(Student student1, Student student2) {
        if (student1 == null || student2 == null) {
            System.out.println("One or both of the students do not exist.");
        } else if (student1.studentGPA > student2.studentGPA) {
            System.out.println("Student with higher GPA:");
            getDetails(student1.studentId);
        } else if (student2.studentGPA > student1.studentGPA) {
            System.out.println("Student with higher GPA:");
            getDetails(student2.studentId);
        } else {
            System.out.println("Both students have the same GPA.");
        }
    }
}
