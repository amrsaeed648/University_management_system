#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <stdexcept>
#include "student.h"
#include "course.h"
#include "UI.h"
using namespace std;

vector<Student> students;
int Student::GlobalStudentCount = 0;

// Constructors
Student::Student () {
        GlobalStudentCount++;
        studentCount = GlobalStudentCount;
        firstName = "NULL";
        lastName = "NULL";
        id = "NULL";
        email = "NULL";
        department = "NULL";
        yearOfStudy = 0;
        idGeneration();
        emailGeneration();
}

Student::Student (string fn, string ln, string d, int yos) {
        transform(d.begin(), d.end(), d.begin(), ::toupper);
        bool validDept = (d == "GEN" || d == "CSE" || d == "ECE" || d == "POW");
        bool validYear = (yos >= 1 && yos <= 4);

        if (!validDept || !validYear) {
            string msg;
            if (!validDept) msg += "Error: Department does not exist.\n";
            if (!validYear) msg += "Error: Incorrect Academic Year.";
            throw invalid_argument(msg);
        }
        
        GlobalStudentCount++;
        studentCount = GlobalStudentCount;
        firstName = fn;
        lastName = ln;
        department = d;
        if (department == "GEN") yearOfStudy = 0;
        else yearOfStudy = yos;
        idGeneration();
        emailGeneration();
}
Student::Student(string fn, string ln, string dep, int yos, string loaded_id, string loaded_email)
{
    firstName = fn;
    lastName = ln;
    department = dep;
    yearOfStudy = yos;
    id = loaded_id;
    email = loaded_email;

    studentCount = stoi(id.substr(id.length() - 4));

    if (studentCount > GlobalStudentCount)
        GlobalStudentCount = studentCount;
}
void Student::idGeneration () // ID = XYNNNN , X = Department No, Y = Academic Year, NNNN = Student Number
{
        int dn;
        if (department == "GEN") dn = 1;
        else if (department == "CSE") dn = 2;
        else if (department == "ECE") dn = 3;
        else if (department == "POW") dn = 4;
        else dn = 0;

        id = to_string(dn) + to_string(yearOfStudy);

        if (studentCount < 9) id += "000" + to_string(studentCount);
        else if (studentCount < 99) id += "00" + to_string(studentCount);
        else if (studentCount < 999) id += "0" + to_string(studentCount);
        else id += to_string(studentCount);
}

void Student::emailGeneration () {
        string fullName = firstName + lastName;
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        email = fullName + "@uni.edu.eg";
}

// Setters
void Student::setFirstName (string s) {firstName = s;}
void Student::setLastName (string s) {lastName = s;}
void Student::setID (const string& s) { id = s; }
void Student::setEmail (const string& s) { email = s; }
void Student::setDepartment (string s) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        bool validDept = (s == "GEN" || s == "CSE" || s == "ECE" || s == "POW");
        if (validDept) {
                department = s;
                if (department == "GEN") yearOfStudy = 0;
                idGeneration(); 
        }
        else cout<<RED<<"Error: Department does not exist.\nPlease Enter Student's Data Correctly.\n"<<RESET;
}

void Student::setYearOfStudy (int s) {
        bool validYear = (s >= 1 && s <= 4);
        if (validYear) {
                if (department == "GEN") yearOfStudy = 0;
                else yearOfStudy = s;
                idGeneration();
        }
        else cout<<RED<<"Error: Incorrect Academic Year.\nPlease Enter Student's Data Correctly.\n"<<RESET;
}

void Student::setGrade(string s, double n) {
    grades.push_back({s,n});
}

//Getters
string Student::getFirstName() const { return firstName; }
string Student::getLastName() const { return lastName; }
string Student::getID() const { return id; }
string Student::getEmail() const { return email; }
string Student::getDepartment() const { return department; }
int Student::getYearOfStudy() const { return yearOfStudy; }

bool Student::foundGrades1() const
{
    if (grades.empty()) {return false;}
    return true;
}

void Student::displayGrades() const
{
    for (const auto & grade : grades)
    {
        cout<<grade.first<<" : "<<grade.second<<"\t\n";
    }
}

bool Student::foundGrades2(const string& code) const
{
    for (auto & grade : grades)
    {
        if (grade.first == code) {
            return true;
        }
    }
        return false;
}
int Student::getGradesSize() const {return grades.size();}
double Student::getGradesGrade(int n) const {return grades.at(n).second;}
string Student::getGradesCode(int n) const {return grades.at(n).first;}
void Student::displayGradesOnly(const string& code) const
{
        for (int i = 0; i < grades.size(); i++) {
            if (grades[i].first == code) {
            cout<<grades[i].second<<"\t\n";
        }
    }
}

void Student::getEnrolledCourses() const{
    if (enrolledCourses.empty()) cout<<"Student has not been enrolled to any courses";
    else {
        cout<<"Enrolled Courses: "<<enrolledCourses[0];
        for (int i = 1; i < enrolledCourses.size(); i++) {
            cout<<" , "<<enrolledCourses[i];
        }
        cout<<" .\n";
    }
}

void Student::addCourse(const string& courseCode){
        bool validcourse = validateCourse(courseCode);
        if (validcourse) {
                enrolledCourses.push_back(courseCode);
                cout << GREEN << "✅Student Enrolled Successfully.\n" << RESET;
        }
        else cout<< RED <<"Error: Incorrect Course Code.\nPlease Enter The Course Code Correctly.\n"<< RESET;
}

void Student::info() const{
    cout<<"{ "<<id<<" , "<<firstName<<" "<<lastName<<" , "<<email<<" , "<<department<<" , "<<yearOfStudy<<" }\n";
}

void Student::enrollCourse () /*number of courses wants to enroll*/ {
    cout<<"Enter How many courses u want to enroll in: ";
    int n; cin>>n;
    cout<<"\nEnter Course Code:\n";
    for (int i = 0; i < n; i++) {
        string x; cin>>x;
        addCourse(x);
    }
}


