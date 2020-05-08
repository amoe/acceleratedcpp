#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "grammar_types.hh"
#include "util.hh"
#include "split.hh"
#include "ex8_5.hh"

using std::istream;
using std::getline;
using std::cout;
using std::endl;
using std::stringstream;

const string multi_line_input = R"(
Alice was beginning to get very tired of sitting by her sister on the
bank, and of having nothing to do: once or twice she had peeped into the
book her sister was reading, but it had no pictures or conversations in
it, ‘and what is the use of a book,’ thought Alice ‘without pictures or
conversations?’
)";

const string demo_grammar = R"(
<noun>          cat
<noun>          dog
<noun>          table
<noun-phrase>   <noun>
<noun-phrase>   <adjective> <noun-phrase>
<adjective>     large
<adjective>     brown
<adjective>     absurd
<verb>          jumps
<verb>          sits
<location>      on the stairs
<location>      under the sky
<location>      wherever it wants
<sentence>      the <noun-phrase> <verb> <location>
)";

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
        
        cout << word << ": [";
        print_line_number_list(line_numbers);
        cout << "]" << endl;
    }
    
    cout << "Table listing done." << endl;
}



Grammar read_grammar(istream& in) {
    Grammar result;
    string line;

    while (getline(in, line)) {
        vector<string> entry = split(line);
        if (!entry.empty()) {
            string production_name = entry.at(0);
            Rule this_rule(entry.begin() + 1, entry.end());
            result[production_name].push_back(this_rule);
        }
    }

    return result;
}

void demo_generating_sentences() {
    srand(time(NULL));
    stringstream sin(demo_grammar);
    Grammar g = read_grammar(sin);

    cout << "size read (number of unique productions) is " << g.size() << endl;

    vector<string> sentence;
    gen_sentence(g, back_inserter(sentence));
    print_vector(sentence);
}


void demo_cross_reference_table(istream& input) {
    cout << "Generating xref" << endl;
    map<string, vector<int>> result = xref(input, split);
    print_xref_table(result);
    cout << "Done" << endl;
}


int main() {
    cout << "Starting." << endl;

    // demo_generating_sentences();

    // stringstream sin2(multi_line_input);
    // demo_cross_reference_table(sin2);



    map<string, int> result = fill_map();

    for (map<string, int>::const_iterator it = result.begin();
         it != result.end();
         it++) {
        cout << it->first << ": " << it->second << endl;
    }
    
    cout << "End." << endl;
    return 0;
}
