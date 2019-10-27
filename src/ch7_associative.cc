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

void create_cross_reference_table(istream& input);
void demo_word_count_using_map(istream& input);

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
    create_cross_reference_table(sin2);

    cout << "Finish ch7." << endl;

    return 0;
}

void create_cross_reference_table(istream& input) {
    string line;

    while (getline(input, line)) {
        vector<string> words = split(line);
        print_vector(words);
    }
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

