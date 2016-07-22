LOCAL_PATH := $(call my-dir)


#include $(CLEAR_VARS)
#LOCAL_MODULE := stdioext
#LOCAL_SRC_FILES := $(LOCAL_PATH)/libstdioext.a
#include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := gzjpeg
#LOCAL_LDFLAGS += $(LOCAL_PATH)/libstdioext.a
LOCAL_C_INCLUDES += $(LOCAL_PATH)
#LOCAL_STATIC_LIBRARIES := libstdioext
#LOCAL_CFLAGS := -Werror -O3 -ffast-math -static
LOCAL_CFLAGS  := -O3 -ffast-math -static -fPIC
LOCAL_LDLIBS  := -llog -ldl 

LOCAL_SRC_FILES := jcapimin.c jcapistd.c jccoefct.c jccolor.c  jcdctmgr.c jchuff.c   \
	               jcinit.c   jcmainct.c jcmarker.c jcmaster.c jcomapi.c  jcparam.c  \
			       jcphuff.c  jcprepct.c jcsample.c jctrans.c  jdapimin.c jdapistd.c \
				   jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c  jddctmgr.c jdhuff.c   \
				   jdinput.c  jdmainct.c jdmarker.c jdmaster.c jdmerge.c  jdphuff.c  \
				   jdpostct.c jdsample.c jdtrans.c  jerror.c   jfdctflt.c jfdctfst.c \
				   jfdctint.c jidctflt.c jidctfst.c jidctint.c jidctred.c jquant1.c  \
				   jquant2.c  jutils.c   jmemmgr.c  jmemansi.c \
				   cdecode.c
#main.c
#LOCAL_STATIC_LIBRARIES := stdioext
#include $(BUILD_EXECUTABLE)
include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)




