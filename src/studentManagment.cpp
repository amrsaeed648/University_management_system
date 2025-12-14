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
#include "sqlite3.h"
#include "course.h"
#include "studentManagment.h"
#include "UI.h"

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
    cout << "Enter First Name: ";
    cin >> fn;

    cout << "Enter Last Name: ";
    cin >> ln;

    cout << "Enter Department (GEN/CSE/ECE/POW): ";
    cin >> dep;

    cout << "Enter Academic Year: ";
    cin >> yos;
    try {
        Student st(fn, ln, dep, yos);
        students.push_back(st);
        saveStudentToDB(st);
        cout<<"Student Added Successfully.\n";
        cout<<"Student ID is: "<<st.getID()<<" .\n";
        cout<<"Student Email is: "<<st.getEmail()<<" .\n";
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    pauseScreen();
}

void updateStudent(string id) {
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        pauseScreen();
        return;
    }

    Student& st = students[index];

    while (true) {
        clearScreen();
        cout << "================= Updating " << st.getFirstName() << " " << st.getLastName() << " =================\n";
        cout << "1. First Name\n"
             << "2. Last Name\n"
             << "3. Department\n"
             << "4. Year of Study\n"
             << "0. Exit\n"
             << "Select: ";

        int c;
        cin >> c;

        if (c == 0) break;

        string input;
        try {
            switch (c) {
                case 1:
                    cout << "New First Name: ";
                    cin >> input;
                    st.setFirstName(input);
                    break;

                case 2:
                    cout << "New Last Name: ";
                    cin >> input;
                    st.setLastName(input);
                    break;

                case 3:
                    cout << "New Department: ";
                    cin >> input;
                    st.setDepartment(input);
                    break;

                case 4:
                    cout << "New Year of Study: ";
                    cin >> input;
                    st.setYearOfStudy(stoi(input));
                    break;

                default:
                    cout << "Invalid choice\n";
                    pauseScreen();
                    continue;
            }

            saveStudentToDB(st);

            cout << "Data Updated Successfully\n";
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        pauseScreen();
    }
}

void deleteStudent(string id) {
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        pauseScreen();
        return;
    }
    deleteStudentFromDB(id);

    students.erase(students.begin() + index);

    cout << "Student Deleted Successfully\n";
    pauseScreen();
}

void studentsList() {
    clearScreen();
    printBanner();
    cout<< BOLD << "\n======================= Student List =======================\n" << RESET;
    for (int i = 0; i < students.size(); i++) students[i].info();
    pauseScreen();
}



void showStudentInfo(string id)
{
    clearScreen();
    printBanner();
    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout<< RED <<"❌Student Not Found!\n"<< RESET;
        pauseScreen();
        return;
    }

    Student &s = students[index];

    cout << "\n============== STUDENT INFORMATION ==============\n";
    cout << "First Name   : " << s.getFirstName() << "\n";
    cout << "Last Name    : " << s.getLastName() << "\n";
    cout << "ID           : " << s.getID() << "\n";
    cout << "Email        : " << s.getEmail() << "\n";
    cout << "Department   : " << s.getDepartment() << "\n";
    cout << "Academic Year: " << s.getYearOfStudy() << "\n";
    cout << "=================================================\n";
    pauseScreen();
}

void enrollStudentInCourse()
{
    clearScreen();
    printBanner();
    string id, course;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout << "Student Not Found!\n";
        return;
    }

    cout << "Enter Course Code: ";
    cin >> course;

    students[index].addCourse(course);
    cout<< GREEN <<"Enrolled Successfully."<< RESET;

    pauseScreen();
}

/* ===================== SQLITE ===================== */


sqlite3* db = nullptr;

void openStudentDatabase() {
    int exit = sqlite3_open("students.db", &db);
    if (exit != SQLITE_OK) {
        cout << "Cannot open database\n";
        db = nullptr;
    }
}

void closeStudentDatabase() {
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

