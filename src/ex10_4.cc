#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

class StringContainer {
public:
    StringContainer(): contents_length(0) { 
        reallocate();
    }

    void print_contents() const;
    void add(string s);

private:
    void reallocate();

    string** contents;
    size_t contents_length;
};

void StringContainer::add(string s) {
    contents_length++;
    reallocate();
    contents[contents_length] = &s;
}

void StringContainer::print_contents() const {
    cout << "Contents (size: " << contents_length << "):" << endl;
    for (size_t i = 0; i < contents_length; i++) {
        cout << "Element: " << *(contents[i]) << endl;
    }
    cout << "End contents" << endl;

}

void StringContainer::reallocate() {
    cout << "reallocating" << endl;
    contents = new string*[contents_length];
}

int main() {
    cout << "Starting." << endl;

    StringContainer container;
    container.print_contents();

    string foo = "Hong Kong Phooey";
    container.add(foo);
    container.print_contents();

    cout << "End." << endl;
    return 0;
}
