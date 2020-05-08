#ifndef EX8_5_HH
#define EX8_5_HH

#include "grammar_types.hh"
#include "random.hh"

// This is bad but whatever
using std::istream;
using std::pair;

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

map<string, vector<int>> xref(
    istream& in,
    vector<string> find_words(const string&) = split
) {
    string line;
    int line_number = 0;
    map<string, vector<int>> ret;

    while (getline(in, line)) {
        ++line_number;

        vector<string> words = find_words(line);
        
        for (
            vector<string>::const_iterator it = words.begin();
            it != words.end();
            it++
        ) {
            ret[*it].push_back(line_number);
        }
    }

    return ret;
}

template <typename T>
void fill_map(T d) {
    pair<string, int> foo("foo", 42);
    pair<string, int> bar("bar", 56);
    pair<string, int> baz("baz", 17);

    *d++ = foo;
    *d++ = bar;
    *d++ = baz;
}


#endif /* EX8_5_HH */
