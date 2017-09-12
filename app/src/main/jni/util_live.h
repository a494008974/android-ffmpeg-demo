//
// Created by Administrator on 2017/3/27.
//

#ifndef MFFMPEG_UTIL_LIVE_H
#define MFFMPEG_UTIL_LIVE_H
    #include <android/log.h>
    #include <pthread.h>

    #define  LOG_TAG "HLS"
    #define  LOGD(fmt, args...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, fmt, ##args)
    #define  LOGE(fmt, args...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, fmt, ##args)
    #define  LOGI(fmt, args...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, fmt, ##args)

    #define HLS_ERR		-1
    #define HLS_FALSE	0
    #define HLS_TRUE	1
    #define HLS_NOCHANGE 2
    #define HLS_CHANGE	3
    #define HLS_SUCCESS 4
    #define HLS_REDIRECT 302
    #define HLS_EXIT HLS_TRUE
    #define HLS_M3U8	5
    #define HLS_FLV		6


    int hls_create_thread(pthread_t *thread, void *arg, void *thread_func);
#endif //MFFMPEG_UTIL_LIVE_H
