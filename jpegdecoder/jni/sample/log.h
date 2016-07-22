#ifndef _LOG_H_
#define _LOG_H_
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LOCAL_TEST
#define  LOGD(...)  
#define  LOGI(...) 
#define  LOGW(...)
#define  LOGE(...)
#else
#include <android/log.h>
#define LOG_TAG "gzlogo"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif
#ifdef __cplusplus
}
#endif

#endif
