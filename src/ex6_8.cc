#include <iostream>
#include <vector>
#include <algorithm>
#include "student_info.hh"
#include <fstream>

// ex6-8

using std::cout;
using std::endl;
using std::vector;
using std::istream;
using std::ifstream;
using std::stable_partition;

bool student_did_all_homework_p(const StudentInfo& s) {
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    return result == s.homework.end();
}


vector<StudentInfo> extract_with_criteria(
    vector<StudentInfo> students, bool criteria(const StudentInfo&)
) {
    vector<StudentInfo>::iterator iter;

    iter = stable_partition(students.begin(), students.end(), criteria);

    vector<StudentInfo> other_students(iter, students.end());
    students.erase(iter, students.end());
    
    return other_students;
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
    incomplete = extract_with_criteria(students, student_did_all_homework_p);

    cout << "Incomplete: " << incomplete.size() << endl;
    cout << "Complete: " << students.size() << endl;
        
    in_file.close();

    std::cout << "End." << std::endl;
}
