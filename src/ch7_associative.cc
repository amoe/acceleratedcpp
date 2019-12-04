#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
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

using Rule = vector<string>;
using RuleCollection = vector<Rule>;
using Grammar = map<string, RuleCollection>;

void demo_cross_reference_table(istream& input);
void demo_word_count_using_map(istream& input);
map<string, vector<int>> xref(istream& in, word_finder_t find_words);
void print_xref_table(map<string, vector<int>> the_xref);
void demo_generating_sentences();
Grammar read_grammar(istream& input);

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


int main() {
    srand(time(NULL));

    cout << "Starting ch7." << endl;

    // As we use the >> operator to word-split, and don't want to make
    // the user type in input every time, we use stringstream to feed input
    // via an istream&.
    string s = "It was the best of times, it was the worst of times";
    stringstream sin1(s);
    demo_word_count_using_map(sin1);

    stringstream sin2(multi_line_input);
    demo_cross_reference_table(sin2);

    demo_generating_sentences();

    cout << "Finish ch7." << endl;

    return 0;
}

Grammar read_grammar(istream& input) {
    Grammar result;
    string line;

    while (getline(input, line)) {
        vector<string> entry = split(line);
        if (!entry.empty()) {
            string key = entry.at(0);
            // 'at' will not work here.
            result[key].push_back(
                // WTF is going on here?    Constructing a vector<string>
                // from the list slice.  Equivalent to entry[1:] in python.
                Rule(entry.begin() + 1, entry.end())
            );
        }
    }

    return result;
}

bool is_production(string str) {
    const char& first = str.at(0);
    const char& last = str.at(str.size() - 1);

    return first == '<' && last == '>';
}


int nrand(int n) {
    return (int)((double)rand() / ((double)RAND_MAX + 1) * n);
}

vector<string> expand_word(Grammar grammar, const string& word) {
    RuleCollection all_rules = grammar.at(word);
    int choice = nrand(all_rules.size());
    Rule chosen_rule = all_rules.at(choice);

    vector<string> result;

    for (string w: chosen_rule) {
        if (is_production(w)) {
            vector<string> r = expand_word(grammar, w);
            result.insert(result.end(), r.begin(), r.end());
        } else {
            result.push_back(w);
        }
    }

    return result;
}

// Kick off the recursive expansion
vector<string> generate_sentence(Grammar grammar) {
    vector<string> result;
    result = expand_word(grammar, "<sentence>");
    return result;
}

void demo_generating_sentences() {
    cout << "I would generate some sentences." << endl;
    stringstream sin(demo_grammar);
    Grammar g = read_grammar(sin);
    vector<string> sentence = generate_sentence(g);
    print_vector(sentence);
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
        
        cout << word << ": [";
        print_line_number_list(line_numbers);
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

