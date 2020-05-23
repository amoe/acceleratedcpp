#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::sort;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class StudentInfo {
public:
    StudentInfo(string student_name, double final, double midterm);
    string name() const { 
        return student_name; 
    };
    bool is_pass() const;

private:
    double grade() const;
    string student_name;
    double final;
    double midterm;
};

StudentInfo::StudentInfo(string student_name, double final, double midterm) 
    : student_name(student_name), final(final), midterm(midterm) {
}

double StudentInfo::grade() const {
    return (final + midterm) / 2.0;
}

bool StudentInfo::is_pass() const {
    return grade() > 60.0;
}

bool compare(const StudentInfo& s1, const StudentInfo& s2) {
    return s1.name() < s2.name();
}

int main() {
    cout << "Starting." << endl;

    StudentInfo s1("Fry", 51.0, 70.0);
    StudentInfo s2("Bender", 40.0, 60.0);
    StudentInfo s3("Leela", 60.0, 60.0);

    vector<StudentInfo> students = {s1, s2, s3};

    sort(students.begin(), students.end(), compare);


    using iter_t = vector<StudentInfo>::const_iterator;
    for (
        iter_t it = students.begin();
        it != students.end();
        it++
    ) {
        cout << it->name() << " "
             <<(it->is_pass() ? "P" : "F") << endl;
    }

    cout << "End." << endl;
    return 0;
}
