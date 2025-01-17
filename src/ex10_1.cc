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

istream& read_hw(istream& in, vector<double>& hw);

class StudentInfo {
public:
    StudentInfo();
    StudentInfo(istream&);

    string grade() const;
    istream& read(istream&);
    string name() const {
        return n;
    }

    bool valid() const {
        return !homework.empty();
    }

private:
    vector<double> homework;
    string n;
    double midterm, final;
};

StudentInfo::StudentInfo(): midterm(0), final(0) {
}


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

string StudentInfo::grade() const {
    static const double thresholds[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };
    static const int thresholds_length = sizeof(thresholds) / sizeof(*thresholds);

    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    double numeric_grade = ::grade(midterm, final, homework);
    
    for (int i = 0; i < thresholds_length; i++) {
        if (numeric_grade >= thresholds[i]) {
            return letters[i];
        }
    }

    return "?";
}

istream& StudentInfo::read(istream& in) {
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}

istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

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

            string letter_grade = this_student.grade();
            cout << letter_grade;
        } catch (std::domain_error& e) {
            cout << e.what();
        }

        cout << endl;
    }


    cout << "End." << endl;
    return 0;
}
