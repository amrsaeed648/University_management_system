#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;



class Student {
    private:
        static int GlobalStudentCount;
        string firstName, lastName, id, email, department;
        int yearOfStudy, studentCount;
        vector<string> enrolledCourses; // course codes
        vector<pair<string, double>> grades; // (courseCode, grade)

    public:
        //Setters
        Student () {
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

        Student (string fn, string ln, string d, int yos) {
            firstName = fn;
            lastName = ln;
            department = d;
            yearOfStudy = yos;
            idGeneration();
            emailGeneration();
        }

        void idGeneration () // ID = XYNNN , X = Department No, Y = YearOfStudy, XXX = Student Number
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

        void emailGeneration () {
            email = firstName + lastName + "@uni.edu.eg";
        }

        void setFirstName (string s) {firstName = s;}
        void setLastName (string s) {lastName = s;}

        // let ID & Email be server sided that cannot be modified.

        void setDepartment (string s) {
            department = s;
            idGeneration();
        }

        void setYearOfStudy (int s) {
            yearOfStudy = s;
            idGeneration();
        }

        void setGrade(string s, double x) {
            grades.push_back({s,x});
        }

        //Getters
        string getFirstName() const { return firstName; }
        string getLastName() const { return lastName; }
        string getID() const { return id; }
        string getEmail() const { return email; }
        string getDepartment() const { return department; }
        int getYearOfStudy() const { return yearOfStudy; }

        void getGrades() {
            if (grades.empty()) cout<<"No Grades Yet.\n";
            else {
                for (int i = 0; i < grades.size(); i++) {
                    cout<<grades[i].first<<" : "<<grades[i].second<<"\t\n";
                }
            }
        }

        void getEnrolledCourses() {
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
        void info() {
            cout<<"{ "<<id<<" , "<<firstName<<" "<<lastName<<" , "<<email<<" , "<<department<<" , "<<yearOfStudy<<" }";
        }

        void enrollCourse () /*number of cources wants to enroll*/ {
            cout<<"Enter How many cources u want to enroll in: ";
            int n; cin>>n;
            cout<<"\nEnter Course Code:\n";
            for (int i = 0; i < n; i++) {
                string x; cin>>x;
                enrolledCourses.push_back(x);
            }
        }


};

// ======================================= course class =======================================


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

int Student::GlobalStudentCount = 0;

/*==========================================================Start of Student Functions==============================================*/

void deleteStudent(string id) /* it deletes the student with id */ {
    int index;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getID() == id) index = i;
    }
    students.erase(students.begin() + index);
}

void studentsList() {
    for (int i = 0; i < students.size(); i++) students[i].info();
}

/*===========================================================End of Student Functions===============================================*/











int main(){
    int choice;
    while (true) {
        cout << "\n============== University Management System ==============\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Student Information\n";
        cout << "4. List All Students\n";
        cout << "5. Enroll Student in Courses\n";
        cout << "6. Add Course\n";
        cout << "7. List All Courses\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        if (choice == 1) {
            string fn, ln, dep;
            int yos;

            cout << "Enter First Name: ";
            cin >> fn;

            cout << "Enter Last Name: ";
            cin >> ln;

            cout << "Enter Department (CSE/ECE/EPE): ";
            cin >> dep;

            cout << "Enter Year of Study: ";
            cin >> yos;

            students.push_back(Student(fn, ln, dep, yos));

            cout << "Student Added Successfully!\n";
            cout << "Your ID: " << students.back().getID() << "\n";
        }

        else if (choice == 2) {
            string id;
            cout << "Enter Student ID to Delete: ";
            cin >> id;
            deleteStudent(id);
            cout << "Deleted Successfully!\n";
        }

        else if (choice == 3) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;

            bool found = false;

            for (auto &s : students) {
                if (s.getID() == id) {
                    found = true;

                    cout << "\n=== Student Information ===\n";
                    s.info();
                    cout << "\n";

                    // cout << "Enrolled Courses:\n";
                    // s.getEnrolledCourses();
                    // cout << "\nGrades:\n";
                    // s.getGrades();
                    // cout << "\n";

                    break;
                }
            }

            if (!found)
                cout << "Student not found!\n";


        }

        else if (choice == 4) {
            cout << "\n=== Students List ===\n";
            studentsList();
            cout << "\n";
        }

        else if (choice == 5) {
            string id;
            cout << "Enter Student ID to Enroll in Courses: ";
            cin >> id;

            bool found = false;
            for (auto &s : students) {
                if (s.getID() == id) {
                    found = true;
                    s.enrollCourse();
                    cout << "Enrollment Completed!\n";
                }
            }

            if (!found)
                cout << "Student not found!\n";
        }

        else if (choice == 6) {
            string code, name, prof, dep;
            int y;

            cout << "Enter Course Code: ";
            cin >> code;

            cout << "Enter Course Name: ";
            cin >> name;

            cout << "Enter Professor Name: ";
            cin >> prof;

            cout << "Enter Department: ";
            cin >> dep;

            cout << "Enter Year: ";
            cin >> y;

            courses.push_back(Course(code, name, prof, dep, y));
            cout << "Course Added!\n";
        }

        else if (choice == 7) {
            cout << "\n=== Courses List ===\n";
            for (auto &c : courses) {
                cout << "{ " << c.getCode() << " , "
                     << c.getName() << " , "
                     << c.getProfessor() << " , "
                     << c.getDepartment() << " , "
                     << c.getYear() << " }\n";
            }
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}