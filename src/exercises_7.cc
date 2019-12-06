#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "grade.hh"
#include "student_info.hh"
#include "util.hh"

using std::streamsize;
using std::setprecision;
using std::max;
using std::cout;
using std::endl;
using std::map;
using std::istream;
using std::cin;
using std::string;
using std::stringstream;
using std::vector;

// Group all words that occur once, then all words that occur twice, etc.
// How would we do this?
// Reconstruct post hoc.
void ex7_1(istream& input) {
    typedef map<string, int>::const_iterator iter1_t;
    typedef map<int, vector<string>>::const_iterator iter2_t;
    string s;
    map<string, int> counters;

    while (input >> s)
        ++counters[s];

    map<int, vector<string>> grouped;

    // Basically invert the map
    for (iter1_t it = counters.begin(); it != counters.end(); ++it) {
        string word = it->first;
        int occurrences = it->second;

        grouped[occurrences].push_back(word);
    }

    for (iter2_t it = grouped.begin(); it != grouped.end(); ++it) {
        int occurrences = it->first;
        cout << "Occurrences: " << occurrences << endl;
        print_vector(it->second);
    }
}

void ex7_2(istream& input) {
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
        double finalGrade = grade(thisStudent);
        cout << finalGrade << endl;
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

    string s = "It was the best of times, it was the worst of times";
    stringstream sin1(s);
    ex7_1(sin1);

    stringstream sin2(students_small_input);
    ex7_2(sin2);

    return 0;
}
