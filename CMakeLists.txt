cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

file(COPY dataset DESTINATION)

include_directories(${PROJECT_SOURCE_DIR}/src/classes)

add_executable(feup-aed1 main.cpp
        src/classes/Request.cpp
        src/classes/Request.h
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/UcClass.h
        src/classes/UcClass.cpp
        src/classes/Student.h
        src/classes/Student.cpp
        src/classes/Lesson.h
        src/classes/Lesson.cpp
)

add_subdirectory(docs)
