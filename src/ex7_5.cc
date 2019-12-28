#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <string>
#include "split.hh"
#include "util.hh"

using std::cout;
using std::endl;
using std::stringstream;
using std::map;
using std::vector;
using std::string;
using std::istream;
using std::list;

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

using Rule = vector<string>;
using RuleCollection = vector<Rule>;
using Grammar = map<string, RuleCollection>;

Grammar read_grammar(istream& input) {
    Grammar result;
    string line;

    while (getline(input, line)) {
        vector<string> entry = split(line);
        if (!entry.empty()) {
            string key = entry.at(0);
            result[key].push_back(
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

list<string> expand_word(Grammar grammar, const string& word) {
    RuleCollection all_rules = grammar.at(word);
    int choice = nrand(all_rules.size());
    Rule chosen_rule = all_rules.at(choice);

    list<string> result;

    for (string w: chosen_rule) {
        if (is_production(w)) {
            list<string> r = expand_word(grammar, w);
            result.insert(result.end(), r.begin(), r.end());
        } else {
            result.push_back(w);
        }
    }

    return result;
}


list<string> generate_sentence(Grammar grammar) {
    list<string> result;
    result = expand_word(grammar, "<sentence>");
    return result;
}


int main() {
    cout << "Hello, world!" << endl;

    cout << "I would generate some sentences." << endl;
    stringstream sin(demo_grammar);
    Grammar g = read_grammar(sin);
    list<string> sentence = generate_sentence(g);
    print_list(sentence);

    return 0;
}
