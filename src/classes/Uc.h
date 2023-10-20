#ifndef UC_H
#define UC_H

#include <string>
using namespace std;

class Uc{
    public:
        /**
         * Parameterized constructor for Uc
         * @param ucCode
         * @param codeOfClass
         * @author Diogo Vieira
         */
        Uc(string ucCode, string codeOfClass);

        /**
         * @brief ucCode getter
         * @return ucCode
         * @author Diogo Vieira
         */
        string get_ucCode() const;

        /**
         * @brief codeOfClass getter
         * @return codeOfClass
         * @author Diogo Vieira
         */
        string get_codeOfClass() const;

        /**
         * @brief numberOfStudents getter
         * @return numberOfStudents
         * @author Diogo Vieira
         */
        int get_numberOfStudents() const;

        /**
         * @brief maxCapacity getter
         * @return maxCapacity
         * @author Diogo Vieira
         */
        int get_maxCapacity() const;

        /**
         * @brief numberOfStudents establishment
         * @param newNumberOfStudents
         * @author Diogo Vieira
         */
        void set_numberOfStudents(int newNumberOfStudents);

        /**
         * @brief maxCapacity establishment
         * @param newMaxCapacity
         * @author Diogo Vieira
         */
        void set_maxCapacity(int newMaxCapacity);
private:
        string ucCode_;
        string codeOfClass_;
        int numberOfStudents_;
        int maxCapacity_;

};


#endif
