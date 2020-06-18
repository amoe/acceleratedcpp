#include <iostream>
#include <algorithm>
#include <string>
#include "characters.hh"

using std::copy;
using std::cout;
using std::endl;
using std::string;

class StringList {

public:
    using iterator = string*;

    StringList(): contents_length(0) {
        contents = new string[0];
    }

    void push_back(const string& value);
    void print_contents();

    string* begin() { return contents; }
    string* end() { return contents + contents_length; }

private:
    void grow(size_t n_members);

    string* contents;
    size_t contents_length;
};

void StringList::push_back(const string& value) {
    grow(1);
//    cout << "length is now " << contents_length << endl;
    contents[contents_length - 1] = value;
}

void StringList::grow(size_t n_members) {
//    cout << "reallocating" << endl;

    size_t old_length = contents_length;
    size_t new_length = contents_length + n_members;
    string* new_contents = new string[new_length];

    // Contents length has already been incremented, so the new value 
    copy(contents, contents + old_length, new_contents);
    delete[] contents;
    
    contents = new_contents;
    contents_length = new_length;

//    cout << "finished reallocating " << endl;
}

void StringList::print_contents() {
    for (size_t i = 0; i < contents_length; i++) {
        cout << contents[i] << endl;
    }
}

StringList split(const string& str) {
    typedef string::const_iterator iter;
    StringList ret;

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


int main() {
    cout << "Starting." << endl;

    cout << "Manual usage" << endl;

    StringList my_list;
    my_list.push_back("the");
    my_list.push_back("quick");
    my_list.push_back("brown");
    my_list.push_back("fox");

    for (
        StringList::iterator it = my_list.begin();
        it != my_list.end();
        it++
    ) {
        cout << *it << endl;
    }

    cout << "Use from split function" << endl;

    StringList result = split("the quick brown fox jumped");
    for (
        StringList::iterator it = result.begin();
        it != result.end();
        it++
    ) {
        cout << *it << endl;
    }


    cout << "End." << endl;
    return 0;
}
