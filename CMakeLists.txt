cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/classes)

add_executable(feup-aed1 main.cpp
        src/classes/Student.h
        src/classes/Student.cpp
        src/classes/Lesson.h
        src/classes/UcClass.h
        src/classes/Lesson.cpp
)

add_subdirectory(docs)