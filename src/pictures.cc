#include "pictures.hh"

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
