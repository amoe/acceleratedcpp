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

// StudentInfo -- handle class

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

// The 3rd item is the thesis grade.  A really low thesis grade should
// "dominate" a very good set of homework grades, hence Zutell should
// be sorted to the top (the lowest effective grade).
const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
)";

const string corestudents_only = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";

const string gradstudents_only = R"(
Droney 31 75 83 81 54 18 87 
Zutell 99 99 26 99 99 99 99 
)";


void demo_read_students() {
    vector<StudentInfo> students;
    string::size_type maxlen = 0;

    stringstream sin(students_input);
    StudentInfo rec;
    while (rec.read(sin)) {
        maxlen = max(maxlen, rec.name().size());
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

void demo_thing() {
    stringstream sin(corestudents_only);
    CoreStudent rec1;
    rec1.read(sin);
    
    CoreStudent& r = rec1;

    cout << "grade of rec1 is " << r.grade() << endl;
    
    r.regrade(100);

    cout << "new grade of rec1 is " << r.grade() << endl;

    // Compile error as expected -- regrade(double, double) is only
    // defined on GradStudent.
    //r.regrade(100, 100);

    stringstream sin2(gradstudents_only);
    GradStudent rec2;
    rec2.read(sin2);

    cout << "rec2 (grad student): Old grade is " << rec2.grade() << endl;
    
    // Works because GradStudent has the method defined.
    rec2.regrade(100, 100);

    cout << "rec2 (grad student): New grade is " << rec2.grade() << endl;

    stringstream sin3(gradstudents_only);
    GradStudent rec3;
    rec3.read(sin3);

    CoreStudent& ref2 = rec3;

    // Still a compile error as we should expect.  The virtual status of
    // CoreStudent::regrade(double) does not affect whether this works or not.
    // It is always a compile error because virtual calls need to exactly match.
    //ref2.regrade(100, 100);
    
    GradStudent& ref3 = rec3;
    
    // A compile error... but why?
    // It seems like this method should be inherited, but:
    // "Even though there is a base-class version that takes a single argument,
    // that version is effectively hidden by the existence of 'regrade' in the
    // derived class."
    // This would definitely not happen in java!
    //ref3.regrade(100);


    // But you can use this bonkers syntax to call the base class version:
    ref3.CoreStudent::regrade(100);
}

int main() {
    cout << "Starting." << endl;

    demo_read_students();
    demo_thing();

    cout << "End." << endl;
    return 0;
}

