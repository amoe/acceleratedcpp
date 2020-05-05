#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "util.hh"
#include "split.hh"

using std::istream;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::map;
using std::vector;

using Rule = vector<string>;
using RuleCollection = vector<Rule>;
using Grammar = map<string, RuleCollection>;


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
    // K&M use find() instead -- long-winded.  This is safe and won't create
    // spurious elements.  It has different behaviour from tbe bracket operator.
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


int main() {
    cout << "Starting." << endl;

    demo_generating_sentences();

    cout << "End." << endl;
    return 0;
}
