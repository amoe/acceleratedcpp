#ifndef PICTURES_HH
#define PICTURES_HH

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

    width_sz width() const {
        width_sz n = 0;
        for (height_sz i = 0; i != data.size(); i++) {
            n = max(n, data[i].size());
        }
        return n;
    }
    
    height_sz height() const {
        return data.size();
    }
    
    void display(ostream& os, height_sz row, bool should_pad) const {
        width_sz start;

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
            os << string(width(), '*');
        } else if (row == 1 || row == height() - 2) {
            os << "*";
            pad(os, 1, width() - 1);
            os << "*";
        } else {
            os << "* ";
            picture->display(os, row - 2, true);
            os << " *";
        }
    }

    ControllableHandle<BasePicture> picture;
};

class VerticallyConcatenatedPicture: public BasePicture {
    friend Picture vcat(const Picture&, const Picture&);
    
    VerticallyConcatenatedPicture(
        const ControllableHandle<BasePicture>& top,
        const ControllableHandle<BasePicture>& bottom
    ): top(top), bottom(bottom) { }
    
    
    width_sz width() const {
        return max(top->width(), bottom->width());
    }
    
    height_sz height() const {
        return top->height() + bottom->height();
    }
    
    void display(ostream& os, height_sz row, bool should_pad) const {
        width_sz start;
        
        if (row < top->height()) {
            top->display(os, row, should_pad);
            start = top->width();
        } else {
            bottom->display(os, row - top->height(), should_pad);
            start = bottom->width();
        }

        if (should_pad)
            pad(os, start, width());
    }
    
    ControllableHandle<BasePicture> top;
    ControllableHandle<BasePicture> bottom;
};

class HorizontallyConcatenatedPicture: public BasePicture {
    friend Picture hcat(const Picture&, const Picture&);
    
    HorizontallyConcatenatedPicture(
        const ControllableHandle<BasePicture>& left,
        const ControllableHandle<BasePicture>& right
    ): left(left), right(right) { }
    

    width_sz width() const {
        return left->width() + right->width();
    }
    
    height_sz height() const {
        return max(left->height(), right->height());
    }
    
    void display(ostream& os, height_sz row, bool should_pad) const {
        bool should_pad_left = should_pad;

        if (row < right->height()) {
            should_pad_left = true;
        }
        
        left->display(os, row, should_pad_left);
        right->display(os, row, should_pad);
    }


    ControllableHandle<BasePicture> left;
    ControllableHandle<BasePicture> right;
};

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

#endif /* PICTURES_HH */

