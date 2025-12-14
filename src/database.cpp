#include "sqlite3.h"
#include "database.h"
#include "student.h"
#include "course.h"
#include "studentManagment.h"
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

void deleteStudentFromDB(const string& id) {
    string sql = "DELETE FROM students WHERE id='" + id + "';";
    char* errMsg = nullptr;
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
}

/* ===================== LOAD ===================== */

static int loadCallback(void*, int arg1, char** arg2, char**) {
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

void loadStudentsFromDB() {
    students.clear();

    const char* sql =
        "SELECT id, first_name, last_name, department, year, email FROM students;";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, loadCallback, nullptr, &errMsg) != SQLITE_OK) {
        cout << "Load failed: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

