#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "handles.hh"

using std::max;
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
    friend ostream& operator<<(ostream& os, const Picture& picture);
    
private:
    using height_sz = vector<string>::size_type;
    using width_sz = string::size_type;

    virtual width_sz width() const;
    virtual height_sz height() const;

    virtual void display(ostream&, height_sz, bool) const = 0;
};

class StringPicture: public BasePicture {
    friend class Picture;
    
    StringPicture(const vector<string>& data): data(data) { }

    // The width of a string pic is the width of the longest string within
    // that picture.
    width_sz width() const {
        width_sz n = 0;
        for (height_sz i = 0; i != data.size(); i++) {
            n = max(n, data[i].size());
        }
        return n;
    }
    
    // A string pic is a vector of lines, so therefore its height is its
    // number of rows.
    height_sz height() const {
        return data.size();
    }
    
    void display(ostream& os, height_sz row, bool should_pad) const {
        width_sz start;

        // If we write a row, then start padding at the end of what we wrote.
        // Otherwise, just pad the whole line, so start at column zero.
        if (row < height()) {
            os << data[row];
            start = data[row].size();
        } else {
            start = 0;
        }

        if (should_pad) {
            pad(os, start, width());
        }
    }
    
    vector<string> data;
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
    friend ostream& operator<<(ostream& os, const Picture& picture);
    
public:
    Picture(
        const vector<string>& v= vector<string>()
    ): ptr(new StringPicture(v)) { }

private:
    Picture(BasePicture* raw_picture): ptr(raw_picture) { }
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

ostream& operator<<(ostream& os, const Picture& picture) {
    using height_sz = BasePicture::height_sz;
    height_sz height = picture.ptr->height();
    for (height_sz i = 0; i != height; i++) {
        picture.ptr->display(os, i, false);
        os << endl;
    }
    return os;
}

int main() {
    cout << "Starting." << endl;

    cout << "End." << endl;
    return 0;
}
