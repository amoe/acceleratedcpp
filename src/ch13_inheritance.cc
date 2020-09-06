#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include "ch13_inheritance.hh"
#include "read_hw.hh"
#include "grading_functions.hh"

using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::endl;
using std::min;

bool compare(const CoreStudent& c1, const CoreStudent& c2) {
    // This will work on GradStudent and sensibly return the name.
    return c1.name() < c2.name();
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

GradStudent::GradStudent(): thesis(0) {
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

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
