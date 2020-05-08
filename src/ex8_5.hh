#ifndef EX8_5_HH
#define EX8_5_HH

#include "grammar_types.hh"
#include "random.hh"

bool is_production(const string& s) {
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

template <typename T>
void gen_aux(const Grammar& g, const string& word, T d) {
    if (!is_production(word)) {
        *d++ = word;
    } else {
        Grammar::const_iterator it = g.find(word);
        if (it == g.end()) {
            throw std::runtime_error("empty rule");
        }

        const RuleCollection& c = it->second;
        const Rule& r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); i++) {
            gen_aux(g, *i, d);
        }
    }
}    


// destination output iterator is d
template <typename T>
void gen_sentence(const Grammar& g, T d) {
    gen_aux(g, "<sentence>", d);
}

#endif /* EX8_5_HH */
