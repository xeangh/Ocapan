#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student {
    int studentID;
    string firstName;
    string lastName;
    string course;
    float gpa;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

void displayMenu();
void addStudent();
void editStudent();
void deleteStudent();
void viewStudents();
int searchStudent(int id);
void displayStudentData(int index);
void sortByName();
void sortByGPA();
void clearScreen();
void pauseAndReturn();

int main() {
    int choice;
    do {
        clearScreen();
        displayMenu();
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: deleteStudent(); break;
            case 4: viewStudents(); break;
            case 5: clearScreen(); cout << "Exiting program...\n"; break;
            default: cout << "Invalid option. Try again.\n"; pauseAndReturn();
        }
    } while (choice != 5);

    return 0;
}

void clearScreen() {
    system("cls");
}

void pauseAndReturn() {
    cout << "\nPress any key to return to the menu...\n";
    cin.ignore();
    cin.get();
}

void displayMenu() {
    cout << "\n-- Student Management System --\n";
    cout << "[1] Add Student\n";
    cout << "[2] Edit Student\n";
    cout << "[3] Delete Student\n";
    cout << "[4] View Student\n";
    cout << "[5] Exit Program\n";
}

void addStudent() {
    clearScreen();
    if (studentCount >= MAX_STUDENTS) {
        cout << "Error: Student record is full!\n";
        pauseAndReturn();
        return;
    }

    Student newStudent;
    cout << "Enter Student ID: ";
    cin >> newStudent.studentID;

    if (searchStudent(newStudent.studentID) != -1) {
        cout << "Error: Duplicate Student ID.\n";
        pauseAndReturn();
        return;
    }

    cout << "Enter First Name: ";
    cin >> newStudent.firstName;
    cout << "Enter Last Name: ";
    cin >> newStudent.lastName;
    cout << "Enter Course: ";
    cin >> newStudent.course;
    cout << "Enter Previous Semester GPA: ";
    cin >> newStudent.gpa;

    if (newStudent.gpa < 0.0 || newStudent.gpa > 4.0) {
        cout << "Error: GPA must be between 0.0 and 4.0.\n";
        pauseAndReturn();
        return;
    }

    students[studentCount] = newStudent;
    studentCount++;
    cout << "Student added successfully!\n";
    pauseAndReturn();
}

int searchStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == id)
            return i;
    }
    return -1;
}

void editStudent() {
    clearScreen();
    if (studentCount == 0) {
        cout << "Error: No student records found!\n";
        pauseAndReturn();
        return;
    }

    int id;
    cout << "Enter Student ID to edit: ";
    cin >> id;
    int index = searchStudent(id);

    if (index == -1) {
        cout << "Error: Student not found!\n";
        pauseAndReturn();
        return;
    }

    cout << "Editing Student Data\n";
    displayStudentData(index);

    cout << "Enter New First Name: ";
    cin >> students[index].firstName;
    cout << "Enter New Last Name: ";
    cin >> students[index].lastName;
    cout << "Enter New Course: ";
    cin >> students[index].course;
    cout << "Enter New GPA: ";
    cin >> students[index].gpa;

    if (students[index].gpa < 0.0 || students[index].gpa > 4.0) {
        cout << "Error: GPA must be between 0.0 and 4.0.\n";
        pauseAndReturn();
        return;
    }

    cout << "Student record updated successfully!\n";
    pauseAndReturn();
}

void deleteStudent() {
    clearScreen();
    if (studentCount == 0) {
        cout << "Error: No student records found!\n";
        pauseAndReturn();
        return;
    }

    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    int index = searchStudent(id);

    if (index == -1) {
        cout << "Error: Student not found!\n";
        pauseAndReturn();
        return;
    }

    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    cout << "Student record deleted successfully!\n";
    pauseAndReturn();
}

void viewStudents() {
    clearScreen();
    if (studentCount == 0) {
        cout << "Error: No student records available!\n";
        pauseAndReturn();
        return;
    }

    int option;
    cout << "Select Viewing Option: \n";
    cout << "[1] Alphabetically\n";
    cout << "[2] By GPA (Ascending Order)\n";
    cout << "Choice: ";
    cin >> option;

    if (option == 1) {
        sortByName();
        cout << "Displaying records alphabetically:\n";
    } else if (option == 2) {
        sortByGPA();
        cout << "Displaying records by GPA (ascending order):\n";
    } else {
        cout << "Error: Invalid option!\n";
        pauseAndReturn();
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        displayStudentData(i);
    }
    pauseAndReturn();
}

void displayStudentData(int index) {
    cout << "---------------------------------\n";
    cout << "ID: " << students[index].studentID << "\n";
    cout << "Name: " << students[index].firstName << " " << students[index].lastName << "\n";
    cout << "Course: " << students[index].course << "\n";
    cout << "GPA: " << students[index].gpa << "\n";
    cout << "---------------------------------\n";
}

void sortByName() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].lastName > students[j + 1].lastName) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void sortByGPA() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].gpa > students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}
