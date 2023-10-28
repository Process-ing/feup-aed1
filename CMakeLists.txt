cmake_minimum_required(VERSION 3.10)
project(feup-aed1)

set(CMAKE_CXX_STANDARD 11)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

<<<<<<< Updated upstream
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
=======
add_executable(feup-aed1 main.cpp
        src/classes/Request.cpp
        src/classes/Request.h
        src/classes/UcClass.h
        src/classes/Dataset.cpp
        src/classes/Dataset.h
        src/classes/Student.h
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Lesson.cpp
        src/classes/Student.cpp
        src/classes/Student.cpp
        src/classes/Student.cpp
        src/classes/Student.cpp
        src/classes/Student.cpp
)
>>>>>>> Stashed changes

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