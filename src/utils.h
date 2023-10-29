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

#endif //FEUP_AED1_UTILS_H
