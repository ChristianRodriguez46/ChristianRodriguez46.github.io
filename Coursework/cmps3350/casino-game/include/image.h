#ifndef IMAGE_H
#define IMAGE_H

class Image {
public:
    int width, height;
    unsigned char *data;

    ~Image() { delete [] data; }
    Image(const char *fname);
};

#endif
