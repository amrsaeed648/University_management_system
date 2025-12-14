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
    cout << "Enter First Name: ";
    cin >> fn;

    cout << "Enter Last Name: ";
    cin >> ln;

    cout << "Enter Department (GEN/CSE/ECE/EPE): ";
    cin >> dep;

    cout << "Enter Year of Study: ";
    cin >> yos;
    try {
        Student st(fn, ln, dep, yos);
        students.push_back(st);
        saveStudentToDB(st);
        cout<<"✅Student Added Successfully.\n";
        cout<<"🆔Student ID is: "<<st.getID()<<" .\n";
        cout<<"📧Student Email is: "<<st.getEmail()<<" .\n";
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    pauseScreen();
}

void updateStudent(string id) {
    clearScreen();
    int index = getStudentIndex(id);
    if (index == -1) cout<<"Student Not Found!\n";
    else {
        string input;
        Student& st = students[index];
        while (true) {
            int c;
            // cout<<"\n====================================================================================================================\n";
            cout<<"================= You are Updating "<<st.getFirstName()<<" "<<st.getLastName()<<"'S Data Now. =================\n";
            // cout<<"====================================================================================================================\n";
            cout<<"1. First Name\n2. Last Name\n3. Department\n4. Year of Study\n0. Exit\nPlease Select from Above: ";
            cin>>c; if (c == 1) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setFirstName(input);
                cout<<" ✅Data Updated Successfully.";
                pauseScreen();
            }
            else if (c == 2) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setLastName(input);
                cout<<" ✅Data Updated Successfully.";
                pauseScreen();
            }
            else if (c == 3) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setDepartment(input);
                cout<<" ✅Data Updated Successfully.";
                pauseScreen();
            }
            else if (c == 4) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setYearOfStudy(stoi(input));
                cout<<" ✅Data Updated Successfully.";
                pauseScreen();
            }
            else if (c == 0) break;
            else {cout<<"❌Invalid Input."; pauseScreen();}
        }
    }
}

void deleteStudent(string id) /* it deletes the student with id */ {
    clearScreen();
    int index = getStudentIndex(id);
    if (index == -1) cout<<"❌Student Not Found!\n";
    else students.erase(students.begin() + index);
    pauseScreen();
}

void studentsList() {
    clearScreen();
    for (int i = 0; i < students.size(); i++) students[i].info();
    pauseScreen();
}



void showStudentInfo(string id)
{
    clearScreen();
    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout << "❌Student Not Found!\n";
        return;
    }

    Student &s = students[index];

    cout << "\n============== STUDENT INFORMATION ==============\n";
    cout << "👤 First Name   : " << s.getFirstName() << "\n";
    cout << "👤 Last Name    : " << s.getLastName() << "\n";
    cout << "🆔 ID           : " << s.getID() << "\n";
    cout << "📧 Email        : " << s.getEmail() << "\n";
    cout << "🏫 Department   : " << s.getDepartment() << "\n";
    cout << "📆 Year of Study: " << s.getYearOfStudy() << "\n";
    cout << "=================================================\n";
    pauseScreen();
}

void enrollStudentInCourse()
{
    clearScreen();
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

    pauseScreen();
}

/* ===================== SQLITE ===================== */


sqlite3* db = nullptr;

void openDatabase() {
    int exit = sqlite3_open("students.db", &db);
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

