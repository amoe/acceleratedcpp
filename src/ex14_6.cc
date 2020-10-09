#include <iostream>
#include "ex14_6.hh"

using std::cout;
using std::endl;


class Dog {
public:
    Dog(): val(42) { }

    Dog* clone() {
        return new Dog(*this);
    }
    
    void woof() {
        std::cout << "Woof!  woof!" << std::endl;
    }

    int val;
};


int main() {
    cout << "Starting." << endl;


    // What do we actually expect to happen here?
    ControllableHandle2<Dog> theDog(
        new Dog
    );

    // Ref count should be 1

    // Ref count should increase to 2
    ControllableHandle2<Dog> dog2 = theDog;

    cout << "Dog1 = " << &theDog << endl;
    cout << "Dog2 = " << &dog2 << endl;
    
    cout << "Ref count for dog2 is " << dog2.get_refcount() << endl;
    cout << "Ref count for theDog is " << theDog.get_refcount() << endl;

    ControllableHandle2<Dog> dog3;
    dog3 = theDog;
    cout << "Ref count for theDog is " << theDog.get_refcount() << endl;

    // dog2 gets destroyed first

    cout << "End." << endl;

    // Dealllocation.
    return 0;
}
