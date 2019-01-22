#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::find_if;
using std::cout;
using std::endl;


/* Test harness for find_urls.  Ex6-2 */

string::const_iterator find_url_beginning(string::const_iterator b, string::const_iterator e);
string::const_iterator find_url_end(string::const_iterator b, string::const_iterator e);
bool not_url_char(char c);

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



int main() {
    std::cout << "Hello, world!" << std::endl;

    vector<string> result = find_urls(
        "Go to http://www.foo.com/bar/ and check out my ftp://site immediately"
    );

    cout << "found " << result.size() << " urls" << endl;

    for (auto url: result) {
        std::cout << "Found URL: " << url << std::endl;
    }

    return 0;
}
