//
//  ImageProcessing.cpp
//  CPP_ImageProcessingLib
//
//  Created by Ancacion on 2022/6/18.
//
#include <iostream>

#include "ImageProcessing.hpp"

using namespace std;

ImageProcessing::ImageProcessing(const char *_inImgName, const char *_outImgName, int *_height, int *_width, int *_bitDepth, unsigned char *_header, unsigned char *_colorTable, unsigned char *_inBuffer, unsigned char *_outBuffer) {
    inImgName = _inImgName;
    outImgName = _outImgName;
    height = _height;
    width = _width;
    bitDepth = _bitDepth;
    header = _header;
    colorTable = _colorTable;
    inBuffer = _inBuffer;
    outBuffer = _outBuffer;
}

ImageProcessing::~ImageProcessing() {
    
}

void ImageProcessing::readImage() {
    int i;
    FILE *streamIn;
    streamIn = fopen(inImgName, "rb");
    
    if(!streamIn) {
        cout << "Unable to open file.\n" << endl;
        exit(0);
    }
    else {
        for(i = 0; i < BMP_HEADER_SIZE; i++) {
            header[i] = getc(streamIn);
        }
        *width = *(int *)&header[18];
        *height = *(int *)&header[22];
        *bitDepth = *(int *)&header[28];
        
        if(*bitDepth == 1 || *bitDepth == 4 || *bitDepth == 8 || *bitDepth == 24) {
            fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
        }
        fread(inBuffer, sizeof(unsigned char), _512by512, streamIn);
        fclose(streamIn);
    }
}

void ImageProcessing::writeImage() {
    FILE *output;
    output = fopen(outImgName, "wb");
    
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, output);
    
    if(*bitDepth == 1 || *bitDepth == 4 || *bitDepth == 8 || *bitDepth == 24) {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, output);
    }
    
    //copyImgData(inBuffer, outBuffer, _512by512);
    fwrite(outBuffer, sizeof(unsigned char), _512by512, output);
    fclose(output);
}

void ImageProcessing::copyImgData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize) {
    for(int i = 0; i < bufSize; i++) {
        _destBuf[i] = _srcBuf[i];
    }
}
