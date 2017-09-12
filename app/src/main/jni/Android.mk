LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := prebuilt/libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := hls

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include \
                    -L$(SYSROOT)/usr/include \
                    $(LOCAL_PATH)/curl/include

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib \
                -L/curl/lib \
                -ldl -llog -lz
LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS \
                -g -O3 -fvisibility=hidden

LOCAL_SRC_FILES := hls.c \
                   mongoose.c \
                   proxy_live.c \
                   util_live.c \
                   main_live.c
LOCAL_SHARED_LIBRARIES := ffmpeg
cmd-strip = $(TOOLCHAIN_PREFIX)strip $1
include $(BUILD_SHARED_LIBRARY)




