package com.detu.m1decoder;

/**
 * Created by chao on 2017/11/20.
 */

public class M1Decoder {

    private long nativeRef;

    private static final int M1_DECODER_SIZE = 4;

    private MediaCodecH264[] h264Decoders = new MediaCodecH264[M1_DECODER_SIZE];

    /**
     * 调用线程必须为opengl线程
     *
     * @param url
     * @param isHwDecoder
     */
    public void start(String url, boolean isHwDecoder) {
        for (int i = 0; i < M1_DECODER_SIZE; i++) {
            h264Decoders[i] = new MediaCodecH264();
            h264Decoders[i].initSurface();
        }

    }

    public void stop() {

    }

    public void refresh() {

    }

    public void close() {

    }

    public M1CodecExtInfo[] getCodecExtInfos() {
        M1CodecExtInfo[] codecExtInfos = new M1CodecExtInfo[M1_DECODER_SIZE];
        for (int i = 0; i < M1_DECODER_SIZE; i++) {
            codecExtInfos[i] = h264Decoders[i].getCodecExtInfo();
        }
        return codecExtInfos;
    }

    private native void _setMediaCodecH264(MediaCodecH264[] mediaCodecH264);

    private native void _start(long nativeRef, String url, boolean isHwDecoder);

    private native void _stop(long nativeRef);

    private native void _refresh(long nativeRef);

    private native void _close(long nativeRef);
}
