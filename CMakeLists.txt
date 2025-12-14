cmake_minimum_required(VERSION 4.0)
project(University_management_system)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(src)

add_executable(University_management_system
        src/main.cpp
        src/student.cpp
        src/student.h
        src/studentManagment.cpp
        src/studentManagment.h
        src/studentManagmentMenu.cpp
        src/studentManagmentMenu.h
        src/course.cpp
        src/course.h
        src/courseManagementMenu.cpp
        src/courseManagementMenu.h
        src/gradeResultsManagment.cpp
        src/gradeResultsManagment.h
        src/gradeManagementMenu.cpp
        src/gradeManagementMenu.h

        src/UI.cpp
        src/UI.h

        src/sqlite3.c
)