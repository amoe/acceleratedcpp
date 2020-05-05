#ifndef EX8_5_HH
#define EX8_5_HH

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


#endif /* EX8_5_HH */
