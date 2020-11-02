#include <iostream>
#include <sstream>
#include "pictures.hh"
#include "student_types.hh"
#include "student_info_ng.hh"

using std::stringstream;
using std::cout;
using std::endl;

Picture histogram(const vector<StudentInfo>& students) {
    Picture names;
    Picture grades;

    using iter_t = vector<StudentInfo>::const_iterator;
    
    for (iter_t it = students.begin(); it != students.end(); it++) {
        string grade_bar(it->grade() / 5, '=');
        
        names = vcat(names, vector<string>(1, it->name()));
        grades = vcat(grades, vector<string>(1, " " + grade_bar));
    }

    return hcat(names, grades);
}

const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
)";

int main() {
    cout << "Starting." << endl;

    vector<StudentInfo> students;
    StudentInfo record;
    stringstream sin(students_input);

    while (record.read(sin)) {
        students.push_back(record);
    }

    sort(students.begin(), students.end(), StudentInfo::compare);

    cout << frame(histogram(students)) << endl;

    cout << "End." << endl;
    return 0;
}
