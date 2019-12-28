#include <iostream>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <stdexcept>

using std::cout;
using std::endl;
using std::domain_error;

#define MY_RAND_MAX 32767

// A recursive solution by K&M.  I have to confess I don't understand it.
int nrand(int n) {
    if (n <= 0)
        throw std::domain_error("no");

    int r;
    if (n <= MY_RAND_MAX) {
        const int bucket_size = MY_RAND_MAX / n;

        do {
            r = rand() / bucket_size;
        } while (r >= n);
    } else {
        const int bucket_size = ceil(n / MY_RAND_MAX);
        
        do {
            const int bucket = nrand(MY_RAND_MAX);
            const int remainder = nrand(bucket_size);
            r = (bucket - 1) * bucket_size + remainder;
        } while (r >= n);
    }

    return r;
}



int main() {
    srand(time(NULL));

    cout << "Hello, world!" << endl;
    cout << "MY_RAND_MAX is " << MY_RAND_MAX << endl;
    
    cout << "nrand(100) = " << nrand(100) << endl;

    cout << "nrand(32766) = " << nrand(32766) << endl;
    cout << "nrand(32767) = " << nrand(32767) << endl;
    cout << "nrand(32768) = " << nrand(32768) << endl;

    cout << "nrand(50000) = " << nrand(50000) << endl;

    return 0;
}
