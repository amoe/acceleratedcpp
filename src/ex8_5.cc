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
