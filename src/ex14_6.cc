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

    void set_value(int new_value) {
        val = new_value;
    }

    int get_value() const {
        return val;
    }
    
    void woof() {
        std::cout << "Woof!  woof!" << std::endl;
    }

    int val;
};

/*
void test_resource_management_functions() {
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

    // dog3 gets destroyed first, then dog2, then theDog
    // Dealllocation.
}
*/

void test_make_unique() {
    ControllableHandle2<Dog> theDog(new Dog);
    ControllableHandle2<Dog> dog2 = theDog;
    dog2.make_unique();
    dog2->set_value(44);
    cout << "Refcount of theDog is " << theDog.get_refcount() << endl;
}


int main() {
    cout << "Starting." << endl;

//    test_resource_management_functions();
    test_make_unique();
    
    cout << "End." << endl;
    return 0;
}
