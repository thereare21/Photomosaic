//
// Created by Raymond Tsai on 10/10/23.
//

#include "../include/Pixel.h"

Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
    grey = 0;
    alpha = 0;
}

//SETTERS
void Pixel::setRed(int rValue) {
    red = rValue; //maybe throw exception??
}

void Pixel::setGreen(int gValue) {
    green = gValue;
}

void Pixel::setBlue(int bValue) {
    blue = bValue;
}

void Pixel::setAlpha(int aValue) {
    alpha = aValue;
}

void Pixel::setGrey(int greyValue) {
    grey = greyValue;
}

//GETTERS
int Pixel::getRed() {
    return red;
}

int Pixel::getGreen() {
    return green;
}

int Pixel::getBlue() {
    return blue;
}

int Pixel::getAlpha() {
    return alpha;
}

int Pixel::getGrey() {
    return grey;
}





