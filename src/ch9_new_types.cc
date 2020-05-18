#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "median.hh"

using std::streamsize;
using std::setprecision;
using std::stringstream;
using std::domain_error;
using std::istream;
using std::cout;
using std::endl;
using std::string;
using std::vector;

istream& read_hw(istream& in, vector<double>& hw);

class StudentInfo {
public:
    double grade() const;
    istream& read(istream&);
    string name() const {
        return n;
    }

private:
    string n;
    double midterm, final;
    vector<double> homework;
};

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
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

const string multi_line_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


int main() {
    cout << "Starting." << endl;


    stringstream sin1(multi_line_input);
    StudentInfo student;
    student.read(sin1);

    // This should actually be the max of the whole collection.
    string::size_type maxlen = student.name().size();

    // Can't do this now
    cout << student.name()
         << string((maxlen + 1) - student.name().size(), ' ');
        

    try {
        double finalGrade = student.grade();
        streamsize prec = cout.precision();
        cout << setprecision(3) << finalGrade << setprecision(prec);
    } catch (std::domain_error& e) {
        cout << e.what();
    }

    cout << endl;


    cout << "End." << endl;
    return 0;
}
