#include <iostream>
#include <limits>
#include "gradeResultsManagment.h"
#include "studentManagment.h"
#include "UI.h"
using namespace std;

void gradeManagementMenu() {
    int choice;
    do
    {
        clearScreen();
        printBanner();
        animatedPrint( "======================= Grade Management =======================\n");
        animatedPrint( "1. Assign Grade\n");
        animatedPrint( "2. Edit Grade\n");
        animatedPrint( "3. Display Grades by Student ID\n");
        animatedPrint( "4. Display Grades by Course Code\n");
        animatedPrint("0. Back to Main Menu\n");
        animatedPrint( "Choose: ");
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            animatedPrint(RED "Invalid input! Please enter a number.\n" RESET);
            pauseScreen();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
            case 1:
                clearScreen();
                printBanner();
                userAssignGrade();
                pauseScreen();
                break;

            case 2:
                clearScreen();
                printBanner();
                userEditGrade();
                pauseScreen();
                break;

            case 3:
                clearScreen();
                printBanner();
                displayGradeByStudentId();
                pauseScreen();
                break;

            case 4:
                clearScreen();
                printBanner();
                displayGradeByCode();
                pauseScreen();
                break;

            case 0:
                clearScreen();
                printBanner();
                animatedPrint( "Returning to previous menu...\n");
                pauseScreen();
                break;

            default:
                clearScreen();
                printBanner();
                animatedPrint(RED "Invalid choice! Please try again.\n" RESET);
                pauseScreen();
        }

    } while (choice != 0);
}