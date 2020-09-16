#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"
#include "ex13_6.hh"

using std::min;
using std::string;
using std::stringstream;
using std::cerr;
using std::istream;
using std::cout;
using std::endl;
using std::vector;

const string corestudents_only = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";

// The second student did no homework.
const string passfailstudent_only = R"(
Ottem 94 89 14 96 16 63
Hellen 50 50
)";


CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
}

CoreStudent::CoreStudent(istream& is) {
    read(is);

}
double CoreStudent::grade() const {
    return ::grade(midterm_grade, final_grade, homework);
}

istream& CoreStudent::read_common(istream& in) {
    in >> n >> midterm_grade >> final_grade;
    return in;
}

istream& CoreStudent::read(istream& in) {
    read_common(in);
    read_hw(in, homework);
    return in;
}


int main() {
    cout << "Starting." << endl;

    // stringstream pfs_ss(passfailstudent_only);
    // PassFailStudent s1(pfs_ss);
    // PassFailStudent s2(pfs_ss);

    

    cout << "End." << endl;
    return 0;
}
