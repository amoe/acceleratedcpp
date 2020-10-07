#include <iostream>
#include <string>
#include <sstream>
#include "student_types.hh"
#include "handles.hh"

using std::string;
using std::cout;
using std::endl;
using std::stringstream;

const string corestudents_only = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


// Note that we don't even pass by reference here, meaning this is going to
// increment the reference count.
bool compare_handles(
    const ControllableHandle<CoreStudent> c1,
    const ControllableHandle<CoreStudent> c2
) {
    return c1->name() < c2->name();
}


int main() {
    cout << "Starting." << endl;

    stringstream ss_in(corestudents_only);

    ControllableHandle<CoreStudent> s1(
        new CoreStudent(ss_in)
    );

    ControllableHandle<CoreStudent> s2(
        new CoreStudent(ss_in)
    );

    cout << "Student name is " << s1->name() << endl;
    cout << "Student name is " << s2->name() << endl;

    // Should return false, because s1 should not be ordered before s2.
    bool result = compare_handles(s1, s2);
    cout << "Comparison result was: " << (result ? "true" : "false") << endl;

    cout << "End." << endl;
    return 0;
}
