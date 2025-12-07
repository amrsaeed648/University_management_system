#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "course.h"
using namespace std;
vector<Course> courses;
Course::Course(const std::string& c,
               const std::string& n,
               const std::string& p,
               const std::string& d,
               int y)
    : code(c), name(n), professor(p), department(d), year(y) {};

    // Getters
    string Course::getCode() const { return code; }
    string Course::getName() const { return name; }
    string Course::getProfessor() const { return professor; }
    string Course::getDepartment() const { return department; }
    int Course::getYear() const { return year; }
    vector<string> Course::getEnrolledStudents() const { return enrolledStudents; }

    // Setters
    void Course::setCode(const string& c) { code = c; }
    void Course::setName(const string& n) { name = n; }
    void Course::setProfessor(const string& p) { professor = p; }
    void Course::setDepartment(const string& d) { department = d; }
    void Course::setYear(int y) { year = y; }
