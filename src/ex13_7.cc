#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"
#include "ex13_7.hh"

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

const string auditstudents_only = R"(
Pyne
Hebert
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

string CoreStudent::name() const {
    return n;
}

AuditStudent::AuditStudent(istream& in) {
    read(in);
}

istream& AuditStudent::read(istream& in) {
    in >> n;
    return in;
}

double AuditStudent::grade() const {
    return 0;
}

int main() {
    cout << "Starting." << endl;

    stringstream as_ss(auditstudents_only);
    AuditStudent s1(as_ss);

    cout << "name: " << s1.name() << endl;
    cout << "grade: " << s1.grade() << endl;

    cout << "End." << endl;
    return 0;
}
