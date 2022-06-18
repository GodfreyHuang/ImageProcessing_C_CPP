//
//  main.cpp
//  CPP_ImageProcessingLib
//
//  Created by Ancacion on 2022/6/18.
//

#include <iostream>

#include "ImageProcessing.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    const char inImgName[] = "/Users/ancacion/Desktop/XcodeFile/C++/CPP_ImageProcessingLib/CPP_ImageProcessingLib/images/girlface.bmp";
    const char outImgName[] = "/Users/ancacion/Desktop/XcodeFile/C++/CPP_ImageProcessingLib/CPP_ImageProcessingLib/images/girlfaceCopy.bmp";
    int imgHeight = 0;
    int imgWidth = 0;
    int imgBitDepth = 0;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512];
    unsigned char imgOutBuffer[_512by512];
    
    ImageProcessing *newImage = new ImageProcessing(inImgName, outImgName, &imgHeight, &imgWidth, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgInBuffer[0], &imgOutBuffer[0]);
    
    newImage -> readImage();
    newImage -> copyImgData(imgInBuffer, imgOutBuffer, _512by512);
    newImage -> writeImage();
    cout << "Copy success.\n" << endl;
    cout << "Image's height : " << imgHeight << endl;
    cout << "Image's width: " << imgWidth << endl;
    
    return 0;
}
