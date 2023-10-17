#ifndef UC_H
#define UC_H

#include <string>
using namespace std;

class Uc{
    public:
        Uc(string ucCode, string codeOfClass);
        string get_ucCode() const;
        string get_codeOfClass() const;
        int get_numberOfStudents() const;
        int get_maxCapacity() const;



    private:
        string ucCode_;
        string codeOfClass_;
        int numberOfStudents_;
        int maxCapacity_;

};


#endif
