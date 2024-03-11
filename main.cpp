//
// Created by Raymond Tsai on 10/29/23.
//

#include "Mosaic.h"
#include "Driver.h"

//Main program
//Run with 0 arguments to run driver program
//To create a mosaic, create a Mosaic object and call processSourceImageLibrary with
//the resolution as a parameter. Then call createMosaic().
int main(int argc, char* argv[]) {
    if (argc == 1) {
        Driver d;
        d.run();
    } else if (argc == 2) {
        Mosaic m("sampleImages/balloon.jpeg",
                 "sampleImages/borzoisAbridged",
                 "sampleImages/balloonBorzoified.jpg");
        m.processSourceImageLibrary(30);
        m.createMosaic();
    } else if (argc == 4) {
        Mosaic m(argv[1], argv[2], argv[3]);
        m.processSourceImageLibrary(20);
        m.createMosaic();
    }
}