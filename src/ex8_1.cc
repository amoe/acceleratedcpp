#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include "student_info.hh"
#include "median.hh"
#include "grade.hh"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::find;
using std::accumulate;

double average(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const StudentInfo& s) {
    return grade(s.midterm, s.final, average(s.homework));
}

double optimistic_median(const StudentInfo& s) {
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



double grade_aux(const StudentInfo& s) {
    try {
        return grade(s);
    } catch (std::domain_error&) {
        return grade(s.midterm, s.final, 0);
    }
}


bool student_did_all_homework_p(const StudentInfo& s) {
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    return result == s.homework.end();
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


double optimistic_median_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;
    
    transform(
        students.begin(), students.end(), std::back_inserter(grades),
        optimistic_median
    );

    return median(grades);
}


int main() {
    cout << "Starting." << endl;

    vector<StudentInfo> did, did_not;
    StudentInfo the_student;

    ifstream in;
    in.open("data/students-medium.dat");
    if (!in) {
        throw std::runtime_error("open of student data failed");
    }


    while (read(in, the_student)) {
        if (student_did_all_homework_p(the_student)) {
            did.push_back(the_student);
        } else {
            did_not.push_back(the_student);
        }
    }
    
    if (did.empty()) {
        cout << "no one did all the homework, sad" << endl;
        return 1;
    }

    if (did_not.empty()) {
        cout << "nice, every student did all the homework" << endl;
        return 1;
    }

    write_analysis(cout, "median", median_analysis, did, did_not);
    write_analysis(cout, "average", average_analysis, did, did_not);
    write_analysis(cout, "optimistic-median", optimistic_median_analysis, did, did_not);

    cout << "End." << endl;
    return 0;
}
