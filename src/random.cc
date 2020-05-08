#include <cstdlib>

int nrand(int n) {
    return (int)((double)rand() / ((double)RAND_MAX + 1) * n);
}
