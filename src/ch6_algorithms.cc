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

// this stub will just produce empty urls
bool not_url_char(char c) {
    return true;
}

string::const_iterator find_url_end(
    string::const_iterator b, string::const_iterator e
) {
    // just scan the string until we reach a 'non-url' character.
    return find_if(b, e, not_url_char);
}

string::const_iterator find_url_beginning(
    string::const_iterator b, string::const_iterator e
) {
    return e;
}


// Find all urls in a given string
vector<string> find_urls(const string& s) {
    vector<string> ret;

    // Standard iterator pattern.
    typedef string::const_iterator iter;
    iter b = s.begin();
    iter e = s.end();

    while (b != e) {
        b = find_url_beginning(b, e);
        
        if (b != e)  break;

        iter after = find_url_end(b, e);

        // extract the substring
        string this_url(b, after);
        ret.push_back(this_url);

        // continue from the next point
        b = after;
    }

    return ret;
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
        std::cout << url << std::endl;
    }

    cout << "hello world" << endl;
}
