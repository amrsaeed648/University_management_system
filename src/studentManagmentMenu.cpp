#include <iostream>
#include "student.h"
#include "studentManagment.h"
#include "UI.h"
using namespace std;



void studentManagementMenu() {
    while (true) {
        clearScreen();
        printBanner();
        cout << "\n=============== Student Management ===============\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Show Student Information\n";
        cout << "5. Students List\n";
        cout << "6. Enroll Student in Course\n";
        cout << "0. Save and return to Admin Menu\n";
        cout << "Choose: ";

        int c;
        cin >> c;

        if (c == 1){
            clearScreen();
            addStudent();
            pauseScreen();
        }
        else if (c == 2){
            clearScreen();
            printBanner();
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            updateStudent(id);
            pauseScreen();
        }
        else if (c == 3){
            clearScreen();
            printBanner();
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            deleteStudent(id);
            pauseScreen();
        }
        else if (c == 4) {
            clearScreen();
            printBanner();
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            showStudentInfo(id);
            pauseScreen();
        }
        else if (c == 5){
            clearScreen();
            studentsList();
            pauseScreen();
        }
        else if (c == 6){
            clearScreen();
            enrollStudentInCourse();
            pauseScreen();
        }
        else if (c == 0){
            clearScreen();
            cout << "All changes already saved to database.\n";
            cout << "Returning to Admin Menu...\n\n";
            pauseScreen();
            break;
        }
        else {cout << RED << "Invalid Choice.\n" << RESET; pauseScreen();}

    }
}
