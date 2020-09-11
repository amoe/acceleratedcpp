#include <iostream>
#include <vector>
#include "ex13_1.hh"
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"

using std::cerr;
using std::istream;
using std::cout;
using std::endl;
using std::vector;

    // CoreStudent();
    // CoreStudent(std::istream&);
    // GradStudent();
    // GradStudent(std::istream&);

CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
    cerr << "CoreStudent::CoreStudent()" << endl;
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

    // Default constructor
    CoreStudent s1;
    
    cout << "End." << endl;
    return 0;
}
