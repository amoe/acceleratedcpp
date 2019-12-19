#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "split.hh"

using std::vector;
using std::string;
using std::stringstream;
using std::istream;
using std::map;
using std::cout;
using std::endl;

using word_finder_t = vector<string> (*)(const string&);

using CrossReferenceTable = map<string, map<int, bool>>;

/*
"The cross reference program: as it stands, if a word occurs more than once on a line,
program will report line multiple itimes.  Change so it detects multiple occurrences
on the same line number and inserts the line number only once."

The obvious solution is to use a map as a set-substitute and do map<int, bool>
or something similar.
*/

void demo_cross_reference_table(istream& input);
CrossReferenceTable xref(istream& in, word_finder_t find_words);
void print_xref_table(CrossReferenceTable the_xref);


const string multi_line_input = R"(
Alice was beginning to get very tired of sitting by her sister on the
bank, and of having nothing to do: once or twice she had peeped into the
book her sister was reading, but it had no pictures or conversations in
it, ‘and what is the use of a book,’ thought Alice ‘without pictures or
conversations?’
)";

void demo_cross_reference_table(istream& input) {
    cout << "Generating xref" << endl;
    auto result = xref(input, split);
    print_xref_table(result);
    cout << "Done" << endl;
}

void print_line_number_list(map<int, bool> line_numbers) {
    typedef map<int, bool>::const_iterator iter_t;

    // Loop and a half to emulate a join function.

    // We always know that there will be more than zero numbers in the vector,
    // so this is safe when used with 'xref' function.
    iter_t it = line_numbers.begin();
    cout << it->first;
    it++;   // scroll past it

    while (it != line_numbers.end()) {
        cout << ", " << it->first;
        it++;
    }
}

void print_xref_table(CrossReferenceTable the_xref) {
    cout << "Table is listed:" << endl;

    typedef CrossReferenceTable::const_iterator iter_t;

    for (iter_t it = the_xref.begin(); it != the_xref.end(); it++) {
        string word = it->first;
        map<int, bool> line_numbers = it->second;
        
        cout << word << ": [";
        print_line_number_list(line_numbers);
        cout << "]" << endl;
    }
    
    cout << "Table listing done." << endl;
}


CrossReferenceTable xref(istream& in, word_finder_t find_words) {
    CrossReferenceTable result;
    int line_number = 1;
    string line;

    while (getline(in, line)) {
        vector<string> words = find_words(line);

        typedef vector<string>::const_iterator iter_t;
        for (iter_t it = words.begin(); it != words.end(); it++) {
            // Note that we don't need to handle the null-array case here, which
            // is kind of cool.  We skip the dynamic-language manual
            // initialization crap.
            result[*it][line_number] = true;
        }

        line_number++;
    }

    return result;
}



int main() {
    cout << "Hello, world!" << endl;

    stringstream sin2(multi_line_input);
    demo_cross_reference_table(sin2);

    return 0;
}
