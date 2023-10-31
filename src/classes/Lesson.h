/**
 * Header file for class Lesson.
 */

#ifndef FEUP_AED1_LESSON_H
#define FEUP_AED1_LESSON_H


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
    enum Weekday {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};
    /**
     * @brief Constructor
     * @author João Mendes
     * @param start Represents the start hour.
     * @param end Represents the end hour.
     * @param type Represents what type of lesson it is.
     */
    Lesson(double start, double end, Type type, Weekday weekday);

    double getStart() const;
    double getEnd() const;
    Type getType() const;
    Weekday getWeekday() const;
    /**
     * @brief Returns whether the current lesson starts before the given lesson or not.
     * @author João Mendes
     * @param lesson Lesson to compare
     */
    bool operator<(const Lesson &lesson) const;
    /**
     * @brief Returns whether the current lesson overlaps with the given lesson.
     * @author João Mendes
     * @param lesson Lesson to compare
     */
    bool overlaps(const Lesson &lesson) const;
private:
    double start_;
    double end_;
    Type type_;
    Weekday weekday_;
};

#endif //FEUP_AED1_LESSON_H
