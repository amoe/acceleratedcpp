#include "split.hh"

bool space(char c) { return isspace(c); }
bool not_space(char c) { return !isspace(c); }

vector<string> split(const string& str) {
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end()) {
        // get the start of the range
        i = find_if(i, str.end(), not_space);

        // get the end of the range
        iter j = find_if(i, str.end(), space);
        
        if (i != str.end()) {
            ret.push_back(string(i, j));
        }

        // jump ahead to the end of the range
        i = j;
    }

    return ret;
}
