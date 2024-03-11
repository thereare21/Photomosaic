//
// Created by Raymond Tsai on 11/1/23.
//

#include "../include/Driver.h"
#include "../include/Mosaic.h"
#include <iostream>

//runs the driver program
void Driver::run() {
    while (true) {
        std::cout << "Welcome to Raymond's Photomosaic program! Press 1 to start or q to quit." << std::endl;
        char input;
        std::cin >> input;

        if (input == '1') {
            std::string inputImage;
            std::string sourceLibrary;
            std::string outputPath;
            int resolution;
            std::cout << "Enter the input image file path" << std::endl;
            std::cin >> inputImage;
            std::cout << "Enter the source image library path" << std::endl;
            std::cin >> sourceLibrary;
            std::cout << "Enter the output image path" << std::endl;
            std::cin >> outputPath;
            std::cout << "Enter the resolution (size of each image)" << std::endl;
            std::cin >> resolution;

            Mosaic m(inputImage.c_str(), sourceLibrary.c_str(), outputPath.c_str());
            m.processSourceImageLibrary(resolution);
            m.createMosaic();
            std::cout << "Mosaic has been created!" << std::endl;
        } else if (input == 'q') {
            std::cout << "Thanks for using this program!" << std::endl;
            break;
        }
    }
}
