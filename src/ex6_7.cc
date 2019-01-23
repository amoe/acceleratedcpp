#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include "student_info.hh"

using std::vector;
using std::find;
using std::stable_partition;
using std::cout;
using std::istream;
using std::ifstream;
using std::endl;

bool student_did_all_homework_p(const StudentInfo& s) {
    // We pass a 0 here -- looking for 0 homeworks.
    // The result is "some iterator type".
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    
    return result == s.homework.end();
}

vector<StudentInfo> extract_incomplete_hw_students(vector<StudentInfo> all_students) {
    vector<StudentInfo>::iterator iter;

    iter = stable_partition(
        all_students.begin(), 
        all_students.end(),
        student_did_all_homework_p
    );

    // Copy all students in the fails vector; iter now points at the start
    // of the failing students.
    vector<StudentInfo> incomplete_students(iter, all_students.end());

    // And remove them from the source vector
    all_students.erase(iter, all_students.end());
    
    return incomplete_students;
}


int main() {
    std::cout << "Starting." << std::endl;

    ifstream in_file;
    in_file.open("data/students-large.dat");
    if (!in_file) {
        throw std::runtime_error("open of student data failed");
    }

    StudentInfo the_student;
    vector<StudentInfo> students;

    while (read(in_file, the_student)) {
        students.push_back(the_student);
    }

    vector<StudentInfo> incomplete;
    incomplete = extract_incomplete_hw_students(students);

    cout << "Incomplete: " << incomplete.size() << endl;
    cout << "Complete: " << students.size() << endl;
        
    in_file.close();

    std::cout << "End." << std::endl;
}
