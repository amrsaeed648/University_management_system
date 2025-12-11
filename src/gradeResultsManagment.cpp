#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "gradeResultsManagment.h"
#include "Student.h"
#include "course.h"
#include "gradeManagementMenu.h"
#include "studentManagment.h"
using namespace std;
void assignGrade (const string& courseCode, const string& studentId, const int grade) // Assigns the grade to a student
{
    int studentIndex = getStudentIndex(studentId);
    if (studentIndex!= (-1) && getCourseIndex(courseCode) != (-1) && grade>=0 && grade<=100)
    {
        students.at(studentIndex).setGrade(courseCode,grade);
    }
}
void userAssignGrade () //asks the user for the grade then calls the Assign function to assign it
{
    string courseCode,studentId;
    int grade;
        cout << "Enter a Valid Course Code to add its grade : ";
        cin >> courseCode;
    if (getCourseIndex(courseCode)<0)
    {
        cout << "Invalid Code Input! \n";
        return;
    }
        cout << "Enter a Valid Student ID to add his grade : ";
        cin >> studentId;
    if (getStudentIndex(studentId)<0)
    {
        cout << "Invalid ID Input! \n";
        return;
    }
        cout << "Enter The Grade (0 -> 100) : ";
        cin >> grade;
    if (grade>=100 || grade<=0)
    {
        cout << "Invalid Grade Input! \n";
        return;
    }
    assignGrade(courseCode,studentId,grade);
    cout << "Assigned Successfully.\n";
}
void userEditGrade () //asks the user for the grade then calls the Edit function to Edit it
{
    string courseCode,studentId;
    int grade;
    cout << "Enter a Valid Course Code to Edit its grade : ";
    cin >> courseCode;
    if (getCourseIndex(courseCode)<0)
    {
        cout << "Invalid Code Input! \n";
        return;
    }
        cout << "Enter a Valid Student ID to Edit his grade : ";
        cin >> studentId;
    if (getStudentIndex(studentId)<0)
    {
        cout << "Invalid ID Input! \n";
        return;
    }
        cout << "Enter The Grade (0 -> 100) : ";
        cin >> grade;
    if (grade>=100 || grade<=0)
    {
        cout << "Invalid Grade Input! \n";
        return;
    }
    assignGrade(courseCode,studentId,grade);
}
void displayGradeByStudentId ()
{
    string studentId;
    int studentIndex;
        cout << "Enter a Student ID : ";
        cin >> studentId;
        studentIndex = getStudentIndex(studentId);
    if (studentIndex<0)
    {
        cout << "Invalid ID Input! \n";
        return;
    }
    if (!students.at(studentIndex).foundGrades1())
    {
        cout << "No Grades Yet.\n";
    }
    else
    {
        cout << students.at(studentIndex).getFirstName() << " " << students.at(studentIndex).getLastName() << "'s Grades: \n";
        students.at(studentIndex).getGrades();
    }
}
void displayGradeByCode ()
{
    string code;
    int codeIndex;
        cout << "Enter a Course Code: ";
        cin >> code;
        codeIndex = getCourseIndex(code);
    if (codeIndex<0)
    {
        cout << "Invalid Code Input! \n";
        return;
    }
    cout <<"The Course is " << courses.at(codeIndex).getName() << "\n";
    for (const auto & student : students)
    {
        if (student.foundGrades2(code))
        {
            cout << student.getFirstName() << " " << student.getLastName() << "'s Grade is ";
            student.getGradesOnly(code);
        }
        else
        {
            cout << "No Grades found for this Course.\n";
            break;
        }
    }
}
