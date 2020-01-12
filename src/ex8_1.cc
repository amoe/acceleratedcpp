#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include "student_info.hh"
#include "median.hh"
#include "grade.hh"
#include "ex8_1.hh"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::find;
using std::accumulate;


double grade_aux(const StudentInfo& s) {
    try {
        return grade(s);
    } catch (std::domain_error&) {
        return grade(s.midterm, s.final, 0);
    }
}

// Average a vector of any doubles
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

bool student_did_all_homework_p(const StudentInfo& s) {
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    return result == s.homework.end();
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

    write_analysis(cout, "median", grade_aux, did, did_not);
    write_analysis(cout, "average", average_grade, did, did_not);
    write_analysis(cout, "optimistic-median", optimistic_median, did, did_not);
    // write_analysis(cout, "median", median_analysis, did, did_not);
    // write_analysis(cout, "average", average_analysis, did, did_not);
    // write_analysis(cout, "optimistic-median", optimistic_median_analysis, did, did_not);

    cout << "End." << endl;
    return 0;
}
