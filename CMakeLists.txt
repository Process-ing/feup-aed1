cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/classes)

add_executable(feup-aed1
        main.cpp
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/Student.cpp
        src/classes/Lesson.cpp
        src/classes/UcClass.cpp
        src/classes/Request.cpp
        src/classes/Request.h
        src/classes/Student.h
)

add_subdirectory(docs)

# Doxygen build configuration (if needed)
find_package(Doxygen)
if(DOXYGEN_FOUND)
        message("Doxygen build started")
        add_custom_target(Doxygen ALL
                COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
else(DOXYGEN_FOUND)
        message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)