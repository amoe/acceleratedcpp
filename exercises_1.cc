#include <iostream>
#include <string>

void ex1_1() {
    const std::string hello = "Hello";
    const std::string message = hello + ", world" + "!";
}

void ex1_2() {
    const std::string exclam = "!";
    
    // Won't compile
    //const std::string message = "hello" + ", world" + exclam;
    const std::string message = "hello" + (", world" + exclam);
}

void ex1_3() {
    {
        const std::string s = "a string";
        std::cout << s << std::endl;
    }
    {
        const std::string s = "another string";
        std::cout << s << std::endl;
    }
}

// This demonstrates some counterintuitive behaviour of std::cin's buffering.
void ex1_6() {
    std::cout << "What is your name? ";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << std::endl << "And what is yours? ";
    std::cin >> name;
    std::cout << "Hello, " << name << "; nice to meet you too!" << std::endl;
}

int main(int argc, char **argv) {
    ex1_1();
    ex1_2();
    ex1_3();
    ex1_6();
    return 0;
}
