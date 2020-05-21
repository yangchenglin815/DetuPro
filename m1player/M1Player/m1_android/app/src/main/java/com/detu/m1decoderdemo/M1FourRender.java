package com.detu.m1decoderdemo;

import android.graphics.SurfaceTexture;
import android.media.MediaCodec;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.view.Surface;

import com.detu.m1decoder.M1CodecExtInfo;
import com.detu.m1decoder.MediaCodecH264;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by chao on 2017/7/20.
 */

public class M1FourRender implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("ijkffmpeg");
        System.loadLibrary("PiliRtmp");
        System.loadLibrary("M1Player");
    }

    private FlatRenderFourToOne flatFourToOne;

    private boolean haveFrameAvaible;

    private long nativeRef;

    private int windowWidth;

    private int windowHeight;

    private static final int RENDER_NUMBER = 4;

    private SurfaceTexture[] sufaceTextures = new SurfaceTexture[RENDER_NUMBER];

    private int textureIds[] = new int[RENDER_NUMBER];

    private MediaCodecH264[] mediaCodecH264s = new MediaCodecH264[RENDER_NUMBER];

    public M1FourRender() {
        _init();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        flatFourToOne = new FlatRenderFourToOne();
        flatFourToOne.initProgram();
        for (int i = 0; i < RENDER_NUMBER; i++) {
            MediaCodecH264 mediaCodecH264 = new MediaCodecH264();
            mediaCodecH264s[i] = mediaCodecH264;
            mediaCodecH264.initSurface();
            M1CodecExtInfo codecExtInfo = mediaCodecH264.getCodecExtInfo();
            sufaceTextures[i] = codecExtInfo.surfaceTexture;
            textureIds[i] = codecExtInfo.textureId;
        }
        _start(nativeRef, "rtmp://192.168.8.74:1935/0CD2DB_1/1", true, mediaCodecH264s);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        this.windowWidth = width;
        this.windowHeight = height;
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        int renderSize = 4;
        final int width = this.windowWidth;
        final int height = this.windowHeight;
        int viewPorts[][] = {{0, 0}, {width / 2, 0}, {0, height / 2}, {width / 2, height / 2}};
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
        GLES20.glClearColor(0.f, 0.0f, 0.0f, 0.0f);
        for (int i = 0; i < renderSize; i++) {
            sufaceTextures[i].updateTexImage();
            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureIds[i]);
            GLES20.glViewport(viewPorts[i][0], viewPorts[i][1], width / 2, height / 2);
            flatFourToOne.drawFrame();
        }
    }

    public void refresh() {
        _refresh(nativeRef);
    }

    public void close() {
        _close(nativeRef);
        _finalize(nativeRef);
    }

    private native void _init();

    private native void _start(long nativeRef, String url, boolean isHwDecoder, MediaCodecH264[] mediaCodecH264);

    private native void _refresh(long nativeRef);

    private native void _close(long nativeRef);

    private native void _finalize(long nativeRef);

}
