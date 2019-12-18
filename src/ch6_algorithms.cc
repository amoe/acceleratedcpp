#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "student_info.hh"
#include "median.hh"
#include "grade.hh"
#include "util.hh"

using std::remove_copy;
using std::transform;
using std::accumulate;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::istream;
using std::ifstream;
using std::remove_if;
using std::remove_copy_if;

void demo_extend_vector() {
    vector<string> myvec = {"hello", "world"};

    vector<string> myvec2 = {"leela", "fry"};

    // Extend myvec with all elements of myvec2
    myvec.insert(myvec.end(), myvec2.begin(), myvec2.end());


    print_vector(myvec);
}

void demo_extend_vector_with_copy() {
    vector<string> myvec = {"hello", "world"};

    vector<string> myvec2 = {"leela", "fry"};

    // this refers to std::copy, and std::back_inserter
    copy(myvec2.begin(), myvec2.end(), back_inserter(myvec));

    print_vector(myvec);
}

bool space(char c) { return isspace(c); }
bool not_space(char c) { return !isspace(c); }

vector<string> split(const string& str) {
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end()) {
        // get the start of the range
        i = find_if(i, str.end(), not_space);

        // get the end of the range
        iter j = find_if(i, str.end(), space);
        
        if (i != str.end()) {
            ret.push_back(string(i, j));
        }

        // jump ahead to the end of the range
        i = j;
    }

    return ret;
}

void demo_better_split() {
    string input = "The quick brown fox";

    vector<string> result = split(input);
    print_vector(result);
}

// Reverse iterator
// the equal function is defined by <algorithm>
// equal assumes that the second sequence is the same size as the first.
bool is_palindrome(const string& s) {
    return equal(s.begin(), s.end(), s.rbegin());
}

// this stub will just produce empty urls
bool not_url_char(char c) {
//    cout << "char is " << c << endl;

    // ok, there's some other valid stuff as well but we don't need it for our test.
    static const string legal_url_punctuation = "://.";

    bool is_legal_punctuation = find(
        legal_url_punctuation.begin(),
        legal_url_punctuation.end(),
        c
    ) != legal_url_punctuation.end();


    bool result = !is_legal_punctuation && !isalnum(c);
    cout << "result for " << c << " will be " << result << endl;
    return result;
}

string::const_iterator find_url_end(
    string::const_iterator b, string::const_iterator e
) {
    std::cout << "finding url end" << std::endl;
    // just scan the string until we reach a 'non-url' character.
    return find_if(b, e, not_url_char);
}

// getting stuck here
string::const_iterator find_url_beginning(
    string::const_iterator b, string::const_iterator e
) {
    std::cout << "finding url beginning" << std::endl;
    static const string separator = "://";
    
    typedef string::const_iterator iter;

    // i will point at the next separator that was found.
    iter i = b;

    while (
        (i = search(i, e, separator.begin(), separator.end())) != e
    ) {
        bool at_start_of_line = i == b;
        bool at_end_of_line = (i + separator.size()) == e;

        if (!at_start_of_line && !at_end_of_line) {
            iter scan_pos = i;

            // scan backwards to a non-alphanumeric
            while (scan_pos != b && isalpha(scan_pos[-1])) {
                --scan_pos;
            }

            if (scan_pos != i && !not_url_char(i[separator.size()])) {
                return scan_pos;
            }
        } else {
            // invalid, advance past the separator.
            i += separator.size();
        }
    }

    return e;
}


// Find all urls in a given string
// The general approach is to manipulate iterators to scan both back and forward,
// using 'search()' and 'find_if()' methods from <algorithm>.
vector<string> find_urls(const string& s) {
    vector<string> ret;

    // Standard iterator pattern.
    typedef string::const_iterator iter;
    iter b = s.begin();
    iter e = s.end();

    while (b != e) {
        b = find_url_beginning(b, e);

        std::cout << "found beginning" << std::endl;
        
        if (b == e)  break;

        iter after = find_url_end(b, e);
        

        // extract the substring
        string this_url(b, after);
        ret.push_back(this_url);

        // continue from the next point
        b = after;
    }

    return ret;
}

bool student_did_all_homework_p(const StudentInfo& s) {
    // We pass a 0 here -- looking for 0 homeworks.
    // The result is "some iterator type".
    auto result = find(s.homework.begin(), s.homework.end(), 0);
    
    return result == s.homework.end();
}



// non-overloaded wrapper for grade() that allows passing through transform()
double grade_aux(const StudentInfo& s) {
    try {
        return grade(s);
    } catch (std::domain_error&) {
        return grade(s.midterm, s.final, 0);
    }
}

// A type of grade analyzer
double median_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;

    transform(
        students.begin(), students.end(),
        std::back_inserter(grades),
        grade_aux
    );

    return median(grades);
}

// Average a vector of any doubles
double average(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const StudentInfo& s) {
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;

    transform(
        students.begin(), students.end(), std::back_inserter(grades), average_grade
    );

    return median(grades);
}

double optimistic_median(const StudentInfo& s) {
    vector<double> nonzero;

    remove_copy(
        s.homework.begin(), s.homework.end(),
        std::back_inserter(nonzero), 0
    );

    if (nonzero.empty()) {
        return grade(s.midterm, s.final, 0);
    } else {
        return grade(s.midterm, s.final, median(nonzero));
    }
}

// this is nearly identical to the other analysis-calling functions
double optimistic_median_analysis(const vector<StudentInfo>& students) {
    vector<double> grades;
    
    transform(
        students.begin(), students.end(), std::back_inserter(grades),
        optimistic_median
    );

    return median(grades);
}

void write_analysis(
    std::ostream& out,
    const string& name,
    double analysis(const vector<StudentInfo>&),
    const vector<StudentInfo>& did,
    const vector<StudentInfo>& did_not
) {
    out << name
        << ": median(did) = " << analysis(did)
        << ": median(did_not) = " << analysis(did_not)
        << std::endl;
}

int demo_comparing_grading_schemes(istream& in) {
    vector<StudentInfo> did, did_not;
    StudentInfo the_student;

    while (read(in, the_student)) {
        // This would be a partition() in a more lispy style.
        if (student_did_all_homework_p(the_student)) {
            did.push_back(the_student);
        } else {
            did_not.push_back(the_student);
        }
    }
    
    if (did.empty()) {
        std::cout << "no one did all the homework, sad" << std::endl;
        return 1;
    }

    if (did_not.empty()) {
        std::cout << "nice, every student did all the homework" << std::endl;
        return 1;
    }

    write_analysis(std::cout, "median", median_analysis, did, did_not);
    write_analysis(std::cout, "average", average_analysis, did, did_not);
    write_analysis(std::cout, "optimistic-median", optimistic_median_analysis, did, did_not);

    return 0;
}

// Return true if a student failed.
bool fgrade(const StudentInfo s) {
    return grade(s) < 60;
}

// Return true if a student passed.
bool pgrade(const StudentInfo& s) {
    return !fgrade(s);
}

// This is a follow-up to extract_fails functions from chapter 5.
// Two-pass solution that iterates twice on students.
vector<StudentInfo> extract_fails_4(vector<StudentInfo>& students) {
    vector<StudentInfo> fail;

    // 'fail' becomes a filtered set of students that did NOT pass.
    remove_copy_if(
        students.begin(), students.end(), back_inserter(fail), pgrade
    );
    
    // remove_if will filter out failing students.  We use this to
    // find a sequence to then later pass to 'erase', which does modify the
    // array.
    students.erase(
        remove_if(students.begin(), students.end(), fgrade), students.end()
    );

    return fail;
}

// This solution only iterates students once.
vector<StudentInfo> extract_fails_5(vector<StudentInfo> students) {
    vector<StudentInfo>::iterator iter;

    iter = stable_partition(students.begin(), students.end(), pgrade);

    // Copy all students in the fails vector; iter now points at the start
    // of the failing students.
    vector<StudentInfo> fail(iter, students.end());

    // And remove them from the source vector
    students.erase(iter, students.end());
    
    return fail;
}

void demo_extract_fails_4(string input_path) {
    cout << "Demo extract_fails_4." << endl;
 
    ifstream in_file;
    in_file.open(input_path);
    if (!in_file) {
        throw std::runtime_error("open of student data failed");
    }

    StudentInfo the_student;
    vector<StudentInfo> students;

    while (read(in_file, the_student)) {
        students.push_back(the_student);
    }

    vector<StudentInfo> fails;
    fails = extract_fails_4(students);

    
    cout << "Fails: " << fails.size() << endl;
    cout << "Passes: " << students.size() << endl;
    
    in_file.close();

    cout << "Done." << endl;
}

void demo_extract_fails_5(string input_path) {
    cout << "Demo extract_fails_5." << endl;
 
    ifstream in_file;
    in_file.open(input_path);
    if (!in_file) {
        throw std::runtime_error("open of student data failed");
    }

    StudentInfo the_student;
    vector<StudentInfo> students;

    while (read(in_file, the_student)) {
        students.push_back(the_student);
    }

    vector<StudentInfo> fails;
    fails = extract_fails_5(students);

    cout << "Fails: " << fails.size() << endl;
    cout << "Passes: " << students.size() << endl;
    
    in_file.close();

    cout << "Done." << endl;
}



int main() {
    demo_extend_vector();
    demo_extend_vector_with_copy();
    demo_better_split();

    cout << is_palindrome("racecar") << endl;
    cout << is_palindrome("foobar") << endl;

    vector<string> result = find_urls(
        "Go to http://www.foo.com/bar/ and check out my ftp://site immediately"
    );

    cout << "found " << result.size() << " urls" << endl;

    for (auto url: result) {
        std::cout << "Found URL: " << url << std::endl;
    }


    cout << "Starting to run grading scheme comparison code, please wait." << endl;
    ifstream in_file;
    in_file.open("data/students-medium.dat");
    if (!in_file) {
        throw std::runtime_error("open of student data failed");
    }
    demo_comparing_grading_schemes(in_file);
    in_file.close();
    cout << "Finished grading scheme comparison." << endl;

    demo_extract_fails_4("data/students-small.dat");
    demo_extract_fails_5("data/students-large.dat");
}
