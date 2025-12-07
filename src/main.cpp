#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "student.h"
#include "course.h"
#include "gradeResultsManagment.h"
#include "studentManagment.h"

using namespace std;


int main(){

    loadStudents();

    int choice;
    while (true) {
        cout << "\n============== University Management System ==============\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Student Information\n";
        cout << "4. List All Students\n";
        cout << "5. Enroll Student in Courses\n";
        cout << "6. Add Course\n";
        cout << "7. List All Courses\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        if (choice == 0) {
            cout << "Exiting...\n";
            saveStudents();
            break;
        }

        if (choice == 1) {
            string fn, ln, dep;
            int yos;

            cout << "Enter First Name: ";
            cin >> fn;

            cout << "Enter Last Name: ";
            cin >> ln;

            cout << "Enter Department (CSE/ECE/EPE): ";
            cin >> dep;

            cout << "Enter Year of Study: ";
            cin >> yos;

            students.push_back(Student(fn, ln, dep, yos));

            cout << "Student Added Successfully!\n";
            cout << "Your ID: " << students.back().getID() << "\n";
        }

        else if (choice == 2) {
            string id;
            cout << "Enter Student ID to Delete: ";
            cin >> id;
            deleteStudent(id);
            cout << "Deleted Successfully!\n";
        }

        else if (choice == 3) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;

            bool found = false;

            for (auto &s : students) {
                if (s.getID() == id) {
                    found = true;

                    cout << "\n=== Student Information ===\n";
                    s.info();
                    cout << "\n";

                    // cout << "Enrolled Courses:\n";
                    // s.getEnrolledCourses();
                    // cout << "\nGrades:\n";
                    // s.getGrades();
                    // cout << "\n";

                    break;
                }
            }

            if (!found)
                cout << "Student not found!\n";


        }

        else if (choice == 4) {
            cout << "\n=== Students List ===\n";
            studentsList();
            cout << "\n";
        }

        else if (choice == 5) {
            string id;
            cout << "Enter Student ID to Enroll in Courses: ";
            cin >> id;

            bool found = false;
            for (auto &s : students) {
                if (s.getID() == id) {
                    found = true;
                    s.enrollCourse();
                    cout << "Enrollment Completed!\n";
                }
            }

            if (!found)
                cout << "Student not found!\n";
        }

        else if (choice == 6) {
            string code, name, prof, dep;
            int y;

            cout << "Enter Course Code: ";
            cin >> code;

            cout << "Enter Course Name: ";
            cin >> name;

            cout << "Enter Professor Name: ";
            cin >> prof;

            cout << "Enter Department: ";
            cin >> dep;

            cout << "Enter Year: ";
            cin >> y;

            courses.push_back(Course(code, name, prof, dep, y));
            cout << "Course Added!\n";
        }

        else if (choice == 7) {
            cout << "\n=== Courses List ===\n";
            for (auto &c : courses) {
                cout << "{ " << c.getCode() << " , "
                     << c.getName() << " , "
                     << c.getProfessor() << " , "
                     << c.getDepartment() << " , "
                     << c.getYear() << " }\n";
            }
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
