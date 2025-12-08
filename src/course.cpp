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
#include "student.h"
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
    vector<string> Course::getEnrolledStudents() const { return enrolledStudents; }

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
                     cout<<"Please enter course data: (Course Name, Instructor Name, Department, Academic Year)\n";
                     cout<<"Course Name : ";
                                            getline(cin,n);   cout<<"\n";
                     cout<<"Instructor Name : ";
                                            getline(cin,p);   cout<<"\n";
                     do{
                     cout<<"Enter valid departement (GEN, CSE, ECE, EPE) : ";
                                            cin>>d;           cout<<"\n";
                        }while(d!="ECE" and d!="EPE" and d!="CSE" and d!="GEN" );

                     do{
                     cout<<"Enter valid academic year (1, 2, 3, 4) : ";
                                            cin>>y;           cout<<"\n";
                        }while(y<1 || y>4);

                     cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // to solve getline problem
                     courses.push_back(Course(n,p,d,y));
                     cout<<"Course added successfully.\n";
                     string rc = ( courses.at(courseCounter) ).generateCode(d,y);   // rc -> received code
                     ( courses.at(courseCounter) ).setCode(rc);
                     cout<<"Course code is : "<<( courses.at(courseCounter) ).getCode()<<"\n"<<"\n";
                     courseCounter++;
    }

    void deleteCourse(const string& c) { // delete by code using iterator and erase function
                    bool check = false;
                    for (auto it = courses.begin(); it != courses.end(); it++) {
                    if (it->getCode() == c) {
                    check = true;
                    courses.erase(it);
                    cout << "Course deleted.\n"<<"\n";
                    break;}
                    }
                    if (!check) {cout<<"Invalid Course Code\n"<<"\n";}
    }
                    // A do while loop is required in main function

    void editCourse(const string& c) { // idicates course by code and choose what to edit (name ,year, prof, departement)

                    cout<<"Editing course code : "<<c<<"\n";
       for( auto& e  : courses) { // e -> random name for course member
           if (e.getCode() == c) {
                    cout<<"Please choose an option from the menu to modify the item you want : "<<"\n";
                    cout<<"1. Course name\n"; cout<<"2. Instructor name\n"; cout<<"3. Departement\n"; cout<<"4. Academic year\n";
                    int choice; cin>>choice;
              switch (choice) {
                    case 1:{
                         string n;
                         cout<<"Enter new course name : ";
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         getline(cin,n);
                         cout<<"Old course name is : "<<e.getName()<<"\n";
                         e.setName(n);
                         cout<<"New course name is : "<<e.getName()<<"\n";
                         cout<<"Course code is : "<<e.getCode()<<"\n";
                         break;
                    }
                    case 2:{
                         string p;
                         cout<<"Enter new instructor name : ";
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         getline(cin,p);
                         cout<<"Old instructor name is : "<<e.getProfessor()<<"\n";
                         e.setProfessor(p);
                         cout<<"New instructor name is : "<<e.getProfessor()<<"\n";
                         cout<<"Course code is : "<<e.getCode()<<"\n";
                         break;
                    }
                    case 3:{
                         string d;
                         do{
                                 cout<<"Enter new valid departement (GEN, CSE, ECE, EPE) : ";
                                 cin>>d;
                         }while(d!="ECE" and d!="EPE" and d!="CSE" and d!="GEN" );

                         cout<<"Old departement name is : "<<e.getDepartment()<<"\n";
                         e.setDepartment(d);
                         cout<<"New departement name is : "<<e.getDepartment()<<"\n"; //nc -> new code variable
                         string nc=e.getCode(); nc.replace(0,3,d); e.setCode(nc); //ex:CSE1001 -> ECE1001
                         cout<<"New course code is : "<<e.getCode()<<"\n";
                         break;
                    }
                    case 4:{
                         int y;
                         do{
                                cout<<"Enter new valid academic year (1, 2, 3, 4) : ";
                                cin>>y;
                         }while(y<1 || y>4);
                         cout<<"Old academic year is : "<<e.getYear()<<"\n";
                         e.setYear(y);
                         cout<<"New academic year is : "<<e.getYear()<<"\n";
                         string nc;
                         nc=e.getCode();
                         nc.replace(3, 1, to_string(y));
                         e.setCode(nc); //ex:CSE1001 -> CSE3001
                         cout<<"New course code is : "<<e.getCode()<<"\n";
                    }     break;

                    default: cout<<"Invalid Choice\n"<<"\n";
              }
           }
       }
    }

    void displayCourses() { // display by name and code
                     cout<<"Entered course codes : \n";
                     for ( int i = 0; i < courses.size(); i++ ) {
                     cout << (courses.at(i)).getName() << " : " << ( courses.at(i) ).getCode() << "\n";}
                     cout<<"\n"<<"\n";
    }
