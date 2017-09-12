package com.video.mffmpeg;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.video.mffmpeg.handler.EventManager;
import com.video.mffmpeg.handler.HlsHander;
import com.video.mffmpeg.handler.MediaProxy;

public class MainActivity extends AppCompatActivity {
    private HlsHander mHlsHander;
    private MediaProxy mMediaProxy;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHlsHander = new HlsHander(this);
        EventManager.getInstance().addHandler(mHlsHander);
        try {
            mMediaProxy = MediaProxy.getInstance();
        }catch (Exception e){

        }

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(mMediaProxy != null){
            mMediaProxy.unInit();
        }
        EventManager.getInstance().removeHandler(mHlsHander);
    }
}
