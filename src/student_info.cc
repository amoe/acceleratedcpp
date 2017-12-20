#include <iostream>
#include "student_info.hh"

using std::istream;
using std::vector;

istream& read_hw(istream& in, vector<double>& hw) {
    // this "if" check is essential, because we don't check it in the main
    // program
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

// read a single line of input into a StudentInfo object that the caller owns.
// we can reuse the previous function that we used to read the homework scores
istream& read(istream& is, StudentInfo& s) {
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.homework);

    return is;
}

// this will be used as a third argument to std::sort to compare studentinfo
// by grade, not sure about performance here... schwartzian transform?
// Actually we only need to do it by name, so ... yay
bool lessThan(const StudentInfo& x, const StudentInfo& y) {
    return x.name < y.name;
}
