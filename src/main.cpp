#ifdef _WIN32
#include <windows.h>
#endif

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
#include "database.h"
#include "sqlite3.h"

#ifdef _WIN32
#include <windows.h>
#endif

// ================= COLORS =================
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// ================= BACKGROUND COLORS =================
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

using namespace std;

const string Admin_UserName = "ADMIN";
const string Admin_Password = "0000";

void adminMenu();
void studentMenu(const Student& s);
string convertToUpper(string str);
void printBanner();

int main(){
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    openDatabase();

    createStudentTable();
    createCourseTables();

    loadStudentsFromDB();
    loadCoursesFromDB();

    int choice;

    while (true) {
        clearScreen();
        printBanner();
        // cout << "\n======================= University Management System =======================\n";
        animatedPrint("1. Admin\n");
        animatedPrint("2. Student\n");
        animatedPrint("0. Exit\n");
        animatedPrint("Enter your choice : ");
        cin >> choice;
        cin.ignore();

        // LOGIN SYSTEM
        if (choice == 1) {
            clearScreen();
            printBanner();
            string username, password;

            animatedPrint(BOLD "\n======================= Admin Login =======================\n" RESET);
            animatedPrint("Enter Username(Admin): ");
            getline(cin, username);
            username = convertToUpper(username);

            animatedPrint("Enter Password: ");
            getline(cin, password);

            if (username == Admin_UserName && password == Admin_Password) {
                animatedPrint(GREEN "\nLogin Successful.\n" RESET);
                pauseScreen();
                adminMenu();
            } else {
                animatedPrint(RED "\nInvalid Username or Password!\n" RESET);
                pauseScreen();
            }
        }

        else if (choice == 2) {
            clearScreen();
            printBanner();
            string id, pass;
            animatedPrint("\n======================= Student Login =======================\n");
            animatedPrint("Enter UserName(ID): ");
            getline(cin, id);
            animatedPrint("Enter Password(ID): ");
            getline(cin, pass);

            bool found = false;

            for (auto& s : students) {
                if (s.getID() == id && s.getID() == pass) { // password = ID
                    animatedPrint(GREEN "\nLogin Successful.\n" RESET);
                    pauseScreen();
                    studentMenu(s);
                    found = true;
                    break;
                }
            }

            if (!found) {
                animatedPrint(RED "\nInvalid Username or Password!\n" RESET);
                pauseScreen();
            }
        }

        else if (choice == 0) {
            animatedPrint("Exiting program...\n");
            break;
        }
        else {
            animatedPrint(RED "Invalid choice! Try again.\n" RESET);
            pauseScreen();
        }
    }

    closeDatabase();
    return 0;
}


void adminMenu(){
    int choice;

    while (true) {
        clearScreen();
        printBanner();
        // cout << "\n======================= University Management System =======================\n";
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
                printBanner();
                studentManagementMenu();
                break;
            case 2:
                clearScreen();
                printBanner();
                courseManagementMenu();
                break;
            case 3:
                clearScreen();
                printBanner();
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
        printBanner();
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
                printBanner();
                s.info();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                printBanner();
                s.getEnrolledCourses();
                pauseScreen();
                break;
            case 3:
                clearScreen();
                printBanner();
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




