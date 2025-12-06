#ifndef GIT_COURSE_H
#define GIT_COURSE_H
using namespace std;
class Course
{
private:
    string code, name, professor, department;
    int year;
    vector<string> enrolledStudents; // student IDs

public:
    Course(const std::string& c = "",
               const std::string& n = "",
               const std::string& p = "",
               const std::string& d = "",
               int y = 0);
    string getCode() const;
    string getName() const;
    string getProfessor() const;
    string getDepartment() const;
    int getYear() const;
    vector<string> getEnrolledStudents() const;
    void setCode(const string& c);
    void setName(const string& n);
    void setProfessor(const string& p);
    void setDepartment(const string& d);
    void setYear(int y);
};
#endif //GIT_COURSE_H