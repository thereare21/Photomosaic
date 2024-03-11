//
// Created by Raymond Tsai on 10/29/23.
//

#include "../include/Mosaic.h"
#include <filesystem>

//constructor for a Mosaic, takes in path for input, source image library, and output
Mosaic::Mosaic(const char* inputPath, const char* srcImgLibPath, const char* output)
        : inputImage(3, inputPath, ""){
    this->inputPath = inputPath;
    this->srcImgLibPath = srcImgLibPath;
    this->outputPath = output;
    this->resolution = 100;
    inputImage.read();
}

void Mosaic::processSourceImageLibrary(int resolution) {
    namespace fs = std::filesystem;
    this->resolution = resolution;

    //iterate through every Image in the srcImgLibDirectory
    for (const auto& entry : fs::directory_iterator(srcImgLibPath)) {

        //initialize the current Image
        if (fs::is_directory(entry)) {
            processSourceImageDirectory(entry.path().c_str());
        }
        processSourceImage(entry.path().c_str());
    }
}

void Mosaic::processSourceImageDirectory(const char* dir) {
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(dir)) {

        //initialize the current Image
        if (fs::is_directory(entry)) {
            processSourceImageDirectory(entry.path().c_str());
        }

        processSourceImage(entry.path().c_str());

    }
}

void Mosaic::processSourceImage(const char* path) {
    Image* curImage = new Image(3, path, "");
    curImage->resize(this->resolution);
    //curImage.squarify(sideLength);

    curImage->read();

    RGB* averageRGB = curImage->calculateAverageRGB();
    //std::cout << path << " " << averageRGB << std::endl;
    this->processedImages.insert(averageRGB, curImage);
}



void Mosaic::createMosaic() {
    //initialize the mosaic
    mosaic = new Image(inputImage.width / resolution * resolution,
               inputImage.height / resolution * resolution, outputPath);

    //iterate through every chunk of size 60
    for (int y = 0; y < mosaic->height; y += resolution) {
        for (int x = 0; x < mosaic->width; x += resolution) {
            Pixel centerPixel = inputImage.pixels[y + resolution / 2][x + resolution / 2];
            RGB* centerPixelColor = new RGB(centerPixel.getRed(), centerPixel.getGreen(), centerPixel.getBlue());
            //std::cout << centerPixel.getRed() << " " << centerPixelColor << " " << x << " " << y << std::endl;
            Image* closestImage = processedImages.search(centerPixelColor);
            replacePixelsInChunkWithImage(x, y, *closestImage);
        }
    }
    mosaic->write();
}

void Mosaic::replacePixelsInChunkWithImage(int xOfTopLeft, int yOfTopLeft, Image& closestImage) {
    for (int currY = 0; currY < resolution; currY++) {
        for (int currX = 0; currX < resolution; currX++) {
            mosaic->pixels[currY + yOfTopLeft][currX + xOfTopLeft] = closestImage.pixels[currY][currX];
        }
    }
}
