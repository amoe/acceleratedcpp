#include <iostream>

int main() {
    {
        std::string s = "a string";
        {
            std::string x = s + ", really";
            std::cout << s << std::endl;
            std::cout << x << std::endl;
        }

        // error: 'x' was not declared in this scope
        //std::cout << x << std::endl;
    }

    return 0;
}
