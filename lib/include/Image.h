//
// Created by Raymond Tsai on 10/10/23.
//

#include "string"
#include "Pixel.h"
#include "RGB.h"

#ifndef IMAGELIB_IMAGE_H
#define IMAGELIB_IMAGE_H


class Image {
public:
    const char* inputFile;
    const char* outputFile;
    unsigned char* data;
    unsigned char* flattened;
    int numComponents;
    int width;
    int height;
    Pixel** pixels;

    //constructor
    explicit Image(int numComponents, const char* input, const char* output);

    //constructor for constructing a blank image from scratch
    Image(int width, int height, const char* output);

    //destructor
    ~Image();

    //copy constructor
    Image(const Image& other);

    //copy assignment operator
    Image& operator=(const Image& other);

    //read
    void read();

    //write
    void write();

    //transform functions
    void flipHorizontal();
    void flipVertical();
    void flipNinety(bool isPlus);
    void border();
    void pointillize();

    //functions for Mosaic

    //resizes the image to a square with the given side length
    void resize(int sideLength);
    //calculates the average RGB of the image
    RGB * calculateAverageRGB();

private:

    void setPixelDataWhenRead(Pixel &newPixel, int &index);
    void flattenArray();
    void addPixelDataToFlattened(int& index, Pixel& pixelToLook);

    void copyPixelData(Pixel& copied, Pixel& toCopy);

    void reallocatePixels(int newWidth, int newHeight);

    void promptUserForBorderColors(Pixel& border);

    //void calculateAverageColor(Pixel& pixel, int* averageColor);

    void freeAllPixelArrays();

    void copyToPixels(Pixel** newPixels);
    //void setPixelColorToAverageColor(Pixel& newPixel, int* averageColor);
};


#endif //IMAGELIB_IMAGE_H
