#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "ch13_inheritance.hh"
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
    // This will work on GradStudent and sensibly return the name.
    return c1.name() < c2.name();
}

bool compare_grades(const CoreStudent& c1, const CoreStudent& c2) {
    return c1.grade() < c2.grade();
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

// Note: If we called CoreStudent(is) here as the base class, the behaviour
// would be wrong.  We implicitly call the default constructor.
GradStudent::GradStudent(istream& is) {
    read(is);
}

istream& GradStudent::read(istream& in) {
    // Directly using the scope operator to refer to members from the parent
    // class.
    CoreStudent::read_common(in);
    in >> thesis;
    read_hw(in, CoreStudent::homework);
    return in;
}

// "The student receives the lesser of the grade ontained on the thesis and the
// grade that would have been obtained if we just counted the exams and homework
// scores."
double GradStudent::grade() const {
    return min(CoreStudent::grade(), thesis);
}

const string students_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";

const string grad_students_input = R"(
Zutell 31 75 81 54 18 87 83
Droney 10 45 37 22 74 70 26
)";

int main() {
    cout << "Starting." << endl;

    vector<CoreStudent> students;
    CoreStudent rec1;
    string::size_type maxlen = 0;

    stringstream sin1(students_input);
    while (rec1.read(sin1)) {
        maxlen = max(maxlen, rec1.name().size());
        students.push_back(rec1);
    }

    GradStudent rec2;
    stringstream sin2(grad_students_input);
    while (rec2.read(sin2)) {
        maxlen = max(maxlen, rec2.name().size());
        students.push_back(rec2);
    }

    sort(students.begin(), students.end(), compare);

    for (vector<CoreStudent>::size_type i = 0; i < students.size(); i++) {
        CoreStudent this_student = students[i];
        cout << this_student.name()
             << string((maxlen + 1) - this_student.name().size(), ' ');

        try {
            double final_grade = this_student.grade();
            streamsize prec = cout.precision();

            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (std::domain_error& e) {
            cout << e.what();
        }

        cout << endl;
    }


    cout << "End." << endl;
    return 0;
}

