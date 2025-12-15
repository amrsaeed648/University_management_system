#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <utility>
#include "gradeResultsManagment.h"
#include "Student.h"
#include "sqlite3.h"
#include "course.h"
#include "studentManagment.h"
#include "UI.h"
#include "database.h"

using namespace std;

int getStudentIndex(string id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getID() == id)
            return i;
    }
    return -1; // Not found
}

void addStudent () {
    string fn, ln, dep;
    int yos;
    clearScreen();
    printBanner();
    animatedPrint("Enter First Name: ");
    cin >> fn;

    animatedPrint( "Enter Last Name: ");
    cin >> ln;

    animatedPrint( "Enter Department (GEN, CSE, ECE, POW): ");
    cin >> dep;

    animatedPrint( "Enter Academic Year (1, 2, 3, 4): ");
    cin >> yos;

    try {
        Student st(fn, ln, dep, yos);
        students.push_back(st);
        saveStudentToDB(st);
        animatedPrint(GREEN "Student Added Successfully.\n" RESET);
        animatedPrint("Student ID is: "+st.getID()+" .\n");
        animatedPrint("Student Email is: "+st.getEmail()+" .\n");
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}


void deleteStudent(string id){
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);

    if (index == -1) {
        animatedPrint(RED "Student Not Found!\n" RESET);
        pauseScreen();
        return;
    }

    // Remove from database
    deleteStudentFromDB(id);

    // Remove student from students vector
    students.erase(students.begin() + index);

    // Remove all grades related to this student
    for (auto it = studentCourseGrades.begin(); it != studentCourseGrades.end(); ) {
        if (it->studentID == id) {
            it = studentCourseGrades.erase(it); // erase returns the next iterator
        } else {
            ++it;
        }
    }
    saveAllGradesToDB();
    animatedPrint(GREEN "Student and related grades deleted successfully\n" RESET);
    /*pauseScreen();*/
}

void studentsList() {
    clearScreen();
    printBanner();
    animatedPrint( BOLD  "\n======================= Student List =======================\n" RESET );
    for (int i = 0; i < students.size(); i++) students[i].info();
    /*pauseScreen();*/
}



void showStudentInfo(string id)
{
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);
    if (index == -1)
    {
        animatedPrint( RED "Student Not Found!\n" RESET );
        pauseScreen();
        return;
    }

    Student &s = students[index];

    animatedPrint( "\n============== STUDENT INFORMATION ==============\n");
    animatedPrint( "First Name   : " + s.getFirstName() + "\n");
    animatedPrint( "Last Name    : " + s.getLastName() + "\n");
    animatedPrint( "ID           : " + s.getID() + "\n");
    animatedPrint( "Email        : " + s.getEmail() + "\n");
    animatedPrint( "Department   : " + s.getDepartment() + "\n");
    animatedPrint( "Academic Year: " + to_string(s.getYearOfStudy()) + "\n");
    animatedPrint( "=================================================\n");
    /*pauseScreen();*/
}
void enrollStudentInCourse()
{
    clearScreen();
    printBanner();
    string id, courseCode;
    animatedPrint("Enter Student ID: ");
    cin >> id;

    int index = getStudentIndex(id);
    if (index == -1)
    {
        animatedPrint( RED"Student Not Found!\n" RESET);
        pauseScreen();
        return;
    }
    animatedPrint( "Enter Course Code: ");
    cin >> courseCode;
    if (validateCourse(courseCode))
    {
        // Add course to student's enrolled courses
        students[index].addCourse(courseCode);

        // Add entry to the global studentCourseGrades vector with default grade 0.0
        studentCourseGrade scg;
        scg.studentID = id;
        scg.courseCode = courseCode;
        scg.Grade = 0.0;
        studentCourseGrades.push_back(scg);
        saveAllGradesToDB();


        animatedPrint( GREEN  "Enrolled Successfully."  RESET);
    }
    else
    {
        animatedPrint( RED "Course Not Found!\n" RESET );
    }
}

