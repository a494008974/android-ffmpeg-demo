package com.video.mffmpeg.handler;

import android.util.Log;

public class MediaProxy
{
    private static final String TAG = "MediaProxy";
    private static MediaProxy sInstance;
    
    static
    {
        try
        {
            System.loadLibrary("ffmpeg");
            System.loadLibrary("hls");
        }
        catch (Exception e)
        {
            Log.e(TAG, "Can't load hls or ffmpeg library: " + e);
            System.exit(1);
        }
    }

    public synchronized static MediaProxy getInstance()
    {
        if (sInstance == null)
        {
            sInstance = new MediaProxy();
            sInstance.init();
        }
        return sInstance;
    }
    
    private MediaProxy()
    {
        Log.d(TAG, "MediaProxy()...... ");
    }
    
    private void init()
    {
        setEventManager(EventManager.getInstance());
        hlsProxyInit();
    }

    public void unInit()
    {
        hlsProxyUninit();
        detachEventManager();
    }
    
    public void request(byte[] url)
    {
        hlsProxyPrepare(url);
    }
    
    private static native void hlsProxyInit();
    
    private static native void hlsProxyUninit();
    
    private static native void hlsProxyPrepare(byte[] url);
    
    private native void setEventManager(EventManager eventManager);
    
    private native void detachEventManager();
}
