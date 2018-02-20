#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::max;

const vector<string> centre(const vector<string>& input) {
    cout << "Hi" << endl;

    typedef string::size_type sz;

    sz maxlen = 0;
    for (
        vector<string>::const_iterator iter = input.begin();
        iter != input.end();
        iter++
    ) {
        maxlen = max(maxlen, iter->size());
    }

    

    cout << "found max length as " << maxlen << endl;

    vector<string> result;

    for (
        vector<string>::const_iterator iter = input.begin();
        iter != input.end();
        iter++
    ) {
        sz padding = maxlen - iter->size();
        sz leftPadding = (padding / 2);
        sz rightPadding = (padding - leftPadding);

        cout << "left padding is " << leftPadding << endl;
        cout << "right padding is " << rightPadding << endl;

        string leftPad(leftPadding, ' ');
        string rightPad(rightPadding, ' ');

        string paddedVersion = "* " + leftPad + *iter + rightPad + " *";

        result.push_back(paddedVersion);
    }

    return result;
}

int main(int argc, char** argv) {
    const vector<string>& input = {
        "The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"
    };

    const vector<string>& result = centre(input);

    for (
        vector<string>::const_iterator iter = result.begin();
        iter != result.end();
        iter++
    ) {
        cout << *iter << endl;
    }
    
    return 0;
}
