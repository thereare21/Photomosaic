//
// Created by Raymond Tsai on 10/29/23.
//

#ifndef PHOTOMOSAIC_MOSAIC_H
#define PHOTOMOSAIC_MOSAIC_H

#include "Image.h"
#include "AVLMap.h"


class Mosaic {
public:

    //takes in directories of all 3 needed elements, sets respective variables
    Mosaic(const char* inputPath, const char* srcImgLibPath, const char* outputPath);

    //processes each image in the source library with the given resolution and
    //adds them to the AVLMap
    void processSourceImageLibrary(int resolution);

    //creates the mosaic from the processed images in the AVLMap
    //must be called after processSourceImageLibrary
    void createMosaic();

private:
    const char* inputPath;
    const char* srcImgLibPath;
    const char* outputPath;

    Image inputImage;
    AVLMap<RGB*, Image*> processedImages;
    Image* mosaic;

    int resolution;

    //helper for createMosaic - replaces a chunk of pixels with the processed image
    //with the closest average color to the corresponding chunk in the input image.
    void replacePixelsInChunkWithImage(int xOfTopLeft, int yOfTopLeft, Image& pImage);

    //helper for processSourceImageLibrary - processes a given directory of source images
    void processSourceImageDirectory(const char* dir);

    //helper for processSourceImageLibrary - processes a single source image
    void processSourceImage(const char* path);
};


#endif //PHOTOMOSAIC_MOSAIC_H
