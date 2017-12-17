#include <iostream>
#include <string>

int main() {
    {
        const std::string s = "a string";
        std::cout << s << std::endl;
        {
            const std::string s = "another string";
            std::cout << s << std::endl;
        }
        ;  // This forms a null statement within this scope.
    }
    return 0;
}
