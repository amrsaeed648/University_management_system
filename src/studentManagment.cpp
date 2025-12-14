#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "gradeResultsManagment.h"
#include "Student.h"
#include "sqlite3.h"
#include "course.h"
#include "studentManagment.h"
#include "UI.h"

using namespace std;

int getStudentIndex(string id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getID() == id)
            return i;
    }
    return -1; // Not found
}

void addStudent () {
    string fn, ln, dep;
    int yos;
    clearScreen();
    printBanner();
    cout << "Enter First Name: ";
    cin >> fn;

    cout << "Enter Last Name: ";
    cin >> ln;

    cout << "Enter Department (GEN/CSE/ECE/POW): ";
    cin >> dep;

    cout << "Enter Academic Year: ";
    cin >> yos;
    try {
        Student st(fn, ln, dep, yos);
        students.push_back(st);
        saveStudentToDB(st);
        cout<<"Student Added Successfully.\n";
        cout<<"Student ID is: "<<st.getID()<<" .\n";
        cout<<"Student Email is: "<<st.getEmail()<<" .\n";
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    pauseScreen();
}

void updateStudent(string id) {
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        pauseScreen();
        return;
    }

    Student& st = students[index];

    while (true) {
        clearScreen();
        cout << "================= Updating " << st.getFirstName() << " " << st.getLastName() << " =================\n";
        cout << "1. First Name\n"
             << "2. Last Name\n"
             << "3. Department\n"
             << "4. Year of Study\n"
             << "0. Exit\n"
             << "Select: ";

        int c;
        cin >> c;

        if (c == 0) break;

        string input;
        try {
            switch (c) {
                case 1:
                    cout << "New First Name: ";
                    cin >> input;
                    st.setFirstName(input);
                    break;

                case 2:
                    cout << "New Last Name: ";
                    cin >> input;
                    st.setLastName(input);
                    break;

                case 3:
                    cout << "New Department: ";
                    cin >> input;
                    st.setDepartment(input);
                    break;

                case 4:
                    cout << "New Year of Study: ";
                    cin >> input;
                    st.setYearOfStudy(stoi(input));
                    break;

                default:
                    cout << "Invalid choice\n";
                    pauseScreen();
                    continue;
            }

            saveStudentToDB(st);

            cout << "Data Updated Successfully\n";
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        pauseScreen();
    }
}

void deleteStudent(string id) {
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        pauseScreen();
        return;
    }
    deleteStudentFromDB(id);

    students.erase(students.begin() + index);

    cout << "Student Deleted Successfully\n";
    pauseScreen();
}

void studentsList() {
    clearScreen();
    printBanner();
    cout<< BOLD << "\n======================= Student List =======================\n" << RESET;
    for (int i = 0; i < students.size(); i++) students[i].info();
    pauseScreen();
}



void showStudentInfo(string id)
{
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout<< RED <<"❌Student Not Found!\n"<< RESET;
        pauseScreen();
        return;
    }

    Student &s = students[index];

    cout << "\n============== STUDENT INFORMATION ==============\n";
    cout << "First Name   : " << s.getFirstName() << "\n";
    cout << "Last Name    : " << s.getLastName() << "\n";
    cout << "ID           : " << s.getID() << "\n";
    cout << "Email        : " << s.getEmail() << "\n";
    cout << "Department   : " << s.getDepartment() << "\n";
    cout << "Academic Year: " << s.getYearOfStudy() << "\n";
    cout << "=================================================\n";
    pauseScreen();
}

void enrollStudentInCourse()
{
    clearScreen();
    printBanner();
    string id, course;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout << "Student Not Found!\n";
        return;
    }

    cout << "Enter Course Code: ";
    cin >> course;

    students[index].addCourse(course);
    cout<< GREEN <<"Enrolled Successfully."<< RESET;

    pauseScreen();
}