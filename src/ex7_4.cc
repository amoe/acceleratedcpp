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

    // Fuck up the xref by shoving a bunch of fake stuff into it.
    typedef map<string, vector<int>>::iterator iter_t;
    for (iter_t it = result.begin(); it != result.end(); it++) {
        for (int i = 0; i < 100; i++) {
            it->second.push_back(i);
        }
    }


    print_xref_table(result);
    cout << "Done" << endl;
}


void print_xref_table(map<string, vector<int>> the_xref) {
    cout << "Table is listed:" << endl;

    typedef vector<int>::size_type vec_sz;
    typedef map<string, vector<int>>::const_iterator iter_t;

    for (iter_t it = the_xref.begin(); it != the_xref.end(); it++) {
        string word = it->first;
        vector<int> line_numbers = it->second;

        string post_token_canned_text = ": [";
        cout << word << post_token_canned_text;
        int column_counter = word.size() + post_token_canned_text.size();


        for (vec_sz i = 0; i < line_numbers.size(); i++) {
            bool is_last_index = (i == line_numbers.size() - 1);
            int this_line_number = line_numbers.at(i);

            int digits;
            if (this_line_number == 0) {
                digits = 1;
            } else {
                digits = floor(log10(this_line_number)) + 1;
            }


            int hypothesized_column = column_counter + digits;

            // Account for the comma
            if (!is_last_index) {
                hypothesized_column += 2;
            }

            // Break the line if necessary
            if (hypothesized_column > 80) {
                cout << endl << "... ";
                column_counter = 4;
            }

            cout << this_line_number;
            if (is_last_index) {
                column_counter += digits;
            } else {
                cout << ", ";
                column_counter += digits;
                column_counter += 2;
            }
        }

        cout << "]" << endl;
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
