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

    animatedPrint( "Enter Course Code: ");
    cin >> courseCode;
    if (getCourseIndex(courseCode) < 0)
    {
        animatedPrint(RED "Invalid Course Code!\n"  RESET);
        return;
    }

    animatedPrint( "Enter Student ID: ");
    cin >> studentId;
    if (getStudentIndex(studentId) < 0)
    {
        animatedPrint(RED  "Invalid Student ID!\n"  RESET);
        return;
    }

    int gradeIndex = findGradeIndex(courseCode, studentId);
    if (gradeIndex == -1)
    {
        animatedPrint( RED "Student is NOT enrolled in this course.\n" RESET) ; pauseScreen();
        return;
    }

    animatedPrint( "Enter Grade (0 -> 100): ");
    cin >> grade;
    if (grade < 0 || grade > 100)
    {
        animatedPrint(RED "Invalid Grade!\n" RESET ); pauseScreen();
        return;
    }

    assignGrade(courseCode, studentId, grade);
    animatedPrint( GREEN  "Grade Assigned Successfully.\n" RESET); pauseScreen();
}

void userEditGrade()
{

    string courseCode, studentId;
    int grade;

    animatedPrint( "Enter Course Code: ");
    cin >> courseCode;
    if (getCourseIndex(courseCode) < 0)
    {
        animatedPrint(RED  "Invalid Course Code!\n"  RESET );
        return;
    }

    animatedPrint( "Enter Student ID: ");
    cin >> studentId;
    if (getStudentIndex(studentId) < 0)
    {
        animatedPrint( RED  "Invalid Student ID!\n"  RESET);
        return;
    }

    int gradeIndex = findGradeIndex(courseCode, studentId);
    if (gradeIndex == -1)
    {
        animatedPrint( RED  "Student is NOT enrolled in this course.\n"  RESET );
        return;
    }

    animatedPrint("Enter New Grade (0 -> 100): ");
    cin >> grade;
    if (grade < 0 || grade > 100)
    {
        animatedPrint( RED  "Invalid Grade!\n"  RESET);
        return;
    }

    assignGrade(courseCode, studentId, grade);
   animatedPrint( GREEN  "Grade Edited Successfully.\n"  RESET);
}

/* ===================== DISPLAY ===================== */
void displayGradeByStudentId()
{

    string studentId;
    animatedPrint( "Enter Student ID: ");
    cin >> studentId;

    if (getStudentIndex(studentId) < 0)
    {
        animatedPrint( RED "Invalid Student ID!\n" RESET);
        return;
    }

    bool found = false;
    for (const auto& scg : studentCourseGrades)
    {
        if (scg.studentID == studentId)
        {
            animatedPrint( "Course: " + scg.courseCode +
                  " | Grade: " + to_string(scg.Grade) + "\n");
            found = true;
        }
        /*pauseScreen();*/
    }
    if (!found)
        animatedPrint( "No grades found for this student.\n"); pauseScreen();
}

void displayGradeByCode()
{

    string courseCode;
    animatedPrint( "Enter Course Code: ");
    cin >> courseCode;

    if (getCourseIndex(courseCode) < 0)
    {
        animatedPrint( RED  "Invalid Course Code!\n"  RESET);
        return;
    }

    bool found = false;
    for (const auto& scg : studentCourseGrades)
    {
        if (scg.courseCode == courseCode)
        {
            animatedPrint( "Student ID: " + scg.studentID +
                 + " | Grade: " + to_string(scg.Grade) + "\n");
            found = true;
        }
    }
    /*pauseScreen();*/

    if (!found)
        animatedPrint( RED "No grades found for this course.\n"  RESET);
}
