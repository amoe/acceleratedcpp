#include <iostream>
#include <string>
#include <vector>
#include "ch13_inheritance.hh"

using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::endl;

class CoreStudent {
public:
    CoreStudent();
    CoreStudent(istream&);
    string name() const;
    istream& read(istream&);
    double grade() const;

private:
    istream& read_common(istream&);
    string n;
    double midterm_grade, final_grade;
    vector<double> homework;
};

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
