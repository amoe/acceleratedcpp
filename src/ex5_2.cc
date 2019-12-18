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

// This is a version using lists.  We only needed to change the data type.
list<StudentInfo> extract_fails(list<StudentInfo>& students) {
    list<StudentInfo> fail;
    list<StudentInfo>::const_iterator iter = students.begin();

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

void spewStudents(const list<StudentInfo>& students, string::size_type maxlen) {
    for (list<StudentInfo>::const_iterator iter = students.begin(); iter != students.end(); iter++) {
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
    list<StudentInfo> students;

    StudentInfo theRecord;

    // This *must* be size_type because both arguments to max() need to have
    // precisely the same type.  No idea why.
    string::size_type maxlen = 0;


    // Accumulate all students from cin
    while (read(cin, theRecord)) {
        maxlen = max(maxlen, theRecord.name.size());
        students.push_back(theRecord);
    }

    list<StudentInfo> fails = extract_fails(students);

//    fails.sort(lessThan);
    
    spewStudents(fails, maxlen);

    return 0;
}
