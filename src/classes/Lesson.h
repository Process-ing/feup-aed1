/**
 * @file Lesson.h
 * Header file for class Lesson.
 */

#ifndef FEUP_AED1_LESSON_H
#define FEUP_AED1_LESSON_H


#include <string>


/**
 * @brief Class that represents a lesson.
 */
class Lesson {
  public:
    /**
     * @brief Represents the lesson type.
     * T stands for Theoretical, TP stands for Theoretical-Practical, PL stands for Practical-Laboratory.
     */
    enum Type {T,TP,PL};

    /**
     * @brief Represents what day of the week the lesson occurs in.
     */
    enum Weekday {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

    /**
     * @brief Constructs a lesson with the given parameters.
     *
     * @param start Start time.
     * @param end End time.
     * @param type Type of lesson.
     */
    Lesson(double start, double end, Type type, Weekday weekday);

    /**
     * @brief Returns the start time.
     * @return Start time as a real number (of hours).
     */
    double getStart() const;

    /**
     * @brief Returns the end time.
     * @return End time as a real number .
     */
    double getEnd() const;

    /**
     * @brief Returns the start time formatted using formatTime().
     *
     * @return Formatted start time.
     */
    std::string getFormattedStart() const;

    /**
     * @brief Returns the end time formatted using formatTime().
     * @return Formatted end time.
     */
    std::string getFormattedEnd() const;

    /**
     * @brief Returns the type of the lesson.
     * @return Lesson type
     */
    Type getType() const;

    /**
     * @brief Returns the weekday of the lesson.
     * @return Lesson weekday.
     */
    Weekday getWeekday() const;

    /**
     * @brief Returns whether the first lesson starts before the second lesson in the week or not.
     * Complexity: O(1)
     *
     * @param lesson Lesson to compare
     * @return True if the first lesson starts before the second, false otherwise
     */
    bool operator<(const Lesson &lesson) const;

    /**
     * @brief Returns whether the current lesson overlaps with the given lesson.
     * Complexity: O(1)
     *
     * @param lesson Lesson to compare
     * @return True if one overlaps with the other,
     */
    bool overlaps(const Lesson &lesson) const;

    /**
     * @brief Returns whether the current lesson can be overlapped with the other, based on their types.
     * Two lessons can be overlapped if they are neither TP or PL.
     * Complexity: O(1)
     *
     * @param lesson Lesson to compare
     * @return True if they are compatible, false otherwise.
     */
    bool isCompatibleWith(const Lesson& lesson) const;

    /**
     * @brief Returns the time in format HH:mm.
     *
     * @param time Time as real number of hours.
     * @return Formatted time
     */
    static std::string formatTime(double time);

  private:
    double start_;
    double end_;
    Type type_;
    Weekday weekday_;
};

#endif //FEUP_AED1_LESSON_H