#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "read_hw.hh"
#include "median.hh"
#include "grading_functions.hh"
#include "ex13_8.hh"

using std::setprecision;
using std::sort;
using std::max;
using std::streamsize;
using std::min;
using std::string;
using std::stringstream;
using std::cerr;
using std::istream;
using std::cout;
using std::endl;
using std::vector;
using std::runtime_error;

const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99
)";


CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
}

CoreStudent::CoreStudent(istream& is) {
    read(is);

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

string CoreStudent::name() const {
    return n;
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

AuditStudent::AuditStudent(istream& in) {
    cout << "constructing auditstudent" << endl;
    read(in);
}

istream& AuditStudent::read(istream& in) {
    in >> n;
    return in;
}

double AuditStudent::grade() const {
    return 0;
}


istream& StudentInfo::read(istream& is) {
    delete student;
    
    char ch = 0;
    is >> ch;


    if (ch == '\0') {
        return is;    // EOF!
    } else if (ch == 'U') {
        student = new CoreStudent(is);
    } else if (ch == 'G') {
        student = new GradStudent(is);
    } else if (ch == 'A') {
        student = new AuditStudent(is);
    } else {
        throw runtime_error("bad student code");
    }

    return is;
}



int main() {
    cout << "Starting." << endl;

    vector<StudentInfo> students;
    string::size_type maxlen = 0;

    stringstream sin(students_input);

    // There's something wrong about the way this loop is structured.
    // Maybe it needs a do...while or something that's somehow different, either
    // way it seems to do an off by one, and it's nothing to do with the raw
    // string literal being used.  We need to be checking the result of 'read'
    // and bailing out if it failed *inside* the loop.
    // The weirdness is to do with the user
    
    StudentInfo rec;
    while (rec.read(sin)) {
        cout << "Stream value inside loop: " << (sin ? "true" : "false") << endl;
        cout << "Read a record: " << rec.name() << endl;
        maxlen = max(maxlen, rec.name().size());
        students.push_back(rec);
    }

    cout << "Read " << students.size() << " records" << endl;

    sort(students.begin(), students.end(), StudentInfo::compare);
    
    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
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
    }
    
    cout << "End." << endl;
    return 0;
}
