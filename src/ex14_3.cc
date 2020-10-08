#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "student_types.hh"
#include "handles.hh"
#include "ex14_3.hh"

// 14-3. Implement the Student_info class to use the final version of Ptr , and
// use that version to implement the grading program from §13.5/247.

using std::istream;
using std::stringstream;
using std::setprecision;
using std::streamsize;
using std::domain_error;
using std::vector;
using std::string;
using std::sort;
using std::cout;
using std::endl;
using std::max;

const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
)";


istream& StudentInfo::read(istream& is) {
    char ch;
    is >> ch;

    if (ch == 'U') {
        cp = new CoreStudent(is);
    } else {
        cp = new GradStudent(is);
    }
    return is;
}



int main() {
    cout << "Starting." << endl;
    vector<StudentInfo> students;
    StudentInfo record;
    char ch;
    string::size_type maxlen = 0;
    stringstream sin(students_input);


    while (record.read(sin)) {
        cout << "Content of record: '" << record.name() << "'" << endl;
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    cout << "Read " << students.size() << " students." << endl;

    sort(students.begin(), students.end(), StudentInfo::compare);
    using vec_sz = vector<StudentInfo>::size_type;

    
    for (vec_sz i = 0; i < students.size(); i++) {
        StudentInfo& s = students[i];
        cout << s.name() << "(" << s.get_refcount() << ")"
             << string((maxlen + 1) - s.name().size(),  ' ');

        try {
            double final_grade = s.grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }
    }

    cout << "End." << endl;
    return 0;
}
