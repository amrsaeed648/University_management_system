#ifndef GIT_COURSE_H
#define GIT_COURSE_H
using namespace std;
#include <string>
#include <vector>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
class Course
{
private:
    string code, name, professor, department;
    int year;
    vector<string> enrolledStudents; // student IDs

public:
    Course(    const string& n = "",
               const string& p = "",
               const string& d = "",
               int y = 0);

    string getCode() const;
    string getName() const;
    string getProfessor() const;
    string getDepartment() const;
    int getYear() const;

    vector<string> &getEnrolledStudents();

    void setCode(const string& c);
    void setName(const string& n);
    void setProfessor(const string& p);
    void setDepartment(const string& d);
    void setYear(int y);

   string generateCode (const string& d, int y);
};
void addCourse();
void deleteCourse(const string& c);
void editCourse(const string& c);
void displayCourses();
int getCourseIndex(string code);
bool validateCourse(string code);
string convertToUpper(string str);
void saveCourses();
void loadCourses();

extern vector<Course> courses;
#endif //GIT_COURSE_H
