#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "student.h"
#include "studentManagment.h"
#include "studentManagmentMenu.h"
#include "course.h"
#include "courseManagementMenu.h"
#include "gradeResultsManagment.h"
#include "gradeManagementMenu.h"
#include "UI.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string Admin_UserName = "ADMIN";
const string Admin_Password = "0000";

void adminMenu();
void studentMenu(const Student& s);
string convertToUpper(string str);

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    loadStudents();
    loadCourses();

        int choice;

    while (true) {
        clearScreen();
        cout << "\n======================= University Management System =======================\n";
        cout << "1.🔐 Admin\n";
        cout << "2.🎓 Student\n";
        cout << "0.🚪 Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        // LOGIN SYSTEM
        if (choice == 1) {
            clearScreen();
            string username, password;

            cout << "\n======================= Admin Login =======================\n";
            cout << "Enter UserName(Admin):  ";
            getline(cin, username);
            username = convertToUpper(username);

            cout << "Enter Password(Admin):  ";
            getline(cin, password);

            if (username == Admin_UserName && password == Admin_Password) {
                cout << "\n✅Login Successful.\n";
                pauseScreen();
                adminMenu();
            } else {
                cout << "\nInvalid Username or Password!\n";
                pauseScreen();
            }
        }

        else if (choice == 2) {
            clearScreen();
            string id, pass;

            cout << "\n======================= Student Login =======================\n";
            cout << "Enter UserName(ID): ";
            getline(cin, id);

            cout << "Enter Password(ID): ";
            getline(cin, pass);

            bool found = false;

            for (auto& s : students) {
                if (s.getID() == id && s.getID() == pass) { // password = ID
                    cout << "\n✅Login Successful.\n";
                    pauseScreen();
                    studentMenu(s);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\nInvalid ID or Password!\n";
                pauseScreen();
            }
        }

        else if (choice == 0) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
            pauseScreen();
        }
    }


    return 0;
}


void adminMenu(){
    int choice;

    while (true) {
        clearScreen();
        cout << "\n======================= University Management System =======================\n";
        cout << "1. Student Management\n";
        cout << "2. Course Management\n";
        cout << "3. Grade & Results Management\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input! Please enter a number between 0 and 3.\n";
            pauseScreen();
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                studentManagementMenu();
                break;
            case 2:
                clearScreen();
                courseManagementMenu();
                break;
            case 3:
                clearScreen();
                gradeManagementMenu();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option!\n";
                pauseScreen();
                break;
        }
    }
}

void studentMenu(const Student& s) {
    int choice;

    while (true) {
        clearScreen();
        cout << "\n======================= Student Dashboard =======================\n";
        cout << "Welcome, " << s.getFirstName() << " " << s.getLastName() << "\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Enrolled Courses\n";
        cout << "3. View Grades\n";
        cout << "0. Logout\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                s.info();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                s.getEnrolledCourses();
                pauseScreen();
                break;
            case 3:
                clearScreen();
                displayGradeByStudentId ();
                pauseScreen();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
                pauseScreen();
                break;
        }
    }
}


string convertToUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
    return str;
}

