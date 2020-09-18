#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "ex13_9.hh"
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

const string students_input = R"(
G Droney 31 75 83 81 54 18 87 
)";


int main() {
    cout << "Starting." << endl;


    stringstream sin(students_input);


    cout << "After initial read:" << endl;
    StudentInfo rec(sin);
    cout << "name is " << rec.name() << endl;


    cout << "After self-assign:" << endl;
    rec = rec;
    cout << "name is " << rec.name() << endl;
    
    cout << "End." << endl;
    return 0;
}

