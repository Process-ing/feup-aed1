cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

link_directories(src/classes/)

add_executable(feup-aed1 main.cpp
        src/classes/Request.cpp
        src/classes/Request.h
        src/classes/UcClass.h
        src/classes/Dataset.h
        src/classes/Student.h)

add_subdirectory(docs)