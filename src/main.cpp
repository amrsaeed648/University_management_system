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


using namespace std;

const string Admin_UserName = "ADMIN";
const string Admin_Password = "0000";

void adminMenu();
void studentMenu(const Student& s);
string convertToUpper(string str);

int main(){

    loadStudents();
    loadCourses();

        int choice;

    while (true) {
        cout << "\n======================= University Management System =======================\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        // LOGIN SYSTEM
        if (choice == 1) {

            string username, password;

            cout << "\n======================= Admin Login =======================\n";
            cout << "Enter UserName(Admin):  ";
            getline(cin, username);
            username = convertToUpper(username);

            cout << "Enter Password(Admin):  ";
            getline(cin, password);

            if (username == Admin_UserName && password == Admin_Password) {
                cout << "\nLogin Successful.\n";
                adminMenu();
            } else {
                cout << "\nInvalid Username or Password!\n";
            }
        }

        else if (choice == 2) {
        string id, pass;

        cout << "\n======================= Student Login =======================\n";
        cout << "Enter UserName(ID): ";
        getline(cin, id);

        cout << "Enter Password(ID): ";
        getline(cin, pass);

        bool found = false;

        for (auto& s : students) {
            if (s.getID() == id && s.getID() == pass) { // password = ID
                cout << "\nLogin Successful.\n";
                studentMenu(s);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nInvalid ID or Password!\n";
        }
    }

        else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }


    return 0;
}


void adminMenu(){
    int choice;

    while (true) {
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
            continue;
        }

        switch (choice) {
            case 1:
                studentManagementMenu();
                break;
            case 2:
                courseManagementMenu();
                break;
            case 3:
                gradeManagementMenu();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option!\n";
                break;
        }
    }
}

void studentMenu(const Student& s) {
    int choice;

    while (true) {
        cout << "\n======================= Student Dashboard =======================\n";
        cout << "Welcome, " << s.getFirstName() << " " << s.getLastName() << "\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Enrolled Courses\n";
        cout << "3. View Grades\n";
        cout << "4. Logout\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.info();
                break;
            case 2:
                s.getEnrolledCourses();
                break;
            case 3:
                s.getGrades();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice!\n";
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
