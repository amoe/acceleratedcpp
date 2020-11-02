#include <iostream>
#include "pictures.hh"
#include "student_types.hh"
#include "student_info_ng.hh"

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

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
