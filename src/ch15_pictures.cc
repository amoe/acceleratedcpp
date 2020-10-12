#include <iostream>
#include <vector>
#include <string>
#include "handles.hh"

using std::ostream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

class BasePicture {
    using height_sz = vector<string>::size_type;
    using width_sz = string::size_type;

    virtual width_sz width() const;
    virtual height_sz height() const;

    virtual void display(ostream&, height_sz, bool) const = 0;
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

Picture frame(const Picture&);
Picture hcat(const Picture&, const Picture&);
Picture vcat(const Picture&, const Picture&);
ostream& operator<<(ostream&, const Picture&);

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
