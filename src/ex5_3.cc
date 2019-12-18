#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <list>
#include "grade.hh"
#include "student_info.hh"

using std::endl;
using std::istream;
using std::string;
using std::vector;
using std::list;
using std::sort;
using std::max;
using std::cin;
using std::cout;
using std::streamsize;
using std::setprecision;

bool fgrade(const StudentInfo s) {
    return grade(s) < 60;
}

typedef list<StudentInfo> student_sequence;

// This is a version using lists.  We only needed to change the data type.
student_sequence extract_fails(student_sequence& students) {
    student_sequence fail;
    student_sequence::const_iterator iter = students.begin();

    while (iter != students.end()) {
        if (fgrade(*iter)) {
            fail.push_back(*iter);

            iter = students.erase(iter);   
        } else {
            iter++;
        }
    }

    return fail;
}

void spewStudents(const student_sequence& students, string::size_type maxlen) {
    for (
        student_sequence::const_iterator iter = students.begin();
        iter != students.end();
        iter++
    ) {
        StudentInfo thisStudent = *iter;
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

int main() {
    student_sequence students;
    StudentInfo theRecord;

    // This *must* be size_type because both arguments to max() need to have
    // precisely the same type.  No idea why.
    string::size_type maxlen = 0;

    // Accumulate all students from cin
    while (read(cin, theRecord)) {
        maxlen = max(maxlen, theRecord.name.size());
        students.push_back(theRecord);
    }

    student_sequence fails = extract_fails(students);

    // Had to be disabled because the algorithm isn't the same between these
    // container types.
    //fails.sort(lessThan);
    
    spewStudents(fails, maxlen);

    return 0;
}
