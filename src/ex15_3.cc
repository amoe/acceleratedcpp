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

class Picture;


class BasePicture {
    friend class FramePicture;
    friend class VerticallyConcatenatedPicture;
    friend class HorizontallyConcatenatedPicture;
    friend ostream& operator<<(ostream& os, const Picture& picture);

protected:
    using height_sz = vector<string>::size_type;
    using width_sz = string::size_type;
    static void pad(ostream& os, width_sz begin, width_sz end) {
        while (begin != end) {
            os << " ";
            begin++;
        }
    }
    
private:
    virtual width_sz width() const = 0;
    virtual height_sz height() const = 0;
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
   friend Picture frame(const Picture&, char, char, char);
    
private:
    FramePicture(
        const ControllableHandle<BasePicture>& picture, char top_border,
        char side_border, char corner_border
    ): picture(picture), top_border(top_border), side_border(side_border),
       corner_border(corner_border) { }
    

    width_sz width() const {
        return picture->width() + 4;
    }
    
    height_sz height() const {
        return picture->height() + 4;
    }


    void display(ostream& os, height_sz row, bool should_pad) const {
        if (row >= height()) {
            if (should_pad) {
                pad(os, 0, width());
                return;
            }
        }

        if (row == 0 || row == height() - 1) {
            os << corner_border;
            os << string(width() - 2, top_border);
            os << corner_border;
        } else if (row == 1 || row == height() - 2) {
            os << side_border;
            pad(os, 1, width() - 1);
            os << side_border;
        } else {
            os << "| ";
            picture->display(os, row - 2, true);
            os << " |";
        }
    }

    ControllableHandle<BasePicture> picture;
    char top_border;
    char side_border;
    char corner_border;
};
// Interface classes and functions.

class Picture {
    friend Picture frame(const Picture&, char, char, char);
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

Picture frame(const Picture& picture, char top_border, char side_border, char corner_border) {
    return new FramePicture(picture.ptr, top_border, side_border, corner_border);
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

    vector<string> initial_text = {"Hello, world!", "Keep on truckin'!"};
    Picture p(initial_text);
    Picture q = frame(p, '*', '|', '*');

    cout << q;
    
    cout << "End." << endl;
    return 0;
}
