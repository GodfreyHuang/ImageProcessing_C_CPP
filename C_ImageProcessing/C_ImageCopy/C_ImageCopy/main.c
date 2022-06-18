//
//  main.c
//  C_ImageCopy
//
//  Created by Ancacion on 2022/6/18.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    //const char* filename = "images/cameraman.bmp";
    //FILE *streamIn = fopen(filename, "rb");
    FILE *streamIn = fopen("/Users/ancacion/Desktop/XcodeFile/C/C_ImageProcessing/C_ImageCopy/C_ImageCopy/images/cameraman.bmp", "rb");
    FILE *fOut = fopen("/Users/ancacion/Desktop/XcodeFile/C/C_ImageProcessing/C_ImageCopy/C_ImageCopy/images/copy.bmp", "wb");
    //FILE *streamIn = fopen("./images/cameraman.bmp", "rb");
    //FILE *fOut = fopen("./images/copy.bmp", "wb");
    
    if(!streamIn) { //streamIn == (FILE*)0
        printf("Unable to open file.\n");
        return -1;
    }
    
    unsigned char header[54]; //BMP header
    unsigned char colorTable[1024]; //BMP data
    
    for(int i = 0; i < 54; i++) {
        header[i] = getc(streamIn);
    }
    
    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bitDepth = *(int *)&header[28];
    
    printf("width = %d, height = %d, bitDepth = %d\n", width, height, bitDepth);
    
    if(bitDepth <= 8) {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }
    
    fwrite(header, sizeof(unsigned char), 54, fOut);
    unsigned char buffer[height * width];
    fread(buffer, sizeof(unsigned char), (height * width), streamIn);
    
    if(bitDepth <= 8) {
        fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
    }
    fwrite(buffer, sizeof(unsigned char), (height * width), fOut);
    fclose(fOut);
    fclose(streamIn);
    
    printf("Copy success.\n");
    
    return 0;
}
