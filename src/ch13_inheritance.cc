#include <iostream>
#include <string>
#include <vector>
#include "ch13_inheritance.hh"
#include "read_hw.hh"
#include "grading_functions.hh"

using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::endl;


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

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
