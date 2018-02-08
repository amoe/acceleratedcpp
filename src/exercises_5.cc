#include <iomanip>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::setprecision;
using std::vector;


vector<string> split(const string& s) {
    vector<string> result;
    typedef string::size_type str_sz;
    str_sz i = 0;

    while (i < s.size()) {
        // skip leading spaces
        while (isspace(s[i]) && i < s.size())
            i++;

        str_sz j = i;
        while (!isspace(s[j]) && j < s.size())
            j++;


        if (j != i) {
            str_sz nChars = j - i;
            result.push_back(s.substr(i, nChars));
            i = j;
        }
    }

    return result;
}

void generateRotations(string input) {
    vector<string> words = split(input);


    vector<string>::iterator iter = words.end();
    iter--;
    string lastWord = *iter;

    vector<string>::iterator iter2 = words.begin();
    string firstWord = *iter;


    *iter2 = lastWord;
    *iter = firstWord;

    for (
        vector<string>::const_iterator iter3 = words.begin();
        iter3 != words.end();
        iter3++
    ) {
        std::cout << *iter3 << std::endl;
    }
}    

void  ex5_1_permuted_index() {
    vector<string> input = {
        "The quick brown fox",
        "jumped over the fence"
    };
    
    for (
        vector<string>::const_iterator iter = input.begin();
        iter != input.end();
        iter++
    ) {
        string thisLine = *iter;

        generateRotations(thisLine);
    }

}

int main() {
    ex5_1_permuted_index();

}
