#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "split.hh"

using std::vector;
using std::string;
using std::stringstream;
using std::istream;
using std::map;
using std::cout;
using std::endl;
using std::log10;

using word_finder_t = vector<string> (*)(const string&);

using std::cout;
using std::endl;

void demo_cross_reference_table(istream& input);
map<string, vector<int>> xref(istream& in, word_finder_t find_words);
void print_xref_table(map<string, vector<int>> the_xref);

const string multi_line_input = R"(
Alice was beginning to get very tired of sitting by her sister on the
bank, and of having nothing to do: once or twice she had peeped into the
book her sister was reading, but it had no pictures or conversations in
it, ‘and what is the use of a book,’ thought Alice ‘without pictures or
conversations?’
)";

int main() {
    cout << "Hello, world!" << endl;

    stringstream sin2(multi_line_input);
    demo_cross_reference_table(sin2);

    return 0;
}

void demo_cross_reference_table(istream& input) {
    cout << "Generating xref" << endl;
    auto result = xref(input, split);
    print_xref_table(result);
    cout << "Done" << endl;
}

void print_line_number_list(const vector<int>& line_numbers) {
    typedef vector<int>::const_iterator iter_t;

    // Loop and a half to emulate a join function.

    // We always know that there will be more than zero numbers in the vector,
    // so this is safe when used with 'xref' function.
    iter_t it = line_numbers.begin();
    cout << *it;
    it++;   // scroll past it

    while (it != line_numbers.end()) {
        cout << ", " << *it;
        it++;
    }
}

void print_xref_table(map<string, vector<int>> the_xref) {
    cout << "Table is listed:" << endl;

    typedef map<string, vector<int>>::const_iterator iter_t;

    for (iter_t it = the_xref.begin(); it != the_xref.end(); it++) {
        string word = it->first;
        vector<int> line_numbers = it->second;

        
        
        cout << "The token '" << word << "' occurs on ";
        
        if (line_numbers.size() > 1) {
            cout << "lines";
        } else {
            cout << "line";
        }

        cout << " ";
        print_line_number_list(line_numbers);
        cout << endl;
    }
    
    cout << "Table listing done." << endl;
}

map<string, vector<int>> xref(istream& in, word_finder_t find_words) {
    map<string, vector<int>> result;
    int line_number = 1;
    string line;

    while (getline(in, line)) {
        vector<string> words = find_words(line);

        typedef vector<string>::const_iterator iter_t;
        for (iter_t it = words.begin(); it != words.end(); it++) {
            // Note that we don't need to handle the null-array case here, which
            // is kind of cool.  We skip the dynamic-language manual
            // initialization crap.
            result[*it].push_back(line_number);
        }

        line_number++;
    }


    return result;
}
