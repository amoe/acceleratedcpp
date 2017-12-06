#include <iostream>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;   // read a single word name


    // This is the message, we can know its length at this point.
    const std::string greeting = "Hello, " + name + "!";


}
