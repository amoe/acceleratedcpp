#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "ex13_8.hh"
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

PassFailStudent::PassFailStudent(istream& is) {
    read(is);
}

double PassFailStudent::grade() const {
    double result;
    
    if (homework.empty()) {
        result = (midterm_grade + final_grade) / 2;
    } else {
        result = CoreStudent::grade();
    }

    return result;
}

// StudentInfo -- handle class

istream& StudentInfo::read(istream& is) {
    delete student;
    
    char ch;
    is >> ch;

    cout << "Read identifying char '" << ch << "'"
         << " (ascii val is " << (int) ch << ")" << endl;
    
    // It's important that we handle every case here.
    // A failure to allocate here will cause a failure to push_back() onto
    // the vector.
    // It will also mean that the contents of 'rec' does NOT get overwritten by
    // this loop, so the contents of the StudentInfo record will be the same
    // but student will be a null pointer (having already been deleted) and thus
    // won't be able to be copied.

    if (ch == 'U') {
        student = new CoreStudent(is);
    } else if (ch == 'G') {
        student = new GradStudent(is);
    } else if (ch == 'P') {
        student = new PassFailStudent(is);
    } else {
        student = new AuditStudent(is);
    }

    return is;
}

// The 3rd item is the thesis grade.  A really low thesis grade should
// "dominate" a very good set of homework grades, hence Zutell should
// be sorted to the top (the lowest effective grade).
const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
A Pyne
A Hebert
P Ottem 94 89 14 96 16 63
P Hellen 50 50
)";


void demo_read_students() {
    vector<StudentInfo> students;
    string::size_type maxlen = 0;

    stringstream sin(students_input);
    StudentInfo rec;
    while (rec.read(sin)) {
        string name = rec.name();
        cout << "name is " << name << endl;
        maxlen = max(maxlen, name.size());
        students.push_back(rec);
    }

    cout << "Read " << students.size() << " records" << endl;

    // Sort is going to call the assignment operator a lot!
    // Hence the assignment operator must be correctly implemented
    // and must copy its managed contents.
    // This is a perfect example of the rule of three.
    sort(students.begin(), students.end(), StudentInfo::compare);
    
    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        // This will copy the student.
        StudentInfo this_student(students[i]);
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

        // The copy of the student is freed here.
    }
}

int main() {
    cout << "Starting." << endl;

    demo_read_students();

    cout << "End." << endl;
    return 0;
}

