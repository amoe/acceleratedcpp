#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "grade.hh"
#include "student_info.hh"

using std::max;
using std::istream;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::map;
using std::vector;

struct GradeBandCriterion {
    double minimum;
    double maximum;
};

map<string, GradeBandCriterion> grade_bands = {
    {"A", {90.0, 100.0}},
    {"B", {80.0, 90.0}},
    {"C", {70.0, 80.0}},
    {"D", {60.0, 70.0}},
    {"F", {0.0, 60.0}}
};

string find_grade_band(double final_grade) {
    typedef map<string, GradeBandCriterion>::const_iterator iter_t;

    for (iter_t it = grade_bands.begin(); it != grade_bands.end(); ++it) {
        string grade_name = it->first;
        GradeBandCriterion criterion = it->second;

        if (final_grade >= criterion.minimum && final_grade <= criterion.maximum) {
            return grade_name;
        }
    }
}


void ex7_2(istream& input) {
    map<string, int> grade_band_count;
    typedef map<string, int>::const_iterator iter_t;

    vector<StudentInfo> students;
    StudentInfo theRecord;
    string::size_type maxlen = 0;

    while (read(input, theRecord)) {
        maxlen = max(maxlen, theRecord.name.size());
        students.push_back(theRecord);
    }

    sort(students.begin(), students.end(), lessThan);

    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        StudentInfo thisStudent = students[i];
        double final_grade = grade(thisStudent);
        string grade_band = find_grade_band(final_grade);
        grade_band_count[grade_band]++;
    }

    for (iter_t it = grade_band_count.begin(); it != grade_band_count.end(); ++it) {
        string grade_name = it->first;
        int count = it->second;
        cout << "Students who got an " << grade_name << ": " << count << endl;
    }
}

const string students_small_input = R"(Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
Zutell 31 75 81 54 18 87
Jervis 10 45 37 22 74 70
Ottem 55 25 88 4 51 55
Hellen 13 75 20 42 66 54
Droney 17 82 29 73 36 75
Pyne 25 77 14 26 93 49
Hebert 35 83 24 69 24 80
Orrico 90 54 27 3 2 11
)";



int main() {
    std::cout << "Hello, world!" << std::endl;

    stringstream sin2(students_small_input);
    ex7_2(sin2);

    return 0;
}
