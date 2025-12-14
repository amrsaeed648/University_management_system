#include <iostream>
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
        cout << "======================= Grade Management =======================\n";
        cout << "1. Assign Grade\n";
        cout << "2. Edit Grade\n";
        cout << "3. Display Grades by Student ID\n";
        cout << "4. Display Grades by Course Code\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                userAssignGrade();
                saveStudents();
                pauseScreen();
                break;

            case 2:
                userEditGrade();
                saveStudents();
                pauseScreen();
                break;

            case 3:
                displayGradeByStudentId();
                pauseScreen();
                break;

            case 4:
                displayGradeByCode();
                pauseScreen();
                break;

            case 0:
                cout << "Returning to previous menu...\n";
                pauseScreen();
                break;

            default:
                cout << RED <<"Invalid choice! Please try again.\n"<< RESET;
                pauseScreen();
        }

    } while (choice != 0);
}