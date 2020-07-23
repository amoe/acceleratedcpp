#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename T>
class Node {
public:
    Node(T data): data(data) {}

private:
    T data;
};

int main() {
    cout << "Starting." << endl;

    Node<string> n("foo");

    cout << "End." << endl;
    return 0;
}
