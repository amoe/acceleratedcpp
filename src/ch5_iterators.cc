#include <iostream>
#include "student_info.hh"
#include "grade.hh"
#include "median.hh"
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::isspace;
using std::max;

typedef vector<StudentInfo>::size_type vecsz;
vector<string> split(const string& s);
vector<string> frame(const vector<string>& words);


int main() {
    std::cout << "Hello, world!" << std::endl;
    
    string foo = "The quick brown fox jumped over the lazy dog";

    vector<string> result = split(foo);

    for (auto word : result) {
        std::cout << word << std::endl;
    }

    vector<string> framed = frame(result);
    for (auto line : framed) {
        std::cout << line << std::endl;
    }


    return 0;
}

bool fgrade(const StudentInfo s) {
    return grade(s) < 60;
}

// START extract_fails functions.

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

// This is a version using lists.  We only needed to change the data type.
list<StudentInfo> extract_fails_3(list<StudentInfo>& students) {
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

// END extract_fails functions.


// Koenig&Moo's index-based string split.
vector<string> split(const string& s) {
    vector<string> result;
    typedef string::size_type str_sz;
    str_sz i = 0;

    while (i < s.size()) {
        // skip leading spaces
        while (isspace(s[i]) && i < s.size())
            i++;

        str_sz j = i;
        while (!isspace(s[j]) && j < s.size())
            j++;


        if (j != i) {
            str_sz nChars = j - i;
            result.push_back(s.substr(i, nChars));
            i = j;
        }
    }

    return result;
}

string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;

    for (vector<string>::size_type i = 0; i < v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }

    return maxlen;
}

// 5.8 -- Framing a picture.

vector<string> frame(const vector<string>& words) {
    vector<string> result;
    string::size_type maxlen = width(words);
    string border(maxlen + 4, '*');

    result.push_back(border);

    for (vector<string>::size_type i = 0; i < words.size(); i++) {
        string padding(maxlen - words[i].size(), ' ');
        
        result.push_back("* "  + words[i] + padding + " *");
    }

    result.push_back(border);

    return result;
}
