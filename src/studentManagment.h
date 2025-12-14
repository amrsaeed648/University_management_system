#ifndef UNIVERSITY_PROGRAM_STUDENTMANAGMENT_H
#define UNIVERSITY_PROGRAM_STUDENTMANAGMENT_H

#include <string>

class Student;

// Student management
int getStudentIndex(std::string id);
void addStudent();
void updateStudent(std::string id);
void deleteStudent(std::string id);
void studentsList();
void showStudentInfo(std::string id);
void enrollStudentInCourse();

// Database (SQLite)
void openDatabase();
void closeDatabase();
void createStudentTable();
void saveStudentToDB(const Student& s);
void deleteStudentFromDB(const std::string& id);
void loadStudentsFromDB();

#endif // UNIVERSITY_PROGRAM_STUDENTMANAGMENT_H
