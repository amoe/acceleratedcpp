#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
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
using std::ifstream;

istream& read_hw(istream& in, vector<double>& hw);

class StudentInfo {
public:
    StudentInfo();
    StudentInfo(istream&);

    double grade() const;
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

double StudentInfo::grade() const {
    return ::grade(midterm, final, homework);
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

bool student_did_all_homework_p(const StudentInfo& s) {
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    
    return result == s.homework.end();
}


double median_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;

    transform(
        students.begin(), students.end(),
        std::back_inserter(grades),
        grade_aux
    );

    return median(grades);
}


double average_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;

    transform(
        students.begin(), students.end(), std::back_inserter(grades), average_grade
    );

    return median(grades);
}

double StudentInfo::optimistic_median(const StudentInfo& s) {
    vector<double> nonzero;

    remove_copy(
        s.homework.begin(), s.homework.end(),
        std::back_inserter(nonzero), 0
    );

    if (nonzero.empty()) {
        return grade(s.midterm, s.final, 0);
    } else {
        return grade(s.midterm, s.final, median(nonzero));
    }
}

// this is nearly identical to the other analysis-calling functions
double optimistic_median_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;
    
    transform(
        students.begin(), students.end(), std::back_inserter(grades),
        optimistic_median
    );

    return median(grades);
}

void write_analysis(
    std::ostream& out,
    const string& name,
    double analysis(const vector<StudentInfo>&),
    const vector<StudentInfo>& did,
    const vector<StudentInfo>& did_not
) {
    out << name
        << ": median(did) = " << analysis(did)
        << ": median(did_not) = " << analysis(did_not)
        << std::endl;
}


int demo_comparing_grading_schemes(istream& in) {
    vector<StudentInfo> did, did_not;
    StudentInfo the_student;

    while (the_student.read(in)) {
        // This would be a partition() in a more lispy style.
        if (student_did_all_homework_p(the_student)) {
            did.push_back(the_student);
        } else {
            did_not.push_back(the_student);
        }
    }
    
    if (did.empty()) {
        std::cout << "no one did all the homework, sad" << std::endl;
        return 1;
    }

    if (did_not.empty()) {
        std::cout << "nice, every student did all the homework" << std::endl;
        return 1;
    }

    write_analysis(std::cout, "median", median_analysis, did, did_not);
    write_analysis(std::cout, "average", average_analysis, did, did_not);
    write_analysis(std::cout, "optimistic-median", optimistic_median_analysis, did, did_not);

    return 0;
}


const string multi_line_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


int main() {
    cout << "Starting." << endl;

    cout << "Starting to run grading scheme comparison code, please wait." << endl;
    ifstream in_file;
    in_file.open("data/students-medium.dat");
    if (!in_file) {
        throw std::runtime_error("open of student data failed");
    }
    demo_comparing_grading_schemes(in_file);
    in_file.close();
    cout << "Finished grading scheme comparison." << endl;

    cout << "End." << endl;
    return 0;
}
