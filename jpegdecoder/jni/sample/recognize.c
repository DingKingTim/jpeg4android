#include "recognize.h"

#include "log.h"
#include "cdecode.h"
#include "matchtemplat.h"

double logoMatchTemplat(char* tmppath_, char* mskpath_, char* imgpath_,
         int x, int y, int w, int h) {

    const char* tmppath = tmppath_;
    const char* mskpath = mskpath_;
    const char* imgpath = imgpath_;

    JpegDecode* tmpJpegDecode = new_jpeg_decode_file(tmppath);
    JpegDecode* mskJpegDecode = new_jpeg_decode_file(mskpath);
    JpegDecode* imgJpegDecode = new_jpeg_decode_file(imgpath);

    Roi roi;
    roi.x = x;
    roi.y = y;
    roi.w = w;
    roi.h = h;
    
    double matchvalue = matchtemplat(tmpJpegDecode, mskJpegDecode, imgJpegDecode, roi);
    LOGI("matchvalue is: %f", matchvalue);

    return matchvalue;
}

