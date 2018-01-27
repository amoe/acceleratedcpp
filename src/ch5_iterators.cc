#include <iostream>
#include "student_info.hh"
#include "grade.hh"
#include "median.hh"
#include <vector>

using std::vector;

typedef vector<StudentInfo>::size_type vecsz;


int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}

bool fgrade(const StudentInfo s) {
    return grade(s) < 60;
}

// This is going to actually modify the input reference by replacing it!
// It's kind of unclear what the memory semantics are for this.
// They go on to explain that it uses double memory.
vector<StudentInfo> extract_fails_0(vector<StudentInfo>& students) {
    vector<StudentInfo> pass, fail;

    for (vecsz i = 0; i < students.size(); i++) {
        StudentInfo theStudent = students[i];

        if (fgrade(theStudent)) {
            fail.push_back(theStudent);
        } else {
            pass.push_back(theStudent);
        }
    }

    // Modify the caller's reference to use the filtered list!
    students = pass;

    // And return the list of failures separately
    return fail;
}

// This is a slow but correct version created as a baseline, it uses erase()
// which has O(n^2) time complexity.
vector<StudentInfo> extract_fails_1(vector<StudentInfo>& students) {
    vector<StudentInfo> fail;

    vecsz i = 0;

    while (i < students.size()) {    // Note that the size can change!
        if (fgrade(students[i])) {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
            // Note that we don't need to increment i in this case, because i
            // now points to the next item to be processed.
        } else {
            i++;
        }
    }

    return fail;
}

// This is a strict-sequential version using iterators.  But it still uses
// erase().
vector<StudentInfo> extract_fails_2(vector<StudentInfo>& students) {
    vector<StudentInfo> fail;
    
    vector<StudentInfo>::const_iterator iter = students.begin();

    // Again, here we *need* to repeatedly call .end() function, because
    // the call to erase(n) will invalidate existing iterators that are past
    // that point -- which the end iterator certainly will be.
    while (iter != students.end()) {
        if (fgrade(*iter)) {
            fail.push_back(*iter);

             // Note reassignment!  Erase() invalidates existing iterators and
            // returns a new (valid) iterator.
            iter = students.erase(iter);   
        } else {
            iter++;
        }
    }

    return fail;
}

