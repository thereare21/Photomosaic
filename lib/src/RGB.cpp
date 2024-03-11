//
// Created by Raymond Tsai on 10/29/23.
//

#include "../include/RGB.h"
#include <cmath>

RGB::RGB(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

//compares blue, then green, then red
bool RGB::operator<(RGB *other) {

    if (this->blue == other->blue) {
        if (this->green == other->green) {
            return this->red < other->red;
        } else {
            return this->green < other->green;
        }
    } else {
        return this->blue < other->blue;
    }
}

bool RGB::operator>(RGB *other) {

    if (this->blue == other->blue) {
        if (this->green == other->green) {
            return this->red > other->red;
        } else {
            return this->green > other->green;
        }
    } else {
        return this->blue > other->blue;
    }

}

bool RGB::operator==(RGB* other) {

    return this->red == other->red
           && this->green == other->green
           && this->blue == other->blue;
}

double RGB::operator-(RGB* other) {
    //calculates the euclidian distance between this rgb value and the given rgb value
    //multiplied by weights to adjust for human color perception
    int dr = this->red - other->red;
    int dg = this->green - other->green;
    int db = this->blue - other->blue;

    double euclidianDistance = std::sqrt((dr * dr * 0.4) + (dg * dg * 0.4) + (db * db * 0.2));

    return euclidianDistance;
}

//calculates the euclidian value of the given RGB (no comparisons, just the value)
double calculateEuclidianDistance(RGB* thisRGB) {

    return (thisRGB->red) * 0.4
           + (thisRGB->green) * 0.4
           + (thisRGB->blue) * 0.2;
}

int RGB::getRed() {
    return red;
}

int RGB::getGreen() {
    return green;
}

int RGB::getBlue() {
    return blue;
}

void RGB::setRed(int red) {
    this->red = red;
}

void RGB::setGreen(int green) {
    this->green = green;
}

void RGB::setBlue(int blue) {
    this->blue = blue;
}

