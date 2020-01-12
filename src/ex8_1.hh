#ifndef EX8_1_HH
#define EX8_1_HH

#include <iostream>
#include <vector>

using std::ostream;
using std::vector;
using std::string;

template <typename T>
double analysis(const vector<StudentInfo>& students, T grading_function) {
    vector<double> grades;

    transform(
        students.begin(), students.end(),
        std::back_inserter(grades),
        grading_function
    );

    return median(grades);
}

template <typename T>
void write_analysis(
    ostream& out,
    const string& name,
    T grading_function,
    const vector<StudentInfo>& did,
    const vector<StudentInfo>& did_not
) {
    out << name
        << ": median(did) = " << analysis(did, grading_function)
        << ": median(did_not) = " << analysis(did_not, grading_function)
        << std::endl;
}
    

#endif /* EX8_1_HH */
