#include <iostream>

void ex0_2() {
    std::cout << "This (\") is a quote, and this (\\) is a backslash." << std::endl;
}

void ex0_3() {
    std::cout << "This\tis a tab" << std::endl;
}

void ex0_4() {
    std::cout <<
        "#include <iostream>\nint main(int argc, char** argv) {std::cout<<\"Hello world!\"<<std::endl;return 0;}" << std::endl;
}

int main(int argc, char **argv) {
    ex0_2();
    ex0_3();
    ex0_4();
    return 0;
}
