#ifndef GRAMMAR_TYPES_HH
#define GRAMMAR_TYPES_HH

#include <vector>
#include <map>
#include <string>

using std::map;
using std::vector;
using std::string;

using Rule = vector<string>;
using RuleCollection = vector<Rule>;
using Grammar = map<string, RuleCollection>;

#endif /* GRAMMAR_TYPES_HH */
