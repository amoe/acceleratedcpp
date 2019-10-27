#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "split.hh"
#include "util.hh"

using std::cout;
using std::endl;
using std::map;
using std::istream;
using std::cin;
using std::string;
using std::stringstream;
using std::vector;

using word_finder_t = vector<string> (*)(const string&);

void demo_cross_reference_table(istream& input);
void demo_word_count_using_map(istream& input);
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
    cout << "Starting ch7." << endl;

    // As we use the >> operator to word-split, and don't want to make
    // the user type in input every time, we use stringstream to feed input
    // via an istream&.
    string s = "It was the best of times, it was the worst of times";
    stringstream sin1(s);
    demo_word_count_using_map(sin1);

    stringstream sin2(multi_line_input);
    demo_cross_reference_table(sin2);

    cout << "Finish ch7." << endl;

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
        
        cout << word << ": [";
        print_line_number_list(line_numbers);
        cout << "]" << endl;
    }
    
    cout << "Table listing done." << endl;
}


map<string, vector<int>> xref(istream& in, word_finder_t find_words) {
    map<string, vector<int>> result;
    string line;

    while (getline(in, line)) {
        vector<string> words = find_words(line);
        print_vector(words);


        typedef vector<string>::const_iterator iter_t;
        for (iter_t it = words.begin(); it != words.end(); it++) {
            result[*it] = {0};
        }
    }


    return result;
}

void demo_word_count_using_map(istream& input) {
    string s;
    map<string, int> counters;

    while (input >> s)
        ++counters[s];

    typedef map<string, int>::const_iterator iter;

    for (iter it = counters.begin(); it != counters.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
}

