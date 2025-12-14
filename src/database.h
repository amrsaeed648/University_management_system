#ifndef UNIVERSITY_MANAGEMENT_SYSTEM_DATABASE_H
#define UNIVERSITY_MANAGEMENT_SYSTEM_DATABASE_H
#include "sqlite3.h"
#include "student.h"
#include "course.h"
#include "studentManagment.h"
#include <iostream>
using namespace std;

void openDatabase();
void closeDatabase();
void createStudentTable();
void saveStudentToDB(const Student& s);
void deleteStudentFromDB(const string& id);
static int loadStudentCallback(void*, int arg1, char** arg2, char**);
void loadStudentsFromDB();
void createCourseTables();
void saveCourseToDB(const Course& c);
void deleteCourseFromDB(const string& code);
static int loadCourseCallback(void*, int, char** argv, char**);
static int loadEnrollmentCallback(void*, int, char** argv, char**);
void loadCoursesFromDB();
#endif //UNIVERSITY_MANAGEMENT_SYSTEM_DATABASE_H