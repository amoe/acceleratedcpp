#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using std::istream;
using std::string;

class StudentInfo {
public:
    StudentInfo() : midterm(0), final(0) { }
    StudentInfo(istream&);

    double grade() const;
    istream& read(istream&);
    string name() const {    // Likely to be inlined, because defined inline
        return n;
    }

    // User can check that the object is valid before requesting a grade.
    bool valid() const {
        return !homework.empty();
    }

private:
    // These container types are value-initialized by default.
    vector<double> homework;
    string n;

    // This would be default-initialized if no constructor were defined.  That
    // means it contains undefined crap.
    double midterm, final;
};

istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

// Why return an istream?
istream& StudentInfo::read(istream& in) {
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}


const string multi_line_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


void demo_copy_constructor() {
    stringstream sin1(multi_line_input);

    StudentInfo s1;

    cout << "initial name is " << s1.name() << endl;

    s1.read(sin1);

    cout << "after read name is " << s1.name() << endl;

    // Invoke synthesized copy constructor
    StudentInfo s2(s1);

    cout << "name of copy is " << s2.name() << endl;

    s1.read(sin1);

    cout << "s1 name is now " << s1.name() << endl;
    cout << "name of copy is " << s2.name() << endl;
}

void demo_assignment_operator() {
    stringstream sin1(multi_line_input);

    StudentInfo s1;

    cout << "initial name is " << s1.name() << endl;

    s1.read(sin1);

    cout << "after read name is " << s1.name() << endl;

    // Invoke operator=
    StudentInfo s2;
    s2 = s1;

    cout << "name of copy is " << s2.name() << endl;

    s1.read(sin1);

    cout << "s1 name is now " << s1.name() << endl;
    cout << "name of copy is " << s2.name() << endl;
}


int main() {
    cout << "Starting." << endl;

    cout << "Copy constructor:" << endl;
    demo_copy_constructor();

    cout << "Assignment operator:" << endl;
    demo_assignment_operator();


    cout << "End." << endl;
    return 0;
}
