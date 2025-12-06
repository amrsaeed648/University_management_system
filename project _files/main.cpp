#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;


/*============================================================Start of Student Class=================================================*/

class Student {
    private:
        static int GlobalStudentCount;
        string firstName, lastName, id, email, department;
        int yearOfStudy, studentCount;
        vector<string> enrolledCourses; // course codes
        vector<pair<string, double>> grades; // (courseCode, grade)

    public:
        // constructors
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

        // setters
        void setFirstName (string s) {firstName = s;}
        void setLastName (string s) {lastName = s;}

        void setID(const string& newID)      { id = newID; }
        void setEmail(const string& newEmail){ email = newEmail; }

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
            cout<<"{ "<<id<<" , "<<firstName<<" "<<lastName<<" , "<<email<<" , "<<department<<" , "<<yearOfStudy<<" }\n";
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

/*============================================================End of Student Class=================================================*/




/*============================================================Start of Course Class=================================================*/

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

/*=============================================================End of Course Class==================================================*/




/*==========================================================Start of Program Variables==============================================*/

vector<Student> students;
vector<Course> courses;

int Student::GlobalStudentCount = 0;

/*===========================================================End of Program Variables===============================================*/




/*==========================================================Start of Student Functions==============================================*/

int getStudentIndex(string id) { return stoi(id.substr(2))-1; }

void addStudent () {
    string fn, ln, d;
    int yos;
    cout<<"Please Enter Student Data: (First Name, Last Name, Department, Year of Study)\n";
    cin>>fn>>ln>>d>>yos;
    Student st(fn, ln, d, yos);
    students.push_back(st);
    cout<<"Student Added Successfully.\n";
    cout<<"His ID is: "<<st.getID()<<" .\n";
    cout<<"His Email is: "<<st.getEmail()<<" .\n";
}

void updateStudent(string id) {
    int index = getStudentIndex(id);
    string input; 
    Student& st = students[index]; 
    while (true) { 
        int c; 
        cout<<"\n====================================================================================================================\n"; 
        cout<<"================= You are Updating "<<st.getFirstName()<<" "<<st.getLastName()<<"'S Data Now. =================\n"; 
        cout<<"====================================================================================================================\n"; 
        cout<<"1. First Name\n2. Last Name\n3. Department\n4. Year of Study\n5. Exit\nPlease Select from Above: "; 
        cin>>c; if (c == 1) {
            cout<<"Enter the New Data: "; cin>>input; 
            st.setFirstName(input); 
            cout<<" Data Updated Successfully."; 
        }
        else if (c == 2) {
            cout<<"Enter the New Data: "; cin>>input; 
            st.setLastName(input); 
            cout<<" Data Updated Successfully."; 
        }
        else if (c == 3) {
            cout<<"Enter the New Data: "; cin>>input; 
            st.setDepartment(input); 
            cout<<" Data Updated Successfully."; 
        }
        else if (c == 4) {
            cout<<"Enter the New Data: "; cin>>input; 
            st.setYearOfStudy(stoi(input)); 
            cout<<" Data Updated Successfully."; 
        }
        else if (c == 5) break; 
        else cout<<"Invalid Input."; 
    } 
}

void deleteStudent(string id) /* it deletes the student with id */ {
    int index = getStudentIndex(id);
    students.erase(students.begin() + index);
}

void studentsList() {
    for (int i = 0; i < students.size(); i++) students[i].info();
}

void saveStudents() {
    ofstream fout("students.txt");

    fout << students.size() << "\n";
    for (auto &s : students) {
        fout << s.getFirstName() << " "
             << s.getLastName() << " "
             << s.getDepartment() << " "
             << s.getYearOfStudy() << " "
             << s.getID() << " "
             << s.getEmail() << "\n";
    }

    fout.close();
}

// Load students from file
void loadStudents() {
    ifstream fin("students.txt");
    if (!fin) return;

    int count;
    fin >> count;

    for (int i = 0; i < count; i++) {
        string fn, ln, dep, email, id;
        int yos;

        fin >> fn >> ln >> dep >> yos >> id >> email;
        Student temp(fn, ln, dep, yos);

        temp.setID(id);
        temp.setEmail(email);

        students.push_back(temp);
    }

    fin.close();
}

/*===========================================================End of Student Functions===============================================*/











int main(){

    loadStudents();

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
            saveStudents();
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