#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "median.hh"


using std::sort;
using std::max;
using std::streamsize;
using std::setprecision;
using std::stringstream;
using std::domain_error;
using std::istream;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class StudentInfo {
public:
    StudentInfo();
    StudentInfo(istream&);

    double grade() const;
    istream& read(istream&);
    string name() const {    // Likely to be inlined, because defined inline
        return n;
    }

    // User can check that the object is valid before requesting a grade.
    bool valid() const {
        return !homework.empty();
    }

private:
    istream& read_hw(istream& in, vector<double>& hw);

    // These container types are value-initialized by default.
    vector<double> homework;
    string n;

    // This would be default-initialized if no constructor were defined.  That
    // means it contains undefined crap.
    double midterm, final;
};

// Use initializer list to define the data members that would otherwise
// default-initialize.
StudentInfo::StudentInfo(): midterm(0), final(0) {
}


// NOTE that in this case we don't initialize the primitive members (because
// we're just about to overwrite them in the constructor body.)
StudentInfo::StudentInfo(istream& is) {
    read(is);
}

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw) {
    if (hw.size() == 0) {
        throw domain_error("student has done no homework");
    }

    return grade(midterm, final, median(hw));
}

double StudentInfo::grade() const {
    return ::grade(midterm, final, homework);
}

// Why return an istream?
istream& StudentInfo::read(istream& in) {
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}

// XXX: Identical to student_info.cc code
istream& StudentInfo::read_hw(istream& in, vector<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

// The `compare` function should be declared in the same header file that
// contains the student info stuff, it's part of the interface.
bool compare(const StudentInfo& x, const StudentInfo& y) {
    return x.name() < y.name();
}

const string multi_line_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


int main() {
    cout << "Starting." << endl;

    vector<StudentInfo> students;
    StudentInfo the_record;
    string::size_type maxlen = 0;

    stringstream sin1(multi_line_input);

    // Note that push_back here must copy the entire record.  Otherwise the
    // read would be overwriting the value.
    while (the_record.read(sin1)) {
        maxlen = max(maxlen, the_record.name().size());
        students.push_back(the_record);
    }

    sort(students.begin(), students.end(), compare);

    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        StudentInfo this_student = students[i];
        cout << this_student.name()
             << string((maxlen + 1) - this_student.name().size(), ' ');

        try {
            // Should never happen
            if (!this_student.valid()) {
                cout << "skipping invalid student" << endl;
            }

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
