//
// Created by Raymond Tsai on 10/10/23.
//


#include "../include/Image.h"
#include <cmath>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#endif

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../stb/stb_image_resize2.h"
#endif


#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"
#endif

//constructor for Image class, takes in input, output, and number of components.
Image::Image(int numComponents, const char* input, const char* output) {
    this->numComponents = numComponents;
    inputFile = input;
    outputFile = output;
    data = stbi_load(inputFile, &width, &height, &this->numComponents, 0);
    flattened = nullptr;
}

Image::Image(int width, int height, const char* output) {
    this->outputFile = output;
    reallocatePixels(width, height);
    flattened = nullptr;
    data = nullptr;
    this->numComponents = 3;
}

//copy constructor
Image::Image(const Image& other) {

    width = other.width;
    height = other.height;
    numComponents = other.numComponents;

    inputFile = other.inputFile;
    outputFile = other.outputFile;

    pixels = new Pixel* [height] {};
    for (int h = 0; h < height; h++) {
        pixels[h] = new Pixel[width];
    }

    if (data != nullptr) {

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixels[y][x] = Pixel();
                copyPixelData(pixels[y][x], other.pixels[y][x]);
            }
        }
    }
}

//destructor
Image::~Image() {
    freeAllPixelArrays();
}

//copy assignment operator
Image& Image::operator=(const Image& other) {
    if (this == &other) {
        return *this;
    } else {
        freeAllPixelArrays();

        width = other.width;
        height = other.height;
        numComponents = other.numComponents;

        inputFile = other.inputFile;
        outputFile = other.outputFile;

        pixels = new Pixel* [height] {};
        for (int h = 0; h < height; h++) {
            pixels[h] = new Pixel[width];
        }

        if (data != nullptr) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    pixels[y][x] = Pixel();
                    copyPixelData(pixels[y][x], other.pixels[y][x]);
                }
            }
        }
        return *this;
    }
}

//deallocates all relevant pixel data to be rewritten later on (pixels and flattened)
//if not already deallocated, deallocate flattened and data as well.
void Image::freeAllPixelArrays() {
    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
    }
    delete[] pixels;
    if (flattened != nullptr) {
        delete[] flattened;
    }
    if (data != nullptr) {
        delete[] data;
    }
}

//reads and sets Image data from the input file
void Image::read() {
    //initialize and allocate data
    pixels = new Pixel* [height] {};
    for (int h = 0; h < height; h++) {
        pixels[h] = new Pixel[width];
    }

    //make 2D array of Pixel objects
    if (data != nullptr) {

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (x + (y * width)) * numComponents;
                pixels[y][x] = Pixel();
                setPixelDataWhenRead(pixels[y][x], index);
            }
        }
    }
    delete[] data;
    data = nullptr;
}

//helper function for read(), sets the newPixel data to the corresponding values in data field.
void Image::setPixelDataWhenRead(Pixel &newPixel, int &index) {
    if (numComponents == 1) {
        newPixel.setGrey(data[index]);
    }
    else if (numComponents == 2) {
        newPixel.setGrey(data[index]);
        newPixel.setAlpha(data[index + 1]);
    }
    else if (numComponents == 3) {
        newPixel.setRed(data[index]);
        newPixel.setGreen(data[index + 1]);
        newPixel.setBlue(data[index + 2]);
    }
    else if (numComponents == 4) {
        newPixel.setRed(data[index]);
        newPixel.setGreen(data[index + 1]);
        newPixel.setBlue(data[index + 2]);
        newPixel.setAlpha(data[index + 3]);
    }
}

//writes this Image to the output file.
void Image::write() {
    //flatten 2d array
    flattened = new unsigned char[width * height * numComponents];
    flattenArray();
    //write
    stbi_write_jpg(
    outputFile, width, height, numComponents, flattened, 10000);
}

//flattens the 2D array of pixels
void Image::flattenArray() {
    int index = 0;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            addPixelDataToFlattened(index, pixels[h][w]);
        }
    }
}

//helper function for flattenArray, adds the given pixel's data to the flattened array
void Image::addPixelDataToFlattened(int& index, Pixel& pixelToLook) {
    if (numComponents == 1) {
        flattened[index++] = (unsigned char)pixelToLook.getGrey();
    }
    else if (numComponents == 2) {
        flattened[index++] = (unsigned char)pixelToLook.getGrey();
        flattened[index++] = (unsigned char)pixelToLook.getAlpha();
    }
    else if (numComponents == 3) {
        flattened[index++] = (unsigned char)pixelToLook.getRed();
        flattened[index++] = (unsigned char)pixelToLook.getGreen();
        flattened[index++] = (unsigned char)pixelToLook.getBlue();

    }
    else if (numComponents == 4) {
        flattened[index++] = (unsigned char)pixelToLook.getRed();
        flattened[index++] = (unsigned char)pixelToLook.getGreen();
        flattened[index++] = (unsigned char)pixelToLook.getBlue();
        flattened[index++] = (unsigned char)pixelToLook.getAlpha();
    }
}

//TRANSFORM FUNCTIONS
//flips along the horizontal axis
void Image::flipHorizontal() {
    //initialize new array of data
    Pixel** newPixels = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        newPixels[i] = new Pixel[width];
    }
    //reads pixels from bottom row to top row, sets newPixels from top row to bottom row, thus transforming it
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            newPixels[y][x] = pixels[height - y - 1][x];
        }
    }
    //clear all pixel data from before
    reallocatePixels(width, height);
    copyToPixels(newPixels);
}

//flips image along the vertical axis
void Image::flipVertical() {
    Pixel** newPixels = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        newPixels[i] = new Pixel[width];
    }

    //read every row from right to left, writes data left to right
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            newPixels[y][x] = pixels[y][width - x - 1];
        }
    }

    //clear all pixel data and flattened pixels from before
    reallocatePixels(width, height);
    copyToPixels(newPixels);
}

//flips the image ninety degrees. Pass in true to rotate +90 degrees, false for -90 degrees.
void Image::flipNinety(bool isPlus) {
    Pixel** newPixels = new Pixel*[width];
    for (int i = 0; i < width; i++) {
        newPixels[i] = new Pixel[height];
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isPlus) {
                newPixels[x][y] = pixels[height - y - 1][x];
            } else {
                newPixels[x][y] = pixels[y][x];
            }
        }
    }
    reallocatePixels(height, width);
    copyToPixels(newPixels);
}

//adds a border with user specified color and border width to the image.
void Image::border() {
    Pixel borderPixel;
    promptUserForBorderColors(borderPixel);
    int borderWidth;
    std::cout << "Enter border width: ";
    std::cin >> borderWidth;
    int newWidth = width + borderWidth * 2;
    int newHeight = height + borderWidth * 2;
    Pixel** newPixels = new Pixel*[newHeight];
    for (int i = 0; i < newHeight; i++) {
        newPixels[i] = new Pixel[newWidth];
    }
    //construct the new 2d array - if pixel position is at border, make it the border pixel, if not, copy from
    //pixels array
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            if (y < borderWidth || y >= newHeight - borderWidth
                || x < borderWidth || x >= newWidth - borderWidth) {
                newPixels[y][x] = borderPixel;
            } else {
                newPixels[y][x] = pixels[y - borderWidth][x - borderWidth];
            }
        }
    }
    reallocatePixels(newWidth, newHeight);
    copyToPixels(newPixels);
}

//creates a pointillism effect on the image.
void Image::pointillize() {
    Pixel** newPixels = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        newPixels[i] = new Pixel[width];
    }
    int pointRadius = (std::rand() % 5) + 1; //the size of the point (random size from 1 to 5)
    for (int y = 0; y < height; y += pointRadius * 2) {
        for (int x = 0; x < width; x += pointRadius * 2) {
            pointRadius = (std::rand() % 5) + 1;
            //picks a random pixel from within the point to call the center pixel
            int randX = x + std::rand() % (pointRadius * 2);
            int randY = y + std::rand() % (pointRadius * 2);
            Pixel centerPixel = pixels[std::min(randY, height - 1)][std::min(randX, width - 1)];
            for (int i = y; i < std::min(y + pointRadius * 2, height); i++) {
                for (int j = x; j < std::min(x + pointRadius * 2, width); j++) {
                    int dx = j - randX;
                    int dy = i - randY;
                    //formula for circle: (y - k)^2 + (x - h)^2 = r^2. Checks if given point is within random point's radius.
                    if (dx * dx + dy * dy <= pointRadius * pointRadius) {
                        copyPixelData(newPixels[i][j], centerPixel);
                    }
                }
            }
        }
    }
    reallocatePixels(width, height);
    copyToPixels(newPixels);
}

//TRANSFORM FUNCTIONS FOR MOSAIC
//resize must be called before read() in order to work
void Image::resize(int sideLength) {

    //calls resize function with the given side length
    unsigned char* newData = stbir_resize_uint8_srgb(data, width, height, width * 3,
                            nullptr, sideLength, sideLength, sideLength * 3,
                            static_cast<stbir_pixel_layout>(STBIR_RGB));

    //update data
    delete[] data;
    data = newData;

    //change the width and height of the image
    this->width = sideLength;
    this->height = sideLength;
}

RGB* Image::calculateAverageRGB() {
    RGB* average = new RGB(0, 0, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            average->setRed(average->getRed() + pixels[y][x].getRed());
            average->setGreen(average->getGreen() + pixels[y][x].getGreen());
            average->setBlue(average->getBlue() + pixels[y][x].getBlue());
        }
    }
    average->setRed(average->getRed() / (width * height));
    average->setGreen(average->getGreen() / (width * height));
    average->setBlue(average->getBlue() / (width * height));
    return average;
}


/********************************/

//copies all relevant pixel data from the toCopy pixel to the copied Pixel
void Image::copyPixelData(Pixel& copied, Pixel& toCopy) {
    if (numComponents == 1) {
        copied.setGrey(toCopy.getGrey());
    } else if (numComponents == 2) {
        copied.setGrey(toCopy.getGrey());
        copied.setAlpha(toCopy.getAlpha());
    } else if (numComponents == 3) {
        copied.setRed(toCopy.getRed());
        copied.setGreen(toCopy.getGreen());
        copied.setBlue(toCopy.getBlue());
    } else if (numComponents == 4) {
        copied.setRed(toCopy.getRed());
        copied.setGreen(toCopy.getGreen());
        copied.setBlue(toCopy.getBlue());
        copied.setGrey(toCopy.getGrey());
    }
}

//reallocates pixels array with new width and height, and frees all existing arrays
void Image::reallocatePixels(int newWidth, int newHeight) {
    //deallocate existing data
    freeAllPixelArrays();

    //modify width and height parameters to reference when writing
    width = newWidth;
    height = newHeight;

    //re-initialize data to get new width and height
    pixels = new Pixel* [height] {};
    for (int h = 0; h < height; h++) {
        pixels[h] = new Pixel[width];
    }
}

//helper for border function, prompts user for border colors
void Image::promptUserForBorderColors(Pixel& border) {
    int grey;
    int alpha;
    int red;
    int green;
    int blue;
    if (numComponents == 1) {
        std::cout << "Enter grey value of border: " << std::endl;
        std::cin >> grey;
        border.setGrey(grey);
    } else if (numComponents == 2) {
        std::cout << "Enter grey value of border: " << std::endl;
        std::cin >> grey;
        border.setGrey(grey);
        std::cout << "Enter alpha value of border: " << std::endl;
        std::cin >> alpha;
        border.setAlpha(alpha);
    } else if (numComponents == 3) {
        std::cout << "Enter red value of border: " << std::endl;
        std::cin >> red;
        border.setRed(red);
        std::cout << "Enter green value of border: " << std::endl;
        std::cin >> green;
        border.setGreen(green);
        std::cout << "Enter blue value of border: " << std::endl;
        std::cin >> blue;
        border.setBlue(blue);
    } else if (numComponents == 4) {
        std::cout << "Enter red value of border: " << std::endl;
        std::cin >> red;
        border.setRed(red);
        std::cout << "Enter green value of border: " << std::endl;
        std::cin >> green;
        border.setGreen(green);
        std::cout << "Enter blue value of border: " << std::endl;
        std::cin >> blue;
        border.setBlue(blue);
        std::cout << "Enter alpha value of border: " << std::endl;
        std::cin >> alpha;
        border.setAlpha(alpha);
    }
}

//copies the data from newPixels to pixels field, deallocates newPixels
void Image::copyToPixels(Pixel** newPixels) {
    //copy data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y][x] = newPixels[y][x];
        }
    }
    //deallocate newPixels array
    for (int i = 0; i < height; i++) {
        delete[] newPixels[i];
    }
    delete[] newPixels;
}


