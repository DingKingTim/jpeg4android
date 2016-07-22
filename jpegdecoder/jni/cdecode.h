//
// Created by dk on 16/3/21.
//

#ifndef _CDECODE_H_
#define _CDECODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct JpegDecode_s JpegDecode;

struct JpegDecode_s { 
    int width;
    int height;
    int depth;
    int row_width;
    unsigned char* data;

    int (*decode_mem)(JpegDecode *obj, char *data, int size);
    int (*decode_file)(JpegDecode *obj, const char *file);
    int (*getWidth)(JpegDecode *obj);
    int (*getHeight)(JpegDecode *obj);
    int (*getDepth)(JpegDecode *obj);
    int (*getRowWidth)(JpegDecode *obj);
    unsigned int (*getPixe)(JpegDecode *obj, int r, int c);
};

JpegDecode* new_jpeg_decode_file(const char *file);
//JpegDecode* new_jpeg_decode_mem(char *data, int dsize);
void        del_jpeg_decode(JpegDecode **obj);



#endif

