#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

void print_vector(const vector<string>& vec) {
    for (string item: vec) {
        cout << '"' << item << '"' << endl;
    }
}

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

int main() {
    demo_extend_vector();
    demo_extend_vector_with_copy();
    demo_better_split();

    cout << is_palindrome("racecar") << endl;
    cout << is_palindrome("foobar") << endl;

    cout << "hello world" << endl;
}
