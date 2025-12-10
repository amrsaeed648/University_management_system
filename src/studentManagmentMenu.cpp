#include <iostream>
#include "student.h"
#include "studentManagment.h"
using namespace std;

void studentManagementMenu() {
    while (true)
    {
        cout << "\n=============== ADMIN MENU ===============\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Show Student Information\n";
        cout << "5. Students List\n";
        cout << "6. Enroll Student in Course\n";
        cout << "0. Save & Exit\n";
        cout << "Choose: ";

        int c;
        cin >> c;

        if (c == 1){
            addStudent();
        }
        else if (c == 2){
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            updateStudent(id);
        }
        else if (c == 3){
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            deleteStudent(id);
        }
        else if (c == 4) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            showStudentInfo(id);
        }
        else if (c == 5){
            studentsList();
        }
        else if (c == 6)
        {
            enrollStudentInCourse();
        }
        else if (c == 0){
            saveStudents();
            cout << "Saved Successfully.\n";
            break;
        }
        else cout << "Invalid Choice.\n";
    }
}
