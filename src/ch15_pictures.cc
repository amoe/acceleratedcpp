#include <iostream>
#include <vector>
#include <string>
#include "handles.hh"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class BasePicture {
};

class StringPicture: public BasePicture {
};

class FramePicture: public BasePicture {
};

class VerticallyConcatenatedPicture: public BasePicture {
};

class HorizontallyConcatenatedPicture: public BasePicture {
};

class Picture {
public:
    Picture(const vector<string>& = vector<string>());

private:
    ControllableHandle<BasePicture> picture;
};



int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
