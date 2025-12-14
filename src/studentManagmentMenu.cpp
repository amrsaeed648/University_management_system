#include <iostream>
#include "student.h"
#include "studentManagment.h"
#include "UI.h"
using namespace std;



void studentManagementMenu() {
    while (true) {
        clearScreen();
        printBanner();
        animatedPrint( "\n=============== Student Management ===============\n");
        animatedPrint( "1. Add Student\n");
        animatedPrint( "2. Update Student\n");
        animatedPrint( "3. Delete Student\n");
        animatedPrint( "4. Show Student Information\n");
        animatedPrint( "5. Students List\n");
        animatedPrint( "6. Enroll Student in Course\n");
        animatedPrint( "0. Save and return to Admin Menu\n");
        animatedPrint("Choose: ");

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
            animatedPrint( "Enter Student ID: ");
            cin >> id;
            updateStudent(id);
            pauseScreen();
        }
        else if (c == 3){
            clearScreen();
            printBanner();
            string id;
            animatedPrint( "Enter Student ID: ");
            cin >> id;
            deleteStudent(id);
            pauseScreen();
        }
        else if (c == 4) {
            clearScreen();
            printBanner();
            string id;
            animatedPrint( "Enter Student ID: ");
            cin >> id;
            showStudentInfo(id);
            pauseScreen();
        }
        else if (c == 5){
            clearScreen();
            printBanner();
            studentsList();
            pauseScreen();
        }
        else if (c == 6){
            clearScreen();
            printBanner();
            enrollStudentInCourse();
            pauseScreen();
        }
        else if (c == 0){
            clearScreen();
            printBanner();
            animatedPrint( GREEN"All changes already saved to database.\n" RESET);
            animatedPrint( "Returning to Admin Menu...\n\n");
            pauseScreen();
            break;
        }
        else {cout << RED << "Invalid Choice.\n" << RESET; pauseScreen();}

    }
}
