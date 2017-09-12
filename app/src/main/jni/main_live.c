//
// Created by Administrator on 2017/3/28.
//
#include "main_live.h"
#include "util_live.h"
#include "curl_live.h"
#include "proxy_live.h"
#include <semaphore.h>

pthread_t th_main;
pthread_t th_hls_mongoose;
sem_t hls_live_sem;

static void *hls_main_thread(void *arg)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
	hls_proxy_main();
	pthread_exit(NULL);
}

static void *hls_mongoose_thread(void *arg)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
    start_proxy();
}

int hls_proxy_main(void)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
	//curl_http_init();
	sem_init(&hls_live_sem, 0, 0);
	if (hls_create_thread(&th_hls_mongoose, NULL, hls_mongoose_thread) != HLS_SUCCESS) goto fail;
	pthread_join(th_hls_mongoose, NULL);
	sem_destroy(&hls_live_sem);
	//curl_http_uninit();
	return HLS_SUCCESS;
  fail:
	return HLS_ERR;
}

int hls_proxy_init(void)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
	hls_create_thread(&th_main, NULL, hls_main_thread);
	return 0;
}

int hls_proxy_uninit(void)
{

}

int hls_event_send(void *priv_data, int event)
{
	return 0;
}

int hls_proxy_prepare(char *hls_url, int url_size)
{

	return 0;
}