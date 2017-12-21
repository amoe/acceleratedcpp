#include <iostream>

using std::cout;
using std::endl;
using std::string;

int nDigits(int n) {
    int result = 0;

    while (n >= 1) {
        n /= 10;
        result++;
    }

    return result;
}

void ex4_2_squares() {

    for (int i = 1; i < 100; i++) {
        int square = i * i;

        // Note that width is reset.  Pad to 2 digits.
        cout.width(2);
        cout << i << " " << square << endl;
    }
}


void ex4_3_generalized_squares() {
    // We use a simple minded way here.  A "better" way might be to convert
    // to string, but we don't know how to do so yet.
    int max = 1000;
    int desiredWidth = nDigits(max) - 1;

    for (int i = 1; i < max; i++) {
        int square = i * i;

        // Note that width is reset.  Pad to 2 digits.
        cout.width(desiredWidth);
        cout << i << " " << square << endl;
    }
}

int main() {
    ex4_2_squares();
    ex4_3_generalized_squares();
}
