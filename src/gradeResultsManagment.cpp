#include <iostream>
#include <string>
#include <vector>
#include "gradeResultsManagment.h"
#include "studentManagment.h"
#include "course.h"
#include "UI.h"
#include "student.h"
#include "database.h"

using namespace std;

// Vector holding all grades in memory
vector<studentCourseGrade> studentCourseGrades;

/* ===================== INTERNAL HELPERS ===================== */
static int findGradeIndex(const string& courseCode, const string& studentId)
{
    for (int i=0;i<studentCourseGrades.size();i++)
    {
        if (studentCourseGrades[i].courseCode == courseCode &&
            studentCourseGrades[i].studentID == studentId)
        {
            return i;
        }
    }
    return -1;
}

/* ===================== CORE LOGIC ===================== */
void assignGrade(const string& courseCode, const string& studentId, const int grade)
{
    int i = findGradeIndex(courseCode, studentId);
    if (i == -1) return;

    studentCourseGrades[i].Grade = grade;

    // Immediately save to database
    saveAllGradesToDB();
}

/* ===================== USER FUNCTIONS ===================== */
void userAssignGrade()
{
    string courseCode, studentId;
    int grade;

    cout << "Enter Course Code: ";
    cin >> courseCode;
    if (getCourseIndex(courseCode) < 0)
    {
        cout << RED << "Invalid Course Code!\n" << RESET;
        return;
    }

    cout << "Enter Student ID: ";
    cin >> studentId;
    if (getStudentIndex(studentId) < 0)
    {
        cout << RED << "Invalid Student ID!\n" << RESET;
        return;
    }

    int gradeIndex = findGradeIndex(courseCode, studentId);
    if (gradeIndex == -1)
    {
        cout << RED << "Student is NOT enrolled in this course.\n" << RESET;
        return;
    }

    cout << "Enter Grade (0 -> 100): ";
    cin >> grade;
    if (grade < 0 || grade > 100)
    {
        cout << RED << "Invalid Grade!\n" << RESET;
        return;
    }

    assignGrade(courseCode, studentId, grade);
    cout << GREEN << "Grade Assigned Successfully.\n" << RESET;
}

void userEditGrade()
{
    string courseCode, studentId;
    int grade;

    cout << "Enter Course Code: ";
    cin >> courseCode;
    if (getCourseIndex(courseCode) < 0)
    {
        cout << RED << "Invalid Course Code!\n" << RESET;
        return;
    }

    cout << "Enter Student ID: ";
    cin >> studentId;
    if (getStudentIndex(studentId) < 0)
    {
        cout << RED << "Invalid Student ID!\n" << RESET;
        return;
    }

    int gradeIndex = findGradeIndex(courseCode, studentId);
    if (gradeIndex == -1)
    {
        cout << RED << "Student is NOT enrolled in this course.\n" << RESET;
        return;
    }

    cout << "Enter New Grade (0 -> 100): ";
    cin >> grade;
    if (grade < 0 || grade > 100)
    {
        cout << RED << "Invalid Grade!\n" << RESET;
        return;
    }

    assignGrade(courseCode, studentId, grade);
    cout << GREEN << "Grade Edited Successfully.\n" << RESET;
}

/* ===================== DISPLAY ===================== */
void displayGradeByStudentId()
{
    string studentId;
    cout << "Enter Student ID: ";
    cin >> studentId;

    if (getStudentIndex(studentId) < 0)
    {
        cout << RED << "Invalid Student ID!\n" << RESET;
        return;
    }

    bool found = false;
    for (const auto& scg : studentCourseGrades)
    {
        if (scg.studentID == studentId)
        {
            cout << "Course: " << scg.courseCode
                 << " | Grade: " << scg.Grade << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No grades found for this student.\n";
}

void displayGradeByCode()
{
    string courseCode;
    cout << "Enter Course Code: ";
    cin >> courseCode;

    if (getCourseIndex(courseCode) < 0)
    {
        cout << RED << "Invalid Course Code!\n" << RESET;
        return;
    }

    bool found = false;
    for (const auto& scg : studentCourseGrades)
    {
        if (scg.courseCode == courseCode)
        {
            cout << "Student ID: " << scg.studentID
                 << " | Grade: " << scg.Grade << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No grades found for this course.\n";
}
