#include <iostream>
#include <vector>
#include "ex13_2.hh"
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"

using std::istream;
using std::vector;
using std::cout;
using std::endl;

CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
    cout << "  CoreStudent::CoreStudent()" << endl;
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

    
    // Should call CoreStudent::CoreStudent()
    CoreStudent* p1 = new CoreStudent;

    // CoreStudent* p2 = new GradStudent;
    // CoreStudent s1;
    // GradStudent s2;
    
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
