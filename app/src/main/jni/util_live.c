//
// Created by Administrator on 2017/3/27.
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <semaphore.h>

#include "util_live.h"

int hls_create_thread(pthread_t *thread, void *arg, void *thread_func)
{
	pthread_t *th = thread;
	void *hls_arg = arg;

	if(pthread_create(th, NULL, thread_func, hls_arg) != 0) {
		LOGE("hls pthread_create failed");
		return HLS_ERR;
	}
    LOGD("hls create a new thread...");
	return HLS_SUCCESS;
}