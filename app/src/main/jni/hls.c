#include <stdio.h>
#include <stdlib.h>
#include "hls.h"
#include "jni.h"
#include "proxy_live.h"
#include "util_live.h"
#include "main_live.h"

#define CLASS_NAME "com/video/mffmpeg/fnative/MediaProxy"
#define CLASS_EVENT "(Lcom/video/mffmpeg/fnative/EventManager;)V"

JavaVM *hls_vm;
jclass hls_event_cls = NULL;
jobject hls_event_obj = NULL;
jmethodID hls_event_cbk = NULL;

void hlsProxyInit(JNIEnv *env, jclass cls)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
    hls_proxy_init();
}

void hlsProxyUninit(JNIEnv *env, jclass cls)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
}

void hlsProxyPrepare(JNIEnv *env, jclass cls, jbyteArray url)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
}

void setEventManager(JNIEnv *env, jobject thiz, jobject eventManager)
{
    LOGD(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
    if (hls_event_obj != NULL) {
        (*env)->DeleteGlobalRef(env, hls_event_obj);
        hls_event_obj = NULL;
    }

    jclass cls = (*env)->GetObjectClass(env, eventManager);
    if (!cls) {
        LOGE(" =====> %s","setEventManager: failed to get class reference\n");
        return;
    }

    jmethodID methodID = (*env)->GetMethodID(env, cls, "callback", "(I)V");
    if (!methodID) {
        LOGE(" =====> %s","setEventManager: failed to get the callback method");
        return;
    }

    hls_event_obj = (*env)->NewGlobalRef(env, eventManager);
}

void detachEventManager(JNIEnv *env, jobject thiz)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
    if (hls_event_obj != NULL) {
        (*env)->DeleteGlobalRef(env, hls_event_obj);
        hls_event_obj = NULL;
    }
}

int hls_event_callback(int event)
{
    LOGE(" =====> %s -----> %s ----> %d",__FILE__ , __FUNCTION__ ,__LINE__);
	JNIEnv *env;
	int ret;
    if (hls_event_obj == NULL)
        return HLS_ERR;

    int isAttached = HLS_FALSE;
    int status = (*hls_vm)->GetEnv(hls_vm, (void**)&env, JNI_VERSION_1_2);
    if (status < 0) {
        status = (*hls_vm)->AttachCurrentThread(hls_vm, &env, NULL);
        if (status < 0)
            return HLS_ERR;
        isAttached = HLS_TRUE;
    }

    if (env == NULL) {
        ret = HLS_ERR;
        goto end;
    }
    hls_event_cls = (*env)->GetObjectClass(env, hls_event_obj);
    if (!hls_event_cls) {
        ret = HLS_ERR;
        goto end;
    }

    hls_event_cbk = (*env)->GetMethodID(env, hls_event_cls, "callback", "(I)V");
    if (hls_event_cbk) {
        (*env)->CallVoidMethod(env, hls_event_obj, hls_event_cbk, event);
        ret = HLS_SUCCESS;
    } else {
        ret = HLS_ERR;
    }

end:
    if (isAttached)
        (*hls_vm)->DetachCurrentThread(hls_vm);

    return ret;
}

static JNINativeMethod gMethods[] = {
    {"hlsProxyInit","()V",(void *)hlsProxyInit},
	{"hlsProxyUninit","()V",(void *)hlsProxyUninit},
	{"hlsProxyPrepare","([B)V",(void *)hlsProxyPrepare},
	{"setEventManager",CLASS_EVENT,(void *)setEventManager},
	{"detachEventManager","()V",(void *)detachEventManager},
};

static const char* const kClassPathName = CLASS_NAME;

static int register_test(JNIEnv *env)
{
	jclass clazz = (*env)->FindClass(env, kClassPathName);
	if (clazz == NULL) {
		LOGE("Native registration unable to find class '%s'", kClassPathName);
		return JNI_FALSE;
	}
	if ((*env)->RegisterNatives(env, clazz, gMethods,  sizeof(gMethods) / sizeof(gMethods[0])) < 0) {
		LOGE("RegisterNatives failed for '%s'", kClassPathName);
		(*env)->DeleteLocalRef(env, clazz);
		return JNI_FALSE;
	}
	(*env)->DeleteLocalRef(env, clazz);
	return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM *vm, void* reserved)
{
    hls_vm = vm;
	JNIEnv* env = NULL;
    jint result = -1;
	if ((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_2) != JNI_OK)
	{
           LOGE("ERROR: GetEnv failed");
           goto bail;
    }

    if (register_test(env) < 0) {
    	LOGE("love native registration failed");
        goto bail;
    }

    result = JNI_VERSION_1_2;

	bail:
    return result;
}

void JNI_OnUnload(JavaVM *vm, void *reserved)
{
    LOGD("JNI interface unloaded.");
}