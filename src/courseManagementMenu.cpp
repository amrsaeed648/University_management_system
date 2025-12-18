#include <iostream>
#include <limits>
#include "course.h"
#include "database.h"
#include"UI.h"
using namespace std;

void courseManagementMenu() {
    int choice;
    string code;

    do {
        clearScreen();
        printBanner();
        animatedPrint("======================= Course Management =======================\n");
        animatedPrint( "1. Add Course\n");
        animatedPrint( "2. Delete Course\n");
        animatedPrint( "3. Edit Course\n");
        animatedPrint("4. Display All Courses\n");
        animatedPrint( "0. Save and return to Admin Menu\n");
        animatedPrint( "Enter choice: ");
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            animatedPrint(RED "Invalid input! Please enter a number.\n" RESET);
            pauseScreen();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        switch (choice) {
            case 1:
                clearScreen();
                printBanner();
                addCourse();
                cin.ignore();
                pauseScreen();
                break;

            case 2:
                clearScreen();
                printBanner();
               animatedPrint("Enter Course Code to delete: ");
                cin >> code;
                deleteCourse(code);
                cin.ignore();
                pauseScreen();
                break;

            case 3:
                clearScreen();
                printBanner();
                animatedPrint( "Enter Course Code to edit: ");
                cin >> code;
                editCourse(code);
                saveAllCoursesToDB();
                cin.ignore();
                pauseScreen();
                break;

            case 4:
                clearScreen();
                printBanner();
                displayCourses();
                cin.ignore();
                pauseScreen();
                break;

            case 0:
               animatedPrint( "Saved Successfully.\n");
               animatedPrint( "Returning to Admin Menu...\n\n");
                cin.ignore();
                pauseScreen();
                break;

            default:
                animatedPrint( "Invalid choice! Try again.\n\n");
                cin.ignore();
                pauseScreen();
        }

    } while (choice != 0);
}
