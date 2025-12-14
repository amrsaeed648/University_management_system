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

    cout << "Enter Department (GEN/CSE/ECE/POW): ";
    cin >> dep;

    cout << "Enter Academic Year: ";
    cin >> yos;
    try {
        Student st(fn, ln, dep, yos);
        students.push_back(st);
        cout<< GREEN <<"✅Student Added Successfully.\n" << RESET;
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
    if (index == -1) {
        cout<< RED <<"Student Not Found!\n" << RESET;
        pauseScreen();
    }
    else {
        string input;
        Student& st = students[index];
        while (true) {
            int c;
            // cout<<"\n====================================================================================================================\n";
            cout<<"================= You are Updating "<<st.getFirstName()<<" "<<st.getLastName()<<"'S Data Now. =================\n";
            // cout<<"====================================================================================================================\n";
            cout<<"1. First Name\n2. Last Name\n3. Department\n4. Academic Year\n0. Exit\nPlease Select from Above: ";
            cin>>c; if (c == 1) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setFirstName(input);
                cout<< GREEN <<" ✅Data Updated Successfully."<< RESET;
                pauseScreen();
            }
            else if (c == 2) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setLastName(input);
                cout<< GREEN <<" ✅Data Updated Successfully."<< RESET;
                pauseScreen();
            }
            else if (c == 3) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setDepartment(input);
                cout<< GREEN <<" ✅Data Updated Successfully."<< RESET;
                pauseScreen();
            }
            else if (c == 4) {
                cout<<"Enter the New Data: "; cin>>input;
                st.setYearOfStudy(stoi(input));
                cout<< GREEN <<" ✅Data Updated Successfully."<< RESET;
                pauseScreen();
            }
            else if (c == 0) break;
            else {
                cout<< RED <<"❌Invalid Input."<< RESET; 
                pauseScreen();
            }
        }
    }
}

void deleteStudent(string id) /* it deletes the student with id */ {
    clearScreen();
    int index = getStudentIndex(id);
    if (index == -1) cout<< RED <<"❌Student Not Found!\n"<< RESET;
    else {
        students.erase(students.begin() + index);
        cout<< GREEN <<"Student Removed Successfully"<< RESET;
    }
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
        cout<< RED <<"❌Student Not Found!\n"<< RESET;
        pauseScreen();
        return;
    }

    Student &s = students[index];

    cout << "\n============== STUDENT INFORMATION ==============\n";
    cout << "👤 First Name   : " << s.getFirstName() << "\n";
    cout << "👤 Last Name    : " << s.getLastName() << "\n";
    cout << "🆔 ID           : " << s.getID() << "\n";
    cout << "📧 Email        : " << s.getEmail() << "\n";
    cout << "🏫 Department   : " << s.getDepartment() << "\n";
    cout << "📆 Academic Year: " << s.getYearOfStudy() << "\n";
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
        cout<< RED <<"❌Student Not Found!\n"<< RESET;
        pauseScreen();
        return;
    }

    cout << "📚Enter Course Code: ";
    cin >> course;

    students[index].addCourse(course);
    cout<< GREEN <<"Enrolled Successfully."<< RESET;

    pauseScreen();
}
