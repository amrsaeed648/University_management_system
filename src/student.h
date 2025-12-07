#ifndef GIT_STUDENT_H
#define GIT_STUDENT_H
using namespace std;
#include <string>
#include <vector>
class Student {
private:
    static int GlobalStudentCount;
    string firstName, lastName, id, email, department;
    int yearOfStudy, studentCount;
    vector<string> enrolledCourses; // course codes
    vector<pair<string, double>> grades; // (courseCode, grade)

public:
    Student ();
    Student (string fn, string ln, string d, int yos);
    void idGeneration ();
    void emailGeneration ();
    void setFirstName (string s);
    void setLastName (string s);
    void setID(const string& newID);
    void setEmail(const string& newEmail);
    void setDepartment (string s);
    void setYearOfStudy (int s);
    void setGrade(string s, double x);
    string getFirstName() const;
    string getLastName() const;
    string getID() const;
    string getEmail() const;
    string getDepartment() const;
    int getYearOfStudy() const;
    void getGrades() ;
    void getEnrolledCourses();
    void info();
    void enrollCourse ();
};
extern vector<Student> students;
#endif //GIT_STUDENT_H