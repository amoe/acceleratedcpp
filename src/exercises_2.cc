#include <iostream>

void ex2_6() {
    int i = 0;
    while (i < 10) {
        i += 1;
        std::cout << i << std::endl;
    }
}

void ex2_7() {
    for (int i = 10; i >= -5; i--) {
        std::cout << i << std::endl;
    }
}

void ex2_8() {
    int product = 1;

    for (int i = 2; i < 10; i++) {
        product *= i;

    }

    std::cout << product << std::endl;
}

void ex2_9() {
    int n1, n2;

    std::cout << "Enter a number: ";
    std::cin >> n1;

    std::cout << "Enter another number: ";
    std::cin >> n2;

    if (n1 > n2) {
        std::cout << "The first is larger." << std::endl;
    } else if (n2 > n1) {
        std::cout << "The second is larger." << std::endl;
    } else {
        std::cout << "It's a trick!  They are equal." << std::endl;
    }
}


int main() {
//    ex2_6();
//    ex2_7();
//    ex2_8();
    ex2_9();
}
