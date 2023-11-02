/**
 * @file utils.h
 * Header file with useful functions for sorting and alike.
 */

#ifndef FEUP_AED1_UTILS_H
#define FEUP_AED1_UTILS_H

#include <vector>
#include "Student.h"

/**
 * @brief Sorts a vector of students by name in alphabetical order.
 * It is based on STL's sort function.
 * Complexity: O(n*log(n)), where n is students.size()
 * @param students Vector of students to sort.
 */
void sortByAlphabeticalOrder(std::vector<Student>& students);

/**
 * @brief Sorts a vector of students by name in reverse alphabetical order.
 * It is based on STL's sort function.
 * Complexity: O(n*log(n)), where n is students.size().
 * @param students Vector of students to sort.
 */
void sortByReverseAlphabeticalOrder(std::vector<Student>& students);

/**
 * @brief Sorts a vector of students by ascending number of UC's they are enrolled in.
 * It is based on STL's sort function.
 * Complexity: O(n*log(n)), where n is students.size().
 * @param students Vector of students to sort.
 */
void sortByAscendingNumOfUcs(std::vector<Student>& students);

/**
 * @brief Sorts a vector of students by descending number of UC's they are enrolled in.
 * It is based on STL's sort function.
 * Complexity: O(n*log(n)), where n is students.size().
 * @param students Vector of students to sort.
 */
void sortByDescendingNumOfUcs(std::vector<Student>& students);


#endif //FEUP_AED1_UTILS_H
