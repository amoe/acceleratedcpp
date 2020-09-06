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

protected:
    istream& read_common(istream&);
    double midterm_grade, final_grade;
    vector<double> homework;

private:
    string n;
};

class GradStudent: public CoreStudent {
public:
    GradStudent();
    GradStudent(istream&);
    double grade() const;    // Note that we re-declare methods we will override
    istream& read(istream&);

private:
    double thesis;
};

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
