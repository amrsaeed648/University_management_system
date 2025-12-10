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
    do
    {
        cout << "Enter a Valid Course Code to add its grade : \n";
        cin >> courseCode;
    } while (getCourseIndex(courseCode)<0);
    do
    {
        cout << "Enter a Valid Student ID to add his grade : \n";
        cin >> studentId;
    } while (getStudentIndex(studentId)<0);
    do
    {
        cout << "Enter The Grade (0 -> 100) : \n";
        cin >> grade;
    } while (grade>=100 || grade<=0);
    assignGrade(courseCode,studentId,grade);
}
void userEditGrade () //asks the user for the grade then calls the Edit function to Edit it
{
    string courseCode,studentId;
    int grade;
    do
    {
        cout << "Enter a Valid Course Code to Edit its grade : \n";
        cin >> courseCode;
    } while (getCourseIndex(courseCode)<0);
    do
    {
        cout << "Enter a Valid Student ID to Edit his grade : \n";
        cin >> studentId;
    } while (getStudentIndex(studentId)<0);
    do
    {
        cout << "Enter The Grade (0 -> 100) : \n";
        cin >> grade;
    } while (grade>=100 || grade<=0);
    assignGrade(courseCode,studentId,grade);
}
void displayGradeByStudentId ()
{
    string studentId;
    int studentIndex;
    do
    {
        cout << "Enter a Student ID : \n";
        cin >> studentId;
        studentIndex = getStudentIndex(studentId);
    }  while (studentIndex<0);
    students.at(studentIndex).getGrades();
}
void displayGradeByCode ()
{
    string code;
    int codeIndex;
    do
    {
        cout << "Enter a Course Code: \n";
        cin >> code;
        codeIndex = getCourseIndex(code);
    }  while (codeIndex<0);
    for (const auto & student : students)
    {
        student.getGradesOnly(code);
    }
}