#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "student.h"
#include "course.h"
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
        GlobalStudentCount++;
        studentCount = GlobalStudentCount;
        firstName = fn;
        lastName = ln;
        transform(d.begin(), d.end(), d.begin(), ::toupper);
        department = d;
        if (department == "GEN") yearOfStudy = 0;
        else yearOfStudy = yos;
        idGeneration();
        emailGeneration();
}

void Student::idGeneration () // ID = XYNNNN , X = Department No, Y = YearOfStudy, NNNN = Student Number
{
        int dn;
        if (department == "GEN") dn = 1;
        else if (department == "CSE") dn = 2;
        else if (department == "ECE") dn = 3;
        else if (department == "EPE") dn = 4;
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
void Student::setID(const string& s) { id = s; }
void Student::setEmail(const string& s) { email = s; }

void Student::setDepartment (string s) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        department = s;
        if (department == "GEN") yearOfStudy = 0;
        idGeneration();
}

void Student::setYearOfStudy (int s) {
        if (department == "GEN") yearOfStudy = 0;
        else yearOfStudy = s;
        idGeneration();
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
void Student::getGrades() const
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
void Student::getGradesOnly(const string& code) const
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
    enrolledCourses.push_back(courseCode);
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
         enrolledCourses.push_back(x);
     }
 }


