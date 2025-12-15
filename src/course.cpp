#include <algorithm>
#include <cmath>
#include <limits> //to solve getline problem
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "course.h"
#include "database.h"
#include "student.h"
#include "studentManagment.h"
#include "UI.h"
#include "gradeResultsManagment.h"
using namespace std;
vector<Course> courses;
Course::Course( const string& n,
                const string& p,
                const string& d,
                int y)
    : name(n), professor(p), department(d), year(y) {};

    // Getters
    string Course::getCode() const { return code; }
    string Course::getName() const { return name; }
    string Course::getProfessor() const { return professor; }
    string Course::getDepartment() const { return department; }
    int Course::getYear() const { return year; }

    // Setters
    void Course::setCode(const string& c) { code = c; }
    void Course::setName(const string& n) { name = n; }
    void Course::setProfessor(const string& p) { professor = p; }
    void Course::setDepartment(const string& d) { department = d; }
    void Course::setYear(int y) { year = y; }

    // Global Course Counter
                             static int courseCounter = 0;      // stays alive entire program
    // Class Functions

    string Course::generateCode(const string& d, int y) { //Code = department name + year + number of course XXXYIII
                     string c ;
                     c = d + to_string(y);
                     if (courseCounter < 9) c += "00" + to_string(courseCounter);
                     else if (courseCounter < 99) c += "0" + to_string(courseCounter);
                     else c += to_string(courseCounter);
                     return c;
    }
    //  Out Of Class Functions
    void addCourse() {
                     string n,p,d; int y;
                     animatedPrint("Please enter course data: (Course Name, Instructor Name, Department, Academic Year)\n");
                     cout<<"Course Name : ";
                                            getline(cin,n);   cout<<"\n";
                     animatedPrint("Instructor Name : ");

                                            getline(cin,p);   cout<<"\n";
                     do{
                     animatedPrint("Enter valid department (GEN, CSE, ECE, POW) : ");
                                            cin>>d;   string temp =convertToUpper(d); d=temp;        cout<<"\n";
                        }while(d!="ECE" and d!="POW" and d!="CSE" and d!="GEN" );

                     do{
                     animatedPrint("Enter valid academic year (1, 2, 3, 4) : ");
                                            cin>>y;           cout<<"\n";
                        }while(y<1 || y>4);

                     cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // to solve getline problem
                     courses.push_back(Course(n,p,d,y));
                     (courses.back()).setCode((courses.back()).generateCode(d, y));
                     saveCourseToDB(courses.back());
                     animatedPrint(GREEN"Course added successfully\n" RESET);
                     animatedPrint("Course code is : "+( courses.at(courseCounter) ).getCode()+"\n"+"\n");
                     courseCounter++;
                     pauseScreen();
    }

void deleteCourse(const string& c) {
        // 1. Remove the course from the courses vector
        bool foundCourse = false;
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if (it->getCode() == c) {
                courses.erase(it);
                foundCourse = true;
                break;
            }
        }

        if (!foundCourse) {
            animatedPrint(RED "Invalid Course Code\n""\n" RESET);
            pauseScreen();
            return;
        }

        // 2. Remove all grades related to this course from studentCourseGrades
        for (auto it = studentCourseGrades.begin(); it != studentCourseGrades.end();) {
            if (it->courseCode == c) {
                it = studentCourseGrades.erase(it); // erase returns next iterator
            } else {
                ++it;
            }
        }
        saveAllGradesToDB();
        // 3. Feedback
        animatedPrint(GREEN "Course and related grades deleted successfully.\n""\n" RESET);
        pauseScreen();
    }
                    // A do while loop is required in main function

    void editCourse(const string& c) { // indicates course by code and choose what to edit (name ,year, prof, department)
            clearScreen();
            printBanner();
            animatedPrint("Editing course code : "+c+"\n");
       for( auto& e  : courses) { // e -> random name for course member
           if (e.getCode() == c) {
                    animatedPrint("Please choose an option from the menu to modify the item you want :\n");
                    animatedPrint("1. Course name\n"); animatedPrint("2. Instructor name\n");
                    animatedPrint("3. Department\n"); animatedPrint("4. Academic year\n");
                    int choice; cin>>choice;
              switch (choice) {
                    case 1:{
                         clearScreen();
                         printBanner();
                         string n;
                         animatedPrint("Enter new course name : ");
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         getline(cin,n);
                         animatedPrint("Old course name is : "+e.getName()+"\n");
                         e.setName(n);
                         animatedPrint(GREEN "New course name is : "+e.getName()+"\n" RESET);
                         animatedPrint("Course code is : "+e.getCode()+"\n");
                       pauseScreen();
                         return;
                    }
                    case 2:{
                        clearScreen();
                        printBanner();
                         string p;
                         animatedPrint("Enter new instructor name : ");
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         getline(cin,p);
                        animatedPrint("Old instructor name is : "+e.getProfessor()+"\n");
                         e.setProfessor(p);
                         animatedPrint(GREEN "New instructor name is : "+e.getProfessor()+"\n" RESET);
                         animatedPrint("Course code is : "+e.getCode()+"\n");
                        pauseScreen();
                         return;
                    }
                    case 3:{
                        clearScreen();
                        printBanner();
                         string d;
                         do{
                                 animatedPrint("Enter new valid department (GEN, CSE, ECE, POW) : ");
                                 cin>>d; string temp =convertToUpper(d); d=temp;
                         }while(d!="ECE" and d!="POW" and d!="CSE" and d!="GEN" );

                         animatedPrint("Old department name is : "+e.getDepartment()+"\n");
                         e.setDepartment(d);
                         animatedPrint("New department name is : "+e.getDepartment()+"\n"); //nc -> new code variable
                         string nc=e.getCode(); nc.replace(0,3,d); e.setCode(nc); //ex:CSE1001 -> ECE1001
                         animatedPrint(GREEN "New course code is : "+e.getCode()+"\n" RESET);
                        pauseScreen();
                         return;
                    }
                    case 4:{
                        clearScreen();
                        printBanner();
                         int y;
                         do{
                                animatedPrint("Enter new valid academic year (1, 2, 3, 4) : ");
                                cin>>y;
                         }while(y<1 || y>4);
                         animatedPrint("Old academic year is : "+to_string(e.getYear())+"\n");
                         e.setYear(y);
                         animatedPrint(GREEN "New academic year is : "+to_string(e.getYear())+"\n" RESET );
                         string nc;
                         nc=e.getCode();
                         nc.replace(3, 1, to_string(y));
                         e.setCode(nc); //ex:CSE1001 -> CSE3001
                         animatedPrint("New course code is : "+e.getCode()+"\n");
                        pauseScreen();
                        return;
                    }

                    default: animatedPrint(RED "Invalid choice.\n""\n" RESET); pauseScreen();
              }
               return;
           }

       }
        animatedPrint(RED "Invalid course code.\n" RESET); pauseScreen();
    }

    void displayCourses() { // display by name and code
                     animatedPrint("Entered courses : \n");
                     for (auto & course : courses) {
                     animatedPrint( "{"+course.getName() + ", " +course.getCode() + ", "+course.getProfessor()+"}\n");}
                     cout<<"\n"<<"\n"; pauseScreen();
    }
int getCourseIndex(string code) // gives the Index of the Course
{
        for (int i = 0; i < courses.size(); i++) {
            if ( ( courses.at(i) ).getCode() == code)
                return i;
        }
        return -1; // Not found
}

bool validateCourse(string code) // Course Existence Validation
{
        for (int i = 0; i < courses.size(); i++) {
            if ( ( courses.at(i) ).getCode() == code)
                return true;
        }
        return false; // Not found
}