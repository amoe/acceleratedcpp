#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include <algorithm>
#include "ex13_5.hh"
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"

using std::find;
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
Capener 7 10 32 0 61 76
)";

const string gradstudents_only = R"(
Droney 31 75 83 81 54 18 87 
Zutell 99 99 26 99 0 99 99 
Jervis 99 99 0 99 99 99 99 
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

CoreStudent::operator bool() const {
    vector<double>::const_iterator found = find(
        homework.begin(), homework.end(), 0
    );

    return found == homework.end();
}

GradStudent::operator bool() const {
    // This looks REALLY WEIRD but it's actually fine.
    // Note that whether 'operator bool()' is virtual doesn't matter at all here.
    // There's no polymorphism involved, just inheritance.
    bool result = CoreStudent::operator bool();
    return result && thesis != 0;
}

int main() {
    cout << "Starting." << endl;

    stringstream core_ss(corestudents_only);
    stringstream grad_ss(gradstudents_only);
    
    CoreStudent s1(core_ss);
    CoreStudent s2(core_ss);
    GradStudent s3(grad_ss);
    GradStudent s4(grad_ss);
    GradStudent s5(grad_ss);

    cout << "s1: " << (s1 ? "true" : "false") << endl;
    cout << "s2: " << (s2 ? "true" : "false") << endl;
    cout << "s3: " << (s3 ? "true" : "false") << endl;
    cout << "s4: " << (s4 ? "true" : "false") << endl;
    cout << "s5: " << (s5 ? "true" : "false") << endl;

    cout << "End." << endl;
    return 0;
}
