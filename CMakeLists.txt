cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

link_directories(src/classes/)

add_executable(feup-aed1 main.cpp
        src/classes/Request.cpp
        src/classes/Request.h
        src/classes/UcClass.h
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/Student.h
)

<<<<<<< HEAD
add_subdirectory(docs)
=======
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

add_executable(feup-aed1 app/main.cpp
        src/classes/UcClass.cpp
        src/classes/UcClass.cpp
        ../untitled/UcReader.cpp
        ../untitled/UcReader.cpp
        src/classes/Lesson.h
        src/classes/Dataset.h
        src/classes/Dataset.cpp
)
>>>>>>> feature/dataset-ucclass
