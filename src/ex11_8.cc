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

    Node* get_next() {
        return next;
    }

    Node* get_previous() {
        return previous;
    }

private:
    const T& data;
    Node* next;
    Node* previous;
};


template <typename T>
class ListIterator {
public:
    ListIterator(Node<T>* current_node): current_node(current_node) {
    }

    const T& operator*() {
        return current_node->get_data();
    }

    void operator++(int n) {
        current_node = current_node->get_next();
    }

    bool operator==(const ListIterator& rhs) {
        return current_node == rhs.current_node;
    }

    bool operator!=(const ListIterator& rhs) {
        return !(*this == rhs);
    }

    Node<T>* get_current_node() {
        return current_node;
    }


private:    
    Node<T>* current_node;
};

template <typename T>
class List {
public:
    using iterator = ListIterator<T>;

    List(): front_node(0), back_node(0) {
        
    }

    void push_back(const T& data) {
        // We have to new it here, otherwise it will just fall off the stack.
        Node<T>* node_pointer = new Node<T>(data);

        if (front_node == 0) {
            front_node = node_pointer;
            back_node = node_pointer;
        } else {
            node_pointer->set_previous(back_node);
            back_node->set_next(node_pointer);
            back_node = node_pointer;
        }
    }

    const T& get_front() {
        return front_node->get_data();
    }

    ListIterator<T> begin() {
        return ListIterator<T>(front_node);
    }

    ListIterator<T> end() {
        // Slightly subtle, have a think about why this works.
        return ListIterator<T>(0);
    }

    void erase(iterator pos) {
        Node<T>* node = pos.get_current_node();
        Node<T>* previous = node->get_previous();
        Node<T>* next = node->get_next();
        previous->set_next(next);
        delete node;
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

    // manual_link();

    List<string> my_list;
    my_list.push_back("fry");
    my_list.push_back("bender");
    my_list.push_back("leela");

    string out = my_list.get_front();
    cout << "out is " << out << endl;


    List<string>::iterator it = my_list.begin();

    while (it != my_list.end()) {
        cout << *it << endl;
        it++;
    }

    List<string>::iterator it2 = my_list.begin();
    it2++;
    my_list.erase(it2);
    


    List<string>::iterator it3 = my_list.begin();
    while (it3 != my_list.end()) {
        cout << *it3 << endl;
        it3++;
    }

    cout << "End." << endl;
    return 0;
}
