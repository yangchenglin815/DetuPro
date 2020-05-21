package com.detu.m1decoder;

import android.graphics.SurfaceTexture;

/**
 * Created by chao on 2017/11/20.
 */

public class M1CodecExtInfo {

    public M1CodecExtInfo(SurfaceTexture surfaceTexture, int textureId) {
        this.surfaceTexture = surfaceTexture;
        this.textureId = textureId;
    }

    public SurfaceTexture surfaceTexture;
    public int textureId;
}
