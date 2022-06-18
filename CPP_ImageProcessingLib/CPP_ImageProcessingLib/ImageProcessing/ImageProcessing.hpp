//
//  ImageProcessing.hpp
//  CPP_ImageProcessingLib
//
//  Created by Ancacion on 2022/6/18.
//

#ifndef ImageProcessing_hpp
#define ImageProcessing_hpp

#include <stdio.h>

static const int _512by512 = 262144; //圖片長寬 512 * 512, 需隨輸入圖片大小進行修正
static const int BMP_COLOR_TABLE_SIZE = 1024;
static const int BMP_HEADER_SIZE = 54;

class ImageProcessing
{
public:
    ImageProcessing(const char *_inImgName, const char *_outImgName, int *_height, int *_width, int *_bitDepth, unsigned char *_header, unsigned char *_colorTable, unsigned char *_inBuffer, unsigned char *_outBuffer);
    virtual ~ImageProcessing();
    void readImage();
    void writeImage();
    void copyImgData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize);
  
private:
    const char *inImgName;
    const char *outImgName;
    int *height;
    int *width;
    int *bitDepth;
    unsigned char *header;
    unsigned char *colorTable;
    unsigned char *inBuffer;
    unsigned char *outBuffer;
};

#endif /* ImageProcessing_hpp */
