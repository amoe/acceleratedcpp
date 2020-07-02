#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;
using std::endl;

class DemoStudent {
public:
    DemoStudent(int v) : value(v) { } 

    DemoStudent& operator=(const DemoStudent& source) {
        cout << "inside overloaded assignment" << endl;
        // Note that we can access the private field here directly!
        // See https://programming.guide/java/accessing-private-fields-of-other-objects.html
        value = source.value;
        return *this;
    }

    int get_value() const { return value; }

private:
    int value;
};

class StudentInfo {
public:
    StudentInfo(): midterm(0), final(0) {
    }

    StudentInfo& operator=(const StudentInfo& source) {
        cout << "assigning" << endl;
        homework = source.homework;   // Call operator= in vector (deletes mem backing this->homework)
        n = source.n;    // Call operator= in string (deletes mem backing this->n)
        midterm = source.midterm;    // Fundamental type, just overwritten
        final = source.final;       // ...same
        return *this;
    }

private:
    vector<double> homework;
    string n;
    double midterm, final;
};

int main() {
    cout << "Starting." << endl;

    DemoStudent s1(42);
    DemoStudent s2(17);

    cout << "s1 has value " << s1.get_value() << endl;

    s1 = s2;

    cout << "s1 has value " << s1.get_value() << endl;

    StudentInfo x;
    StudentInfo y;
    x = y;
    
    cout << "End." << endl;
    return 0;
}
