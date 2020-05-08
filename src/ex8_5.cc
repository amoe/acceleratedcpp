#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "util.hh"
#include "split.hh"
#include "ex8_5.hh"

using std::getline;
using std::istream;
using std::stringstream;
using std::cout;
using std::endl;
using std::map;

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

int nrand(int n) {
    return (int)((double)rand() / ((double)RAND_MAX + 1) * n);
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

bool is_production(const string& s) {
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret) {
    if (!is_production(word)) {
        ret.push_back(word);
    } else {
        Grammar::const_iterator it = g.find(word);
        if (it == g.end()) {
            throw std::runtime_error("empty rule");
        }

        const RuleCollection& c = it->second;
        const Rule& r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); i++) {
            gen_aux(g, *i, ret);
        }
    }
}    

vector<string> gen_sentence(const Grammar& g) {
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}



int main() {
    cout << "Starting." << endl;

    srand(time(NULL));

    stringstream sin(demo_grammar);
    Grammar g = read_grammar(sin);

    cout << "size read (number of unique productions) is " << g.size() << endl;

    vector<string> sentence = gen_sentence(g);

    print_vector(sentence);

    cout << "End." << endl;
    return 0;
}
