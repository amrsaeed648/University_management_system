cmake_minimum_required(VERSION 4.0)
project(University_Program)

set(CMAKE_CXX_STANDARD 20)

add_executable(University_Program
        main.cpp
        student.cpp
	course.cpp
		gradeResultsManagment.cpp
		studentManagment.cpp
		UI.cpp
		studentManagmentMenu.cpp
		gradeManagementMenu.cpp
)