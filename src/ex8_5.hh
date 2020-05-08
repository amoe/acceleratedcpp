#ifndef EX8_5_HH
#define EX8_5_HH

#include "grammar_types.hh"
#include "random.hh"

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

#endif /* EX8_5_HH */
