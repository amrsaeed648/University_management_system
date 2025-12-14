#include "sqlite3.h"
#include "database.h"
#include "student.h"
#include "course.h"
#include "studentManagment.h"
#include "gradeResultsManagment.h"
#include <iostream>
using namespace std;
sqlite3* db = nullptr;

void openDatabase() {
    int exit = sqlite3_open("database.db", &db);
    if (exit != SQLITE_OK) {
        cout << "Cannot open database\n";
        db = nullptr;
    }
}

void closeDatabase() {
    if (db) sqlite3_close(db);
}

void createStudentTable() {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS students ("
        "id TEXT PRIMARY KEY,"
        "first_name TEXT,"
        "last_name TEXT,"
        "department TEXT,"
        "year INTEGER,"
        "email TEXT);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Table error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
void createCourseTables() {
    const char* courseTable =
        "CREATE TABLE IF NOT EXISTS courses ("
        "code TEXT PRIMARY KEY,"
        "name TEXT,"
        "professor TEXT,"
        "department TEXT,"
        "year INTEGER);";

    const char* enrollmentTable =
        "CREATE TABLE IF NOT EXISTS course_students ("
        "course_code TEXT,"
        "student_id TEXT,"
        "PRIMARY KEY (course_code, student_id));";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, courseTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Course table error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    if (sqlite3_exec(db, enrollmentTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Enrollment table error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}


/* ===================== SAVE / DELETE ===================== */

void saveStudentToDB(const Student& s) {
    string sql =
        "INSERT OR REPLACE INTO students VALUES ('" +
        s.getID() + "','" +
        s.getFirstName() + "','" +
        s.getLastName() + "','" +
        s.getDepartment() + "'," +
        to_string(s.getYearOfStudy()) + ",'" +
        s.getEmail() + "');";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Save failed: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
void saveCourseToDB(const Course& c) {
    // Save course info
    string sql =
        "INSERT OR REPLACE INTO courses VALUES ('" +
        c.getCode() + "','" +
        c.getName() + "','" +
        c.getProfessor() + "','" +
        c.getDepartment() + "'," +
        to_string(c.getYear()) + ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Save course failed: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    // Clear old enrollments/grades for this course
    string del = "DELETE FROM course_students WHERE course_code='" + c.getCode() + "';";
    sqlite3_exec(db, del.c_str(), nullptr, nullptr, nullptr);

    // Save new enrollments/grades for this course using studentCourseGrades struct
    for (const auto& scg : studentCourseGrades) {
        if (scg.courseCode == c.getCode()) {
            string ins =
                "INSERT INTO course_students (course_code, student_id, grade) VALUES ('" +
                scg.courseCode + "','" + scg.studentID + "'," + to_string(scg.Grade) + ");";
            sqlite3_exec(db, ins.c_str(), nullptr, nullptr, nullptr);
        }
    }
}

void deleteStudentFromDB(const string& id) {
    string sql = "DELETE FROM students WHERE id='" + id + "';";
    char* errMsg = nullptr;
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
}

void deleteCourseFromDB(const string& code) {
    string sql1 = "DELETE FROM courses WHERE code='" + code + "';";
    string sql2 = "DELETE FROM course_students WHERE course_code='" + code + "';";

    sqlite3_exec(db, sql1.c_str(), nullptr, nullptr, nullptr);
    sqlite3_exec(db, sql2.c_str(), nullptr, nullptr, nullptr);
}

/* ===================== LOAD ===================== */

static int loadStudentCallback(void*, int arg1, char** arg2, char**) {
    string id    = arg2[0];
    string fn    = arg2[1];
    string ln    = arg2[2];
    string dep   = arg2[3];
    int yos      = stoi(arg2[4]);
    string email = arg2[5];

    Student s(fn, ln, dep, yos);
    s.setID(id);
    s.setEmail(email);

    students.push_back(s);
    return 0;
}
static int loadCourseCallback(void*, int, char** argv, char**) {
    Course c;
    c.setCode(argv[0]);
    c.setName(argv[1]);
    c.setProfessor(argv[2]);
    c.setDepartment(argv[3]);
    c.setYear(stoi(argv[4]));

    courses.push_back(c);
    return 0;
}

static int loadstudentCourseGradesCallback(void*, int argc, char** argv, char**) {
    if (argc < 3) return 0; // ensure we have enough columns

    studentCourseGrade scg;
    scg.courseCode = argv[0];
    scg.studentID  = argv[1];
    scg.Grade      = stod(argv[2]); // convert string to double

    studentCourseGrades.push_back(scg);

    return 0;
}


void loadStudentsFromDB() {
    students.clear();

    const char* sql =
        "SELECT id, first_name, last_name, department, year, email FROM students;";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, loadStudentCallback, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Load failed: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void loadCoursesFromDB() {
    courses.clear();

    char* errMsg = nullptr;

    const char* courseSQL =
        "SELECT code, name, professor, department, year FROM courses;";

    if (sqlite3_exec(db, courseSQL, loadCourseCallback, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Load courses failed: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    const char* enrollSQL =
        "SELECT course_code, student_id FROM course_students;";

    sqlite3_exec(db, enrollSQL, loadstudentCourseGradesCallback, nullptr, nullptr);
}

