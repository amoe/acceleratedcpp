#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include "ex13_2.hh"
#include "read_hw.hh"
#include "median.hh"

using std::string;
using std::min;
using std::istream;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


double grade(double midterm, double final, const vector<double>& hw) {
    // Technically wrong but we can't throw in this exercise as we don't want
    // to abort the program.
    if (hw.size() == 0) {
        return 0;
    }

    return grade(midterm, final, median(hw));
}


CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
    cerr << "  CoreStudent::CoreStudent()" << endl;
}

double CoreStudent::grade() const {
    cerr << "  CoreStudent::grade()" << endl;
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
    cerr << "  CoreStudent::name()" << endl;
    return n;
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
    cerr << "  GradStudent::grade()" << endl;
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

    // Should call CoreStudent::grade()
    p1->grade();

    // Should call CoreStudent::name()
    p1->name();

    // Should call GradStudent::grade(), then (explicitly) CoreStudent::grade().
    p2->grade();

    // Should call CoreStudent::name() as there's no implementation for GradStudent.
    // Note that it doesn't matter that `name` isn't virtual.
    p2->name();

    // Should call CoreStudent::grade()
    s1.grade();
    
    // Should call CoreStudent::name()
    s1.name();

    // Should call CoreStudent::name() as again no implementation for Grad.
    s2.name();

    // Should call GradStudent::grade(), then (explicitly) CoreStudent::grade().
    // It doesn't matter that this isn't a polymorphic call, GradStudent::grade
    // can still call down to its base class method.
    s2.grade();
    
    cout << "End." << endl;
    return 0;
}
