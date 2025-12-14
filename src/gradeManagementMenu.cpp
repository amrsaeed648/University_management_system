#include <iostream>
#include "gradeResultsManagment.h"
#include "studentManagment.h"
using namespace std;

void gradeManagementMenu() {
    int choice;
    do
    {
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
                break;

            case 2:
                userEditGrade();
                break;

            case 3:
                displayGradeByStudentId();
                break;

            case 4:
                displayGradeByCode();
                break;

            case 0:
                cout << "Returning to previous menu...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);
}