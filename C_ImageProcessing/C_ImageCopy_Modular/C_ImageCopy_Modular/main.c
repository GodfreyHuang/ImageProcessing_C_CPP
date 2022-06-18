//
//  main.c
//  C_ImageCopy_Modular
//
//  Created by Ancacion on 2022/6/18.
//

#include <stdio.h>
#include <stdlib.h>

#define BMP_HEADER 54
#define BMP_COLOR_TABLE_SIZE 1024
#define CUSTUM_IMG_SIZE (1024 * 1024) //根據要複製圖片的大小而定

void imageReader(const char *imgName, int *_height, int *_width, int *_bitDepth, unsigned char *_header, unsigned char *_colorTable, unsigned char *_buffer);
void imageWriter(const char *imgName, unsigned char *header, unsigned char *colorTable, unsigned char *buffer, int bitDepth);

void imageReader(const char *imgName, int *_height, int *_width, int *_bitDepth, unsigned char *_header, unsigned char *_colorTable, unsigned char *_buffer) {
    int i = 0;
    FILE *streamIn = fopen(imgName, "rb"); //開檔
    
    if(!streamIn) { //若沒找到檔案輸出錯誤訊息
        printf("Unable to open file.\n");
    }
    else {
        for(i = 0; i < BMP_HEADER; i++) { //讀取BMP內的header
            _header[i] = getc(streamIn);
        }
        
        //                                width                  height             bitDepth
        // header記憶體第幾byte---> | 18 | 19 | 20 | 21 |  | 22 | 23 | 24 | 25 | ... | 28 | 29 |
        *_width = *(int *)&_header[18];
        *_height = *(int *)&_header[22];
        *_bitDepth = *(int *)&_header[28];
        
        printf("width = %d, height = %d, bitDepth = %d\n", *_width, *_height, *_bitDepth);
        
        if(*_bitDepth <= 32) { //滿足bitDepth的極值要求
            fread(_colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn); //讀取BMP的顏色資料
        }
        
        fread(_buffer, sizeof(unsigned char), CUSTUM_IMG_SIZE, streamIn); //讀取BMP的圖片資料
        fclose(streamIn); //關閉開檔
    }
}

void imageWriter(const char *imgName, unsigned char *header, unsigned char *colorTable, unsigned char *buffer, int bitDepth) {
    FILE *output = fopen(imgName, "wb"); //建立輸出圖片
    fwrite(header, sizeof(unsigned char), BMP_HEADER, output); //將複製過來的header寫入output
    
    if(bitDepth <= 32) {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, output); //複製顏色資料
    }
    fwrite(buffer, sizeof(unsigned char), CUSTUM_IMG_SIZE, output); //寫入圖片資料
    fclose(output); //關閉圖片
}

int main(int argc, const char * argv[]) {
    int imgWidth, imgHeight, imgBitDepth; //分別代表圖片的寬, 高, 每pixel需要多少bits
    unsigned char imgHeader[BMP_HEADER]; //BMP的header
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE]; //BMP顏色資料
    unsigned char imgBuffer[CUSTUM_IMG_SIZE]; //圖片的資料
    
    const char imgName[] =  "/Users/ancacion/Desktop/XcodeFile/C/C_ImageProcessing/C_ImageCopy_Modular/C_ImageCopy_Modular/images/man.bmp"; //被複製的圖片位置
    const char newImgName[] = "/Users/ancacion/Desktop/XcodeFile/C/C_ImageProcessing/C_ImageCopy_Modular/C_ImageCopy_Modular/images/man_copy.bmp"; //複製圖片的儲存位置
    
    imageReader(imgName, &imgHeight, &imgWidth, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgBuffer[0]); //讀取被複製圖片
    imageWriter(newImgName, imgHeader, imgColorTable, imgBuffer, imgBitDepth); //寫出複製圖片
    
    printf("Copy success.\n");
    
    return 0;
}
