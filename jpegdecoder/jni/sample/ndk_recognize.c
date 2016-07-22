#include "ndk_recognize.h"

#include "log.h"
#include "cdecode.h"
#include "matchtemplat.h"


JNIEXPORT jdouble JNICALL Java_com_gzads_recognition_LogoRecognize_logoMatchTemplatPath
        (JNIEnv *env, jobject obj, jstring tmppath_, jstring mskpath_, jstring imgpath_,
         jint x, jint y, jint w, jint h) {

    const char* tmppath = (*env)->GetStringUTFChars(env, tmppath_, NULL);
    const char* mskpath = (*env)->GetStringUTFChars(env, mskpath_, NULL);
    const char* imgpath = (*env)->GetStringUTFChars(env, imgpath_, NULL);

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
