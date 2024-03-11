//
// Created by Raymond Tsai on 10/10/23.
//

#ifndef IMAGELIB_PIXEL_H
#define IMAGELIB_PIXEL_H
#endif //IMAGELIB_PIXEL_H

class Pixel {

public:

    Pixel();

    void setRed(int rValue);
    void setGreen(int gValue);
    void setBlue(int bValue);
    void setAlpha(int aValue);
    void setGrey(int greyValue);

    int getRed();
    int getGreen();
    int getBlue();
    int getAlpha();
    int getGrey();

private:
    int red;
    int green;
    int blue;
    int alpha;
    int grey;

};
