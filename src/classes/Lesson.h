/**
 * Header file for class Lesson.
 */

#ifndef FEUP_AED1_LESSON_H
#define FEUP_AED1_LESSON_H
#include <utility>


class Lesson {
public:
    /**
     * @brief Represents the lesson type.
     * @author João Mendes
     * @details T stands for Theoretical, TP stands for Theoretical-Practical, PL stands for Practical-Laboratory.
     */
    enum Type {T,TP,PL};
    /**
     * @brief Represents what day of the week the lesson occurs in.
     * @author João Mendes
     */
    enum Weekday {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
    /**
     * @brief Constructor
     * @author João Mendes
     * @param start Represents the start hour.
     * @param end Represents the end hour.
     * @param type Represents what type of lesson it is.
     */
    Lesson(std::pair<int, int> start, std::pair<int, int> end, Type type, Weekday weekday);
    /**
     * @brief Returns a pair of ints representing the start hour.
     * @author João Mendes
     * @return Pair of ints, with the first representing the hour and the second representing the minutes.
     */
    std::pair<int, int> getStart() const;
    /**
     * @brief Returns a pair of ints representing the start hour.
     * @author João Mendes
     * @return Pair of ints, with the first representing the hour and the second representing the minutes.
     */
    std::pair<int, int> getEnd() const;

    Type getType() const;
    Weekday getWeekday() const;
    /**
     * @brief Returns whether the current lesson starts before the given lesson or not.
     * @author João Mendes
     * @param lesson Lesson to compare
     */
    bool operator<(const Lesson &lesson);
    /**
     * @brief Returns whether the current lesson overlaps with the given lesson.
     * @author João Mendes
     * @param lesson Lesson to compare
     */
    bool overlaps(const Lesson &lesson);
private:
    std::pair<int, int> start_;
    std::pair<int, int> end_;
    Type type_;
    Weekday weekday_;
};

#endif //FEUP_AED1_LESSON_H
