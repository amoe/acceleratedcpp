#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include "util.hh"
#include "split.hh"
#include "ex8_5.hh"

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
