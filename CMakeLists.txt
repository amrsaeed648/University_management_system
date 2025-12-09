cmake_minimum_required(VERSION 4.0)
project(University_management_system)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(University_management_system
        src/course.cpp
        src/course.h
        src/gradeResultsManagment.cpp
        src/gradeResultsManagment.h
        src/main.cpp
        src/student.cpp
        src/student.h
        src/studentManagment.cpp
        src/studentManagment.h
        src/studentManagmentMenu.cpp
        src/studentManagmentMenu.h
        src/courseManagementMenu.cpp
        src/courseManagementMenu.h
        src/gradeManagementMenu.h
        src/gradeManagementMenu.cpp)
