#include <iostream>
#include <sstream>
#include <map>
#include <vector>
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


vector<string> generate_sentence(Grammar grammar) {
    vector<string> result;
    vector<string> word_stack;
    word_stack.push_back("<sentence>");
    
    while (!word_stack.empty()) {
        string this_word = word_stack.back();   // Should invoke the copy constructor.
        word_stack.pop_back();

        if (is_production(this_word)) {
            RuleCollection all_rules = grammar.at(this_word);
            int choice = 0;
            Rule chosen_rule = all_rules.at(choice);

            // Add in reverse order.  This has the effect of causing the rules
            // to be processed in order.
            word_stack.insert(
                word_stack.end(),
                chosen_rule.rbegin(),
                chosen_rule.rend()
            );
        } else {
            result.push_back(this_word);
        }        
    }

    return result;
}


int main() {
    cout << "Hello, world!" << endl;

    cout << "I would generate some sentences." << endl;
    stringstream sin(demo_grammar);
    Grammar g = read_grammar(sin);
    vector<string> sentence = generate_sentence(g);
    print_vector(sentence);

    cout << "Finished printing sentence." << endl;

    return 0;
}
