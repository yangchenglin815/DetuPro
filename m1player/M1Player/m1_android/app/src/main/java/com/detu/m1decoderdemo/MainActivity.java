package com.detu.m1decoderdemo;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    M1FourRender render;

    AudioTrack mAudioTrack;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle("M1测试界面");
        setContentView(R.layout.activity_main);

        findViewById(R.id.bt_refresh).setOnClickListener(this);
        GLSurfaceView glview = findViewById(R.id.glview);
        glview.setEGLContextClientVersion(3);
        render = new M1FourRender();
        glview.setRenderer(render);
        //testAudioTrack();
    }

    private void testAudioTrack() {
        final int bufferSize = AudioTrack.getMinBufferSize(16000,
                AudioFormat.CHANNEL_OUT_STEREO,
                AudioFormat.ENCODING_PCM_16BIT);
        mAudioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, 16000, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT, bufferSize, AudioTrack.MODE_STREAM);
        mAudioTrack.play();
        new Thread() {
            @Override
            public void run() {
                super.run();
                File file = new File("/mnt/sdcard/mono.pcm");
                try {
                    FileInputStream fis = new FileInputStream(file);
                    byte[] buffer = new byte[bufferSize];
                    int length = 0;
                    while ((length = fis.read(buffer)) > 0) {
                        mAudioTrack.write(buffer, 0, length);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }

    @Override
    public void onClick(View v) {
        if (render != null) {
            render.refresh();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        render.close();
        Log.e("ceshi", "this is m1 close!");
    }
}
