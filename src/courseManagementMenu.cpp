#include <iostream>
#include "course.h"
using namespace std;

void courseManagementMenu() {
    int choice;
    string code;

    do {
        cout << "======================= Course Management =======================\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Edit Course\n";
        cout << "4. Display All Courses\n";
        cout << "0. Return to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
            case 1:
                addCourse();
                break;

            case 2:
                cout << "Enter Course Code to delete: ";
                cin >> code;
                deleteCourse(code);
                break;

            case 3:
                cout << "Enter Course Code to edit: ";
                cin >> code;
                editCourse(code);
                break;

            case 4:
                displayCourses();
                break;

            case 0:
                cout << "Returning to Admin Menu...\n\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n\n";
        }

    } while (choice != 0);
}
