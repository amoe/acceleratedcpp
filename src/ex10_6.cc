#include <iostream>
#include <algorithm>
#include <string>

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
    cout << "length is now " << contents_length << endl;
    contents[contents_length - 1] = value;
}

void StringList::grow(size_t n_members) {
    cout << "reallocating" << endl;

    size_t old_length = contents_length;
    size_t new_length = contents_length + n_members;
    string* new_contents = new string[new_length];

    // Contents length has already been incremented, so the new value 
    copy(contents, contents + old_length, new_contents);
    delete[] contents;
    
    contents = new_contents;
    contents_length = new_length;

    cout << "finished reallocating " << endl;
}

void StringList::print_contents() {
    for (size_t i = 0; i < contents_length; i++) {
        cout << contents[i] << endl;
    }
}

int main() {
    cout << "Starting." << endl;

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

    cout << "End." << endl;
    return 0;
}
