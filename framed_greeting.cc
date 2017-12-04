#include <iostream>
#include <string>

int main() {
    std::cout << "Please enter your first name: ";

    // Note that we can't declare name as const here, because we can't both 
    // define the variable and assign to it using the right-shift operator.
    std::string name;
    std::cin >> name;

    const std::string greeting = "Hello, " + name + "!";

    const std::string spaces(greeting.size(), ' ');
    const std::string second = "* " + spaces + " *";

    const std::string first(second.size(), '*');
    
    std::cout << std::endl;
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << "* " << greeting << " *" << std::endl;
    std::cout << second << std::endl;
    std::cout << first << std::endl;
    
    return 0;
}
