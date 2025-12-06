#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "student.h"

        // constructors
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
            yearOfStudy = yos;
            idGeneration();
            emailGeneration();
        }

        void Student::idGeneration () // ID = XYNNN , X = Department No, Y = YearOfStudy, XXX = Student Number
        {
            int dn;
            if (department == "CSE") dn = 1;
            else if (department == "ECE") dn = 2;
            else if (department == "EPE") dn = 3;
            else dn = 0;

            id = to_string(dn) + to_string(yearOfStudy);

            if (studentCount < 9) id += "00" + to_string(studentCount);
            else if (studentCount < 99) id += "0" + to_string(studentCount);
            else id += to_string(studentCount);
        }

        void Student::emailGeneration () {
            string fullName = firstName + lastName;
            transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
            email = fullName + "@uni.edu.eg";
        }

        // setters
        void Student::setFirstName (string s) {firstName = s;}
        void Student::setLastName (string s) {lastName = s;}

        void Student::setID(const string& newID)      { id = newID; }
        void Student::setEmail(const string& newEmail){ email = newEmail; }

        void Student::setDepartment (string s) {
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            department = s;
            idGeneration();
        }

        void Student::setYearOfStudy (int s) {
            yearOfStudy = s;
            idGeneration();
        }

        void Student::setGrade(string s, double x) {
            grades.push_back({s,x});
        }

        //Getters
        string Student::getFirstName() const { return firstName; }
        string Student::getLastName() const { return lastName; }
        string Student::getID() const { return id; }
        string Student::getEmail() const { return email; }
        string Student::getDepartment() const { return department; }
        int Student::getYearOfStudy() const { return yearOfStudy; }

        void Student::getGrades() {
            if (grades.empty()) cout<<"No Grades Yet.\n";
            else {
                for (int i = 0; i < grades.size(); i++) {
                    cout<<grades[i].first<<" : "<<grades[i].second<<"\t\n";
                }
            }
        }

        void Student::getEnrolledCourses() {
            if (enrolledCourses.empty()) cout<<"Student has not been enrolled to any courses";
            else {
                cout<<"Enrolled Courses: "<<enrolledCourses[0];
                for (int i = 1; i < enrolledCourses.size(); i++) {
                    cout<<" , "<<enrolledCourses[i];
                }
                cout<<" .\n";
            }
        }



        //Functions
        void Student::info() {
            cout<<"{ "<<id<<" , "<<firstName<<" "<<lastName<<" , "<<email<<" , "<<department<<" , "<<yearOfStudy<<" }\n";
        }

        void Student::enrollCourse () /*number of cources wants to enroll*/ {
            cout<<"Enter How many cources u want to enroll in: ";
            int n; cin>>n;
            cout<<"\nEnter Course Code:\n";
            for (int i = 0; i < n; i++) {
                string x; cin>>x;
                enrolledCourses.push_back(x);
            }
        }