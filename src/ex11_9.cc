#include <iostream>
#include "ex11_9.hh"

using std::cout;
using std::endl;

class CopyCounter {
public:
    CopyCounter(): copies(0) { }

    void increment() {
        copies++;
    }

    int get_count() {
        return copies;
    }

private:
    int copies;
};

class IntWrapper {
public:
    IntWrapper(CopyCounter& counter, int x): counter(counter), x(x) { }

    IntWrapper(const IntWrapper& rhs): counter(rhs.counter), x(rhs.x) {
        counter.increment();
    }

    int get() const {
        return x;
    }

private:
    CopyCounter& counter;
    int x;
};

int main() {
    cout << "Starting." << endl;

    CopyCounter c;
    Vec<IntWrapper> container;

    // See exercise notes for the stats that come out of this.
    for (int i = 0; i < 10000000; i++) {
        IntWrapper x(c, i);
        container.push_back(x);
    }

    cout << "Copy count: " << c.get_count() << endl;

    cout << "End." << endl;
    return 0;
}
