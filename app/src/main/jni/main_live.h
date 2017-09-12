//
// Created by Administrator on 2017/3/28.
//

#ifndef MFFMPEG_MAIN_LIVE_H
#define MFFMPEG_MAIN_LIVE_H

    int hls_proxy_init(void);
    int hls_proxy_uninit(void);
    int hls_proxy_prepare(char *hls_url, int url_size);
    int hls_event_send(void *priv_data, int event);

#endif //MFFMPEG_MAIN_LIVE_H
