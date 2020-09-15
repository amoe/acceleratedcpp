#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "ex13_3.hh"
#include "read_hw.hh"
#include "grading_functions.hh"

using std::max;
using std::streamsize;
using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::endl;
using std::min;
using std::setprecision;
using std::sort;
using std::stringstream;

bool compare(const CoreStudent& c1, const CoreStudent& c2) {
    return c1.name() < c2.name();
}

bool compare_grades(const CoreStudent& c1, const CoreStudent& c2) {
    return c1.grade() < c2.grade();
}

bool compare_ptr(CoreStudent* c1, CoreStudent* c2) {
    return compare_grades(*c1, *c2);
}

CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
}

CoreStudent::CoreStudent(istream& is) {
    read(is);
}


string CoreStudent::name() const {
    return n;
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

bool CoreStudent::valid() const {
    cout << "  CoreStudent::valid()" << endl;
    return !homework.empty();
}

GradStudent::GradStudent(): thesis(0) {
    
}

bool GradStudent::valid() const {
    cout << "   GradStudent::valid()" << endl;
    return CoreStudent::valid() && thesis != 0;
}

// Note: If we called CoreStudent(is) here as the base class, the behaviour
// would be wrong.  We implicitly call the default constructor.
GradStudent::GradStudent(istream& is) {
    read(is);
}

istream& GradStudent::read(istream& in) {
    // Directly using the scope operator to refer to members from the parent
    // class.
    CoreStudent::read_common(in);
    in >> thesis;
    read_hw(in, CoreStudent::homework);
    return in;
}

// "The student receives the lesser of the grade ontained on the thesis and the
// grade that would have been obtained if we just counted the exams and homework
// scores."
double GradStudent::grade() const {
    return min(CoreStudent::grade(), thesis);
}

const string corestudents_only = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";

const string gradstudents_only = R"(
Droney 31 75 83 81 54 18 87 
Zutell 99 99 26 99 99 99 99 
)";


int main() {
    cout << "Starting." << endl;

    stringstream core_ss(corestudents_only);
    stringstream grad_ss(gradstudents_only);
    
    CoreStudent s1(core_ss);
    cout << "s1 is valid? " << (s1.valid() ? "true" : "false") << endl;

    CoreStudent s2;
    cout << "s2 is valid? " << (s2.valid() ? "true" : "false") << endl;

    GradStudent s3(grad_ss);
    cout << "s3 is valid? " << (s3.valid() ? "true" : "false") << endl;

    GradStudent s4;
    cout << "s4 is valid? " << (s4.valid() ? "true" : "false") << endl;

    cout << "End." << endl;
    return 0;
}
