#include <iostream>
#include <cstdlib>
#include <climits>

using std::cout;
using std::endl;

int nrand(int n) {
    if (n <= 0 or n > RAND_MAX)
        throw std::domain_error("no");

    const int bucket_size = RAND_MAX / n;
//    cout << "bucket size is " << bucket_size << endl;

    int r;

    do {
        // rand() returns a value in the range of RAND_MAX.
        // So given that 
        int generated_random_value = rand();
//        cout << "generated " << generated_random_value  << endl;
        
        r = generated_random_value / bucket_size;
//        cout  << "r is " <<  r << endl;
    } while (r >= n);

    return r;
}

int main() {
    cout << "Hello, world!" << endl;
    cout << "RAND_MAX is " << RAND_MAX << endl;
    cout << "INT_MAX is " << INT_MAX << endl;
    
    cout << "nrand(100) = " << nrand(100) << endl;

    cout << "nrand(32766) = " << nrand(32766) << endl;
    cout << "nrand(32767) = " << nrand(32767) << endl;
    cout << "nrand(32768) = " << nrand(32768) << endl;

    return 0;
}
