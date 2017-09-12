package com.video.mffmpeg.handler;

import android.os.Message;
import android.util.Log;

import com.video.mffmpeg.MainActivity;

/**
 * Created by Administrator on 2017/3/24.
 */
public class HlsHander extends WeakHandler<MainActivity> {
    private static final String TAG = "HlsHander";

    public HlsHander(MainActivity owner) {
        super(owner);
    }
    @Override
    public void handleMessage(Message msg) {
        super.handleMessage(msg);
        MainActivity act = getOwner();
        Log.d(TAG+" msg.what:",String.valueOf(msg.what));
        switch (msg.what){
            case EventManager.MediaPlayerInit:
                Log.d(TAG, "EventManager.MediaPlayerInit ****************************");
                break;
            case EventManager.MediaPlayerBuffering:
                Log.d(TAG, "EventManager.MediaPlayerBuffering");
                break;
            case EventManager.MediaPlayerPlaying:
                Log.d(TAG, "EventManager.MediaPlayerPlaying");
                break;
            case EventManager.MediaPlayerPaused:
                Log.d(TAG, "EventManager.MediaPlayerPaused");
                break;
            case EventManager.MediaPlayerStopped:
                Log.d(TAG, "EventManager.MediaPlayerStopped");
                break;
            case EventManager.MediaPlayerEndReached:
                Log.d(TAG, "EventManager.MediaPlayerEndReached");
                break;
            case EventManager.MediaPlayerVout:
                Log.d(TAG, "EventManager.MediaPlayerVout");
                break;
            case EventManager.MediaPlayerDead:
                Log.d(TAG, "EventManager.MediaPlayerDead");
                break;
            default:
                break;
        }
    }
}
