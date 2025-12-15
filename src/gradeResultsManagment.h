#ifndef UNIVERSITY_PROGRAM_GRADE_RESULTS_FUN_H
#define UNIVERSITY_PROGRAM_GRADE_RESULTS_FUN_H
#include <vector>
using namespace std;
struct studentCourseGrade
{
    string studentID;
    string courseCode;
    double Grade;
};
extern vector<studentCourseGrade> studentCourseGrades;
void assignGrade (const string& courseCode, const string& studentId, const int grade);
void userAssignGrade ();
void userEditGrade ();
void displayGradeByStudentId ();
void displayGradeByCode ();
void displayCoursesByStudentId();

#endif //UNIVERSITY_PROGRAM_GRADE_RESULTS_FUN_H
