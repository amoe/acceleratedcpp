#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::max;

vector<string> frame(const vector<string>& words);
void spew(const vector<string>& pic);
vector<string> split(const string& s);
string::size_type width(const vector<string>& v);
vector<string> hcat(const vector<string>& left, const vector<string>& right);
vector<string> vcat(const vector<string>& top, const vector<string>& bottom);


// Exercise 6-1, hcat() with iterators.
vector<string> hcat(const vector<string>& left, const vector<string>& right) {
    vector<string> result;

    string::size_type widthLeft = width(left) + 1;

    typedef vector<string>::const_iterator iter;
    iter i = left.begin();
    iter j = right.begin();

    while (i != left.end() || j != right.end()) {
        string s;

        // i may have already run out at any stage during the loop.
        if (i != left.end()) {
            s = *i;
            i++;
        }

        s += string(widthLeft - s.size(), ' ');

        if (j != right.end()) {
            s += *j;
            j++;
        }

        
        result.push_back(s);
    }

    return result;
}



// Exercise 6-1, reimplementing frame() with iterators.
vector<string> frame(const vector<string>& words) {
    typedef vector<string>::const_iterator iter;

    vector<string> result;
    string::size_type maxlen = width(words);
    string border(maxlen + 4, '*');

    result.push_back(border);

    for (iter it = words.begin(); it != words.end(); it++) {
        string padding(maxlen - it->size(), ' ');
        result.push_back("* "  + *it + padding + " *");
    }

    result.push_back(border);

    return result;
}


string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;

    for (vector<string>::size_type i = 0; i < v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }

    return maxlen;
}



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

void spew(const vector<string>& pic) {
    for (auto line : pic) {
        std::cout << line << std::endl;
    }
}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
    vector<string> result = top;

    for (
        vector<string>::const_iterator iter = bottom.begin();
        iter != bottom.end();
        iter++
    ) {
        result.push_back(*iter);
    }

    return result;
}



int main() {
    std::cout << "Hello, world!" << std::endl;
    
    string foo = "The quick brown fox jumped over the lazy dog";

    vector<string> result = split(foo);

    for (auto word : result) {
        std::cout << word << std::endl;
    }

    vector<string> framed = frame(result);
    spew(framed);


    spew(vcat(result, framed));
    spew(hcat(result, framed));

    return 0;

}
