#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// a reference wouldn't work for this case because it can never be null and we
// don't have maybe/optional

template <typename T>
class Node {
public:
    Node(const T& data): data(data), next(0), previous(0) {}

    const T& get_data() {
        return data;
    }

    void set_next(Node* next) {
        this->next = next;
    }

    void set_previous(Node* previous) {
        this->previous = previous;
    }

private:
    const T& data;
    Node* next;
    Node* previous;
};

template <typename T>
class List {
public:
    List(): front_node(0), back_node(0) {
        
    }

    void push_back(const T& data) {
        // We have to new it here, otherwise it will just fall off the stack.
        Node<T>* node_pointer = new Node<T>(data);

        if (front_node == 0) {
            cout << "empty" << endl;
            front_node = node_pointer;
            back_node = node_pointer;
        } else {
            back_node->set_next(node_pointer);
            back_node = node_pointer;
        }
    }

    const T& get_front() {
        return front_node->get_data();
    }
    
private:
    Node<T>* front_node;
    Node<T>* back_node;
};


void manual_link() {
    Node<string> n1("fry");
    Node<string> n2("bender");
    Node<string> n3("leela");

    
    n1.set_next(&n2);
    n1.set_previous(0);    // 0 indicates a null pointer

    n2.set_next(&n3);
    n2.set_previous(&n1);

    n3.set_next(0);
    n3.set_previous(&n2);
}

int main() {
    cout << "Starting." << endl;

    manual_link();

    List<string> foo;
    foo.push_back("fry");

    string out = foo.get_front();
    cout << "out is " << out << endl;

    cout << "End." << endl;
    return 0;
}
