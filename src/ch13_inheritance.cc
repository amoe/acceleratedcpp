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

// The 3rd item is the thesis grade.  A really low thesis grade should
// "dominate" a very good set of homework grades, hence Zutell should
// be sorted to the top (the lowest effective grade).
const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
)";

int main() {
    cout << "Starting." << endl;

    vector<CoreStudent*> students;
    CoreStudent* rec;
    string::size_type maxlen = 0;

    stringstream sin(students_input);
    char type_code;
    while (sin >> type_code) {
        if (type_code == 'U') {
            rec = new CoreStudent(sin);
        } else {
            // XXX tweak me
            rec = new GradStudent(sin);
        }
        maxlen = max(maxlen, rec->name().size());
        students.push_back(rec);
    }

    cout << "Read " << students.size() << " records" << endl;

    sort(students.begin(), students.end(), compare_ptr);

    for (vector<CoreStudent*>::size_type i = 0; i < students.size(); i++) {
        CoreStudent* this_student = students[i];
        cout << this_student->name()
             << string((maxlen + 1) - this_student->name().size(), ' ');

        try {
            double final_grade = this_student->grade();
            streamsize prec = cout.precision();

            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (std::domain_error& e) {
            cout << e.what();
        }

        cout << endl;

        delete this_student;
    }


    cout << "End." << endl;
    return 0;
}

