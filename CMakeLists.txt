cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/classes)

add_executable(feup-aed1
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/Student.h
        src/classes/Student.cpp
        src/classes/Lesson.h
        src/classes/UcClass.h
        src/classes/Lesson.cpp
        src/classes/Student.h
        src/classes/UcClass.cpp
)

