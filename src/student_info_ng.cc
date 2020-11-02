#include <iostream>
#include "student_info_ng.hh"

using std::istream;

istream& StudentInfo::read(istream& is) {
    delete student;
    
    char ch;
    is >> ch;

    if (ch == 'U') {
        student = new CoreStudent(is);
    } else {
        student = new GradStudent(is);
    }

    return is;
}
