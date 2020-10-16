#include <iostream>
#include <vector>
#include <string>
#include "handles.hh"

using std::ostream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

// fwd declaration neeeded otherwise friend declaration fails
class Picture;

// Implementation classes -- These classes implement the operations but should
// remain invisible.

class BasePicture {
    friend class StringPicture;
    friend class FramePicture;
    friend class VerticallyConcatenatedPicture;
    friend class HorizontallyConcatenatedPicture;
    
private:
    using height_sz = vector<string>::size_type;
    using width_sz = string::size_type;

    virtual width_sz width() const;
    virtual height_sz height() const;

    virtual void display(ostream&, height_sz, bool) const = 0;
};

class StringPicture: public BasePicture {
    StringPicture(const vector<string>& data): data(data) { }
    vector<string> data;
    
    width_sz width() const;
    height_sz height() const;
    void display(ostream&, height_sz, bool) const;
};

class FramePicture: public BasePicture {
   friend Picture frame(const Picture&);
    
private:
    FramePicture(
        const ControllableHandle<BasePicture>& picture
    ): picture(picture) { }
    
    ControllableHandle<BasePicture> picture;

    width_sz width() const;
    height_sz height() const;
    void display(ostream&, height_sz, bool) const;
};

class VerticallyConcatenatedPicture: public BasePicture {
    friend Picture vcat(const Picture&, const Picture&);
    
    VerticallyConcatenatedPicture(
        const ControllableHandle<BasePicture>& top,
        const ControllableHandle<BasePicture>& bottom
    ): top(top), bottom(bottom) { }
    
    ControllableHandle<BasePicture> top;
    ControllableHandle<BasePicture> bottom;
    
    width_sz width() const;
    height_sz height() const;
    void display(ostream&, height_sz, bool) const;
};

class HorizontallyConcatenatedPicture: public BasePicture {
    friend Picture hcat(const Picture&, const Picture&);
    
    HorizontallyConcatenatedPicture(
        const ControllableHandle<BasePicture>& left,
        const ControllableHandle<BasePicture>& right
    ): left(left), right(right) { }
    
    ControllableHandle<BasePicture> left;
    ControllableHandle<BasePicture> right;
    
    width_sz width() const;
    height_sz height() const;
    void display(ostream&, height_sz, bool) const;
};

// Interface classes and functions.

class Picture {
    friend Picture frame(const Picture& picture);
    friend Picture hcat(const Picture&, const Picture&);
    friend Picture vcat(const Picture&, const Picture&);
    
public:
    Picture(const vector<string>& = vector<string>());

    // XXX: abstraction violation?
    Picture(BasePicture* raw_picture): ptr(raw_picture) { }

private:
    ControllableHandle<BasePicture> ptr;
};

// XXX: MAGIC HAPPENING HERE!  Return type is automatically converted to Picture
// using the `BasePicture*` constructor of Picture.
Picture frame(const Picture& picture) {
    return new FramePicture(picture.ptr);
}

Picture hcat(const Picture& left, const Picture& right) {
    return new HorizontallyConcatenatedPicture(left.ptr, right.ptr);
}

Picture vcat(const Picture& left, const Picture& right) {
    return new VerticallyConcatenatedPicture(left.ptr, right.ptr);
}

ostream& operator<<(ostream&, const Picture&);

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
