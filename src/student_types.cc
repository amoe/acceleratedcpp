#include "student_types.hh"
#include "read_hw.hh"
#include "grading_functions.hh"
#include "median.hh"

using std::string;
using std::istream;
using std::min;

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

GradStudent::GradStudent(istream& is) {
    read(is);
}

istream& GradStudent::read(istream& in) {
    CoreStudent::read_common(in);
    in >> thesis;
    read_hw(in, CoreStudent::homework);
    return in;
}

double GradStudent::grade() const {
    return min(CoreStudent::grade(), thesis);
}
