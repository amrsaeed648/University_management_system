#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {
private:
    string firstName, lastName, id, email, department;
    int yearOfStudy;
    vector<string> enrolledCourses; // course codes
    vector<pair<string, double>> grades; // (courseCode, grade)

public:
    Student(const string& fn="", const string& ln="", const string& i="", const string& e="", const string& d="", int y=0)
        : firstName(fn), lastName(ln), id(i), email(e), department(d), yearOfStudy(y) {}


    // Getters
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getId() const { return id; }
    string getEmail() const { return email; }
    string getDepartment() const { return department; }
    int getYearOfStudy() const { return yearOfStudy; }
    vector<string> getEnrolledCourses() const { return enrolledCourses; }
    vector<pair<string, double>> getGrades() const { return grades; }


    // Setters
    void setFirstName(const string& fn) { firstName = fn; }
    void setLastName(const string& ln) { lastName = ln; }
    void setId(const string& i) { id = i; }
    void setEmail(const string& e) { email = e; }
    void setDepartment(const string& d) { department = d; }
    void setYearOfStudy(int y) { yearOfStudy = y; }


};


class Course {
private:
    string code, name, professor, department;
    int year;
    vector<string> enrolledStudents; // student IDs

public:
    Course(const string& c="", const string& n="", const string& p="", const string& d="", int y=0)
        : code(c), name(n), professor(p), department(d), year(y) {}



    // Getters
    string getCode() const { return code; }
    string getName() const { return name; }
    string getProfessor() const { return professor; }
    string getDepartment() const { return department; }
    int getYear() const { return year; }
    vector<string> getEnrolledStudents() const { return enrolledStudents; }

    // Setters
    void setCode(const string& c) { code = c; }
    void setName(const string& n) { name = n; }
    void setProfessor(const string& p) { professor = p; }
    void setDepartment(const string& d) { department = d; }
    void setYear(int y) { year = y; }

};



vector<Student> students;
vector<Course> courses;


int main(){

    return 0;
}
