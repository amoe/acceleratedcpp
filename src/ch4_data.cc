#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "median.h"
#include "student_info.h"

using std::istream;
using std::string;
using std::vector;
using std::sort;
using std::max;
using std::cin;
using std::cout;

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}




// determine the grade of a student.  The const reference is just a performance
// thing.
double grade(const StudentInfo& s) {
    // Note that here we check the condition of the function domain, even though
    // the median function will do so for us anyway.
    if (s.homework.size() == 0) {
        throw std::domain_error("student has done no homework");
    }

    // Delegate to the overloaded version which works on a simple double.
    // Not quite sure what happens here, I suppose that the vector will be copied
    // into the overloaded median.
    return grade(s.midterm, s.final, median(s.homework));
}


int main() {
    vector<StudentInfo> students;

    StudentInfo theRecord;

    // This *must* be size_type because both arguments to max() need to have
    // precisely the same type.  No idea why.
    string::size_type maxlen = 0;


    // Accumulate all students from cin
    while (read(cin, theRecord)) {
        maxlen = max(maxlen, theRecord.name.size());
        students.push_back(theRecord);
    }

    sort(students.begin(), students.end(), lessThan);

    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        StudentInfo thisStudent = students[i];
        cout << thisStudent.name
             << string((maxlen + 1) - thisStudent.name.size(), ' ');

        try {
            double finalGrade = grade(thisStudent);
            streamsize prec = cout.precision();

            cout << setprecision(3) << finalGrade << setprecision(prec);
        } catch (std::domain_error e) {
            cout << e.what();
        }
    }
    
}
