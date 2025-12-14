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

void saveStudents() {
    clearScreen();
    ofstream fout("students.txt");

    fout << students.size() << "\n";
    for (auto &s : students) {
        fout << s.getFirstName() << " "
             << s.getLastName() << " "
             << s.getDepartment() << " "
             << s.getYearOfStudy() << " "
             << s.getID() << " "
             << s.getEmail() << " ";
        fout << s.getGradesSize() << " ";
        for (int i=0;i<s.getGradesSize();i++)
        {
            fout << s.getGradesCode(i)<< " " << s.getGradesGrade(i) << " ";
        }
        fout << "\n";
    }

    fout.close();
}

// Load students from file
void loadStudents()
{
    ifstream fin("students.txt");
    if (!fin) return;

    int count;
    fin >> count;

    for (int i = 0; i < count; i++) {
        string fn, ln, dep, email, id;
        int yos;

        fin >> fn >> ln >> dep >> yos >> id >> email;
        Student temp(fn, ln, dep, yos, id, email);
        int gradesCount;
        fin >> gradesCount;

        for (int j=0; j<gradesCount;j++)
        {
            string code;
            double grade;

            fin >> code >> grade;
            temp.setGrade(code, grade);
        }
        students.push_back(temp);
    }
    fin.close();
};

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
    cout << "🆔Enter Student ID: ";
    cin >> id;

    int index = getStudentIndex(id);
    if (index == -1)
    {
        cout << "❌Student Not Found!\n";
        return;
    }

    cout << "📚Enter Course Code: ";
    cin >> course;

    students[index].addCourse(course);

    pauseScreen();
}
