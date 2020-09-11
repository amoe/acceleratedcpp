#include <iostream>
#include <numeric>
#include <vector>
#include "ex13_2.hh"
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"

using std::min;
using std::istream;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;

CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
    cerr << "  CoreStudent::CoreStudent()" << endl;
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
    cerr << "  GradStudent::GradStudent()" << endl;
}

GradStudent::GradStudent(istream& is) {
    cerr << "  GradStudent::GradStudent(istream&)" << endl;
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

    
    // Should call CoreStudent::CoreStudent() ✓
    CoreStudent* p1 = new CoreStudent;

    // Should call CoreStudent::CoreStudent, then GradStudent::GradStudent() ✓
    CoreStudent* p2 = new GradStudent;
    
    // Should call CoreStudent::CoreStudent() ✓
    CoreStudent s1;
    
    // Should call CoreStudent::CoreStudent, then GradStudent::GradStudent() ✓
    GradStudent s2;
    
    // p1->grade();
    // p1->name();
    // p2->grade();
    // p2->name();
    // s1.grade();
    // s1.name();
    // s2.name();
    // s2.grade();

    
    cout << "End." << endl;
    return 0;
}
