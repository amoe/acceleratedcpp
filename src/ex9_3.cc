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

int main() {
    cout << "Starting." << endl;
    
    cout << "Catching the exception." << endl;

    try {
        StudentInfo s1;
        s1.grade();
    } catch (domain_error& e) {
        cout << "An exception occurred." << endl;
        cout << e.what() << endl;
    }

    cout << "Not catching the exception, this should kill the program." << endl;

    StudentInfo s1;
    s1.grade();

    cout << "End." << endl;
    return 0;
}
