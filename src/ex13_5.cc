#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include "ex13_5.hh"
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"

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

const string gradstudents_only = R"(
Droney 31 75 83 81 54 18 87 
Zutell 99 99 26 99 99 99 99 
)";


CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
    cerr << "    CoreStudent::CoreStudent()" << endl;
}

CoreStudent::CoreStudent(istream& is) {
    cerr << "    CoreStudent::CoreStudent(istream&)" << endl;
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

GradStudent::GradStudent(): thesis(0) {
    cerr << "    GradStudent::GradStudent()" << endl;
}

GradStudent::GradStudent(istream& is) {
    cerr << "    GradStudent::GradStudent(istream&)" << endl;
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

int main() {
    cout << "Starting." << endl;
    cout << "End." << endl;
    return 0;
}
