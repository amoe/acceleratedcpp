#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "grade.hh"
#include "student_info.hh"

using std::endl;
using std::istream;
using std::string;
using std::vector;
using std::sort;
using std::max;
using std::cin;
using std::cout;
using std::streamsize;
using std::setprecision;

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
        } catch (std::domain_error& e) {
            cout << e.what();
        }

        cout << endl;
    }
    
}
