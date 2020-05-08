#include <iostream>
#include <map>
#include "util.hh"
#include "split.hh"
#include "ex8_5.hh"

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

int main() {
    cout << "Starting." << endl;
    cout << "End." << endl;
    return 0;
}
