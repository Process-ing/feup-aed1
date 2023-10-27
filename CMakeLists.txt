cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

add_executable(feup-aed1 main.cpp
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/Student.h
        src/classes/UcClass.h
)
add_subdirectory(docs)