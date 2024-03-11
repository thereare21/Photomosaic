//
// Created by Raymond Tsai on 10/29/23.
//

#ifndef PHOTOMOSAIC_RGB_H
#define PHOTOMOSAIC_RGB_H

#include <iostream>

//class to represennt an RGB value
class RGB {
public:

    RGB(int red, int green, int blue);

    //compare red. if red is the same, compare green. if green is the same, compare blue.
    bool operator<(RGB* other);

    bool operator>(RGB* other);

    bool operator==(RGB* other);

    double operator-(RGB* other);

    friend double calculateEuclidianDistance(RGB* thisRGB);

    int getRed();
    int getGreen();
    int getBlue();

    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    friend std::ostream& operator<<(std::ostream& os, RGB* obj) {
        os << "RGB(red=" << obj->getRed() << " green=" << obj->getGreen() << " blue=" << obj->getBlue() << ")";
        return os;
    }

private:
    int red;
    int green;
    int blue;


};






#endif //PHOTOMOSAIC_RGB_H
