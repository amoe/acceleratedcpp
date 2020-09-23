#include <iostream>
#include "ch14_automatic.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    Dog* dog = new Dog;
    
    Handle<Dog> my_handle(dog);
    dog->woof();
    
    cout << "End." << endl;
    return 0;
}
