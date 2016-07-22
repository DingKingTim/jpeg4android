//
// Created by dk on 16/3/21.
//

#include "cdecode.h"
#include "jpeglib.h"

static int decode_file(JpegDecode *obj, const char *file) {
    struct jpeg_decompress_struct jpjinfo;

    struct jpeg_error_mgr jerr;
    jpjinfo.err = jpeg_std_error(&jerr);

    FILE *input_file = NULL;
    if ((input_file = fopen(file, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", file);
        return 0;
    }

    jpeg_create_decompress(&jpjinfo);

    jpeg_stdio_src(&jpjinfo, input_file);

    (void) jpeg_read_header(&jpjinfo, TRUE);

    (void) jpeg_start_decompress(&jpjinfo);

    obj->width     = jpjinfo.output_width;
    obj->height    = jpjinfo.output_height;
    obj->depth     = jpjinfo.output_components;
    obj->row_width = obj->width * obj->depth;

    //LOGI("jpeg file's width: %d", obj->width);
    //LOGI("jpeg file's heigh: %d", obj->height);
    //LOGI("jpeg file's compo: %d", obj->row_width);


    /* Make a one-row-high sample array that will go away when done with image */
    JSAMPARRAY buffer = (*jpjinfo.mem->alloc_sarray)
            ((j_common_ptr) &jpjinfo, JPOOL_IMAGE, obj->row_width, 1);


    obj->data = (unsigned char *)malloc(obj->row_width * obj->height);
    memset(obj->data, 0, obj->row_width * obj->height);

    unsigned char * tmp = obj->data;

    while (jpjinfo.output_scanline < jpjinfo.output_height) {
        (void) jpeg_read_scanlines(&jpjinfo, buffer, 1);
        memcpy(tmp, *buffer, obj->row_width);
        tmp += obj->row_width;
    }

    (void) jpeg_finish_decompress(&jpjinfo);
    jpeg_destroy_decompress(&jpjinfo);
    fclose(input_file);
    return 1;
}

#if 0
static int decode_mem(JpegDecode *obj, char *data, int dsize) {

    struct jpeg_decompress_struct jpjinfo;

    struct jpeg_error_mgr jerr;
    jpjinfo.err = jpeg_std_error(&jerr);

    FILE *input_file = NULL;
    if ((input_file = fmemopen(data, dsize, "rb"))) {
        fprintf(stderr, "can't open memeory\n");
        return 0;
    }

    jpeg_create_decompress(&jpjinfo);

    jpeg_stdio_src(&jpjinfo, input_file);

    (void) jpeg_read_header(&jpjinfo, TRUE);

    (void) jpeg_start_decompress(&jpjinfo);

    obj->width     = jpjinfo.output_width;
    obj->height    = jpjinfo.output_height;
    obj->depth     = jpjinfo.output_components;
    obj->row_width = obj->width * obj->depth;

    //LOGI("jpeg file's width: %d", obj->width);
    //LOGI("jpeg file's heigh: %d", obj->height);
    //LOGI("jpeg file's compo: %d", obj->row_width);


    /* Make a one-row-high sample array that will go away when done with image */
    JSAMPARRAY buffer = (*jpjinfo.mem->alloc_sarray)
            ((j_common_ptr) &jpjinfo, JPOOL_IMAGE, obj->row_width, 1);


    obj->data = (unsigned char *)malloc(obj->row_width * obj->height);
    memset(obj->data, 0, obj->row_width * obj->height);

    unsigned char * tmp = obj->data;

    while (jpjinfo.output_scanline < jpjinfo.output_height) {
        (void) jpeg_read_scanlines(&jpjinfo, buffer, 1);
        memcpy(tmp, *buffer, obj->row_width);
        tmp += obj->row_width;
    }

    (void) jpeg_finish_decompress(&jpjinfo);
    jpeg_destroy_decompress(&jpjinfo);
    fclose(input_file);
    return 1;
}
#endif

static int getWidth(JpegDecode *obj) {
    return obj->width;
}

static int getHeight(JpegDecode *obj) {
    return obj->height;
}

static int getDepth(JpegDecode *obj) {
    return obj->depth;
}

static int getRowWidth(JpegDecode *obj) {
    return obj->row_width;
}

static unsigned int getPixe(JpegDecode *obj, int r, int c) {

    unsigned int pixe = 0;
    unsigned char* ptr = (obj->data + obj->row_width * r + c*obj->depth);

    int i;
    for (i = 0; i < obj->depth; ++i) {
        pixe = ((pixe<<8*(i==0?0:1)) | ptr[i]);
    }

    return pixe;
}

#if 0
JpegDecode* new_jpeg_decode_mem(char *data, int dsize) {

    JpegDecode *decodeObj = (JpegDecode*)calloc(sizeof(JpegDecode), 1);
    if (!decodeObj) {
        fprintf(stderr, "decode obj init memeory error\n");
        return NULL;
    }

    int ret = decodeObj->decode_mem(decodeObj, data, dsize);
    if (ret) {
        decodeObj->decode_file = decode_file;
        //decodeObj->decode_mem  = decode_mem;
        decodeObj->getWidth    = getWidth;
        decodeObj->getHeight   = getHeight;
        decodeObj->getDepth    = getDepth;
        decodeObj->getRowWidth = getRowWidth; 
        decodeObj->getPixe     = getPixe;

        return decodeObj;
    }

    free(decodeObj);
    return NULL;
}
#endif

JpegDecode* new_jpeg_decode_file(const char *file) {
    
    JpegDecode *decodeObj = (JpegDecode*)calloc(sizeof(JpegDecode), 1);
    if (!decodeObj) {
        //LOGE("decode obj init memeory error");
        return NULL;
    }
    
    decodeObj->decode_file = decode_file;
    //decodeObj->decode_mem  = decode_mem;
    decodeObj->getWidth    = getWidth;
    decodeObj->getHeight   = getHeight;
    decodeObj->getDepth    = getDepth;
    decodeObj->getRowWidth = getRowWidth; 
    decodeObj->getPixe     = getPixe;


    int ret = decodeObj->decode_file(decodeObj, file);
    if (ret) {
        return decodeObj;
    }

    free(decodeObj);
    return NULL;
}

void del_jpeg_decode(JpegDecode **obj) {

    if (*obj == NULL)
        return;

    JpegDecode *decodeObj  = *obj;
    if (decodeObj->data) free(decodeObj->data);
    free(*obj); *obj=NULL;

    return;
}


