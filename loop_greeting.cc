#include <iostream>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;   // read a single word name


    // This is the message, we can know its length at this point.
    const std::string greeting = "Hello, " + name + "!";

    const int greeting_height = 1;
    const int frame_height = 2;    // The top and the bottom use up one row each


    // Padding applies to both the top and bottom of the greeting.
    const int padding_top = 1;
    const int padding_bottom = 1;
    
    const int padding_total = padding_top + padding_bottom;

    
}
