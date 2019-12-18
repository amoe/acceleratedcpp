#include <iomanip>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::setprecision;
using std::vector;

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

void ex4_4_doubles() {
    // We use a simple minded way here.  A "better" way might be to convert
    // to string, but we don't know how to do so yet.
    int max = 1000;

    for (double i = 1.0; i < max; i++) {
        double square = i * i;
        cout << i << " " << setprecision(10) << square << endl;
    }
}

void ex4_7_average() {
    vector<double> input = {1.0, 2.2, 3.7, 4.3, 5.3, 6.9};
    typedef vector<double>::size_type  vec_sz;

    double sum = 0;
    for (vec_sz i = 0; i < input.size(); i++) {
        sum += input[i];
    }

    // I guess that this is supposed to bring up some kind of problem with
    // the typing here, but it seems fine.
    double result = sum / input.size();

    cout << setprecision(4) << result << endl;
}


int main() {
    // ex4_2_squares();
    // ex4_3_generalized_squares();
//    ex4_4_doubles();
    ex4_7_average();
}
