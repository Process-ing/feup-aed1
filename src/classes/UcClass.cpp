    #include "UcClass.h"

    UcClass::UcClass(string uc_code, string code_of_class, vector<Lesson> lessons) {
        this->uc_code_ = uc_code;
        this->code_of_class_ = code_of_class;
        this->lessons_ = lessons;
        this->number_of_students_ = 0;
        this->max_capacity_ = 0;
    }

    string UcClass::getUcCode() {
        return uc_code_;
    }

    string UcClass::getCodeOfClass(){
        return code_of_class_;
    }

    int UcClass::getNumberOfStudents() {
        return number_of_students_;
    }

    int UcClass::getMaxCapacity() {
        return max_capacity_;
    }

    void UcClass::setMaxCapacity(int new_max_capacity) {
        max_capacity_ = new_max_capacity;
    }

    void UcClass::setNumberOfStudents(int new_number_of_students) {
        number_of_students_ = new_number_of_students;
    }

    vector<Lesson> UcClass::getLessons(){
        return lessons_;
    }
    /**
    * @brief Adds a lesson to the class
    * @param lesson
    * @author Diogo Vieira
    */
    void UcClass::addLesson(Lesson lesson) {
        lessons_.push_back(lesson);
    }
    /**
    * @brief Less-than comparison operator for UcClass objects.
    * This operator overloads the '<' operator to compare two UcClass objects based on their `uc_code_` member variable.
    * @param other The UcClass object to compare with.
    * @return True if this UcClass's `uc_code_` is less than the `uc_code_` of the other UcClass, false otherwise.
    * @author Diogo Vieira
    */
    bool UcClass::operator<(const UcClass& other) const {
        return uc_code_ < other.uc_code_;
    }

