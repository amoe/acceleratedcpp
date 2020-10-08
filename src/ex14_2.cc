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

// 14-2. Implement and test the student grading program using Ptr<Core> objects.

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


bool compare_Core_handles(
    const ControllableHandle<CoreStudent>& s1,
    const ControllableHandle<CoreStudent>& s2
) {
    return s1->name() < s2->name();
}


int main() {
    cout << "Starting." << endl;

    vector<ControllableHandle<CoreStudent>> students;
    ControllableHandle<CoreStudent> record;
    char ch;
    string::size_type maxlen = 0;
    stringstream sin(students_input);
    while (sin >> ch) {
        if (ch == 'U') {
            record = new CoreStudent;
        } else {
            record = new GradStudent;
        }

        record->read(sin);

        maxlen = max(maxlen, record->name().size());
        students.push_back(record);
    }

    cout << "Read " << students.size() << " students." << endl;

    sort(students.begin(), students.end(), compare_Core_handles);

    using vec_sz = vector<ControllableHandle<CoreStudent>>::size_type;

    
    for (vec_sz i = 0; i < students.size(); i++) {
        ControllableHandle<CoreStudent> s = students[i];
        cout << s->name()
             << string((maxlen + 1) - s->name().size(),  ' ');

        try {
            double final_grade = s->grade();
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

