package com.detu.m1decoder;

import android.graphics.SurfaceTexture;
import android.media.MediaCodec;
import android.media.MediaFormat;
import android.opengl.GLES20;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Surface;

import java.nio.ByteBuffer;
import java.util.concurrent.ArrayBlockingQueue;

import static android.opengl.GLES11Ext.GL_TEXTURE_EXTERNAL_OES;

/**
 * Created by chao on 2017/5/17.
 */

public class MediaCodecH264 implements SurfaceTexture.OnFrameAvailableListener {

    private static final String TAG = MediaCodecH264.class.getSimpleName();

    private static final int INPUT_DEQUEUE_TIMEOUT_US = -1;

    private static final int OUTPUT_DEQUEUE_TIMEOUT_US = -1;

    private MediaCodec mH264MediaCodec;

    private boolean mHaveException;

    private Surface mSurface;

    private SurfaceTexture mSurfaceTexture;

    private int mTextureId;

    private boolean mIsFrameUpdated;

    private boolean mIsMediaCodecStared = false;

    private int mWidth;

    private int mHeight;

    private long mFrameIndex;

    private long mFrameAvailableIndex;

    private ArrayBlockingQueue<Long> blockingDeque = new ArrayBlockingQueue<Long>(1);

    private byte[] mPacketCache;

    private void start() {
        new Thread() {
            @Override
            public void run() {
                super.run();
                decoderThreadFunc();
            }
        }.start();
    }

    public void initSurface() {
        int tex[] = new int[1];
        GLES20.glGenTextures(1, tex, 0);
        GLES20.glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex[0]);
        GLES20.glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);

        mTextureId = tex[0];
        Log.d(TAG, "createSurfaceTexture textureName:" + mTextureId);
        mSurfaceTexture = new SurfaceTexture(mTextureId);
        mSurfaceTexture.setOnFrameAvailableListener(this);
        mSurface = new Surface(mSurfaceTexture);
    }

    public void releaseSurface() {
        if (mTextureId != 0) {
            int[] textureIds = {mTextureId};
            GLES20.glDeleteTextures(1, textureIds, 0);
            mTextureId = 0;
        }
        if (mSurfaceTexture != null) {
            mSurfaceTexture.release();
            mSurfaceTexture = null;
        }
        if (mSurface != null) {
            mSurface.release();
            mSurface = null;
        }
    }

    public M1CodecExtInfo getCodecExtInfo() {
        return new M1CodecExtInfo(mSurfaceTexture, mTextureId);
    }

    private void decoderThreadFunc() {
        while (true) {
            try {
                MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
                int outputIndex = mH264MediaCodec.dequeueOutputBuffer(bufferInfo, 0);
                if (outputIndex == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
                } else if (outputIndex >= 0) {
                    if (bufferInfo.flags != MediaCodec.BUFFER_FLAG_END_OF_STREAM) {
                        mH264MediaCodec.releaseOutputBuffer(outputIndex, true);
                    } else {
                        Log.e(TAG, "flag end of stream!");
                        //onReadFrameEnd(mFrameIndex, MediaCodecH264.this.nativePtr);
                        mH264MediaCodec.releaseOutputBuffer(outputIndex, false);
                        break;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                MediaCodecH264.this.mHaveException = true;
                break;
            }
        }
        release();
        Log.e(TAG, "this is decoder out thread over!");
    }

    private void release() {
        try {
            if (mH264MediaCodec != null) {
                mH264MediaCodec.stop();
                mH264MediaCodec.release();
                mH264MediaCodec = null;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void onGetMediaInfo(byte[] spsPpsData, int width, int height) {
        try {
            mIsFrameUpdated = true;
            this.mWidth = width;
            this.mHeight = height;
            mPacketCache = new byte[width * height];
            this.mH264MediaCodec = MediaCodec.createDecoderByType("video/avc");
            MediaFormat mediaFormat = new MediaFormat();
            mediaFormat.setInteger(MediaFormat.KEY_WIDTH, width);
            mediaFormat.setInteger(MediaFormat.KEY_HEIGHT, height);
            mediaFormat.setString(MediaFormat.KEY_MIME, "video/avc");

            final int size = spsPpsData.length;
            int prefixIndex = 0;
            for (int i = 0; i < size - 4; i++) {
                if (spsPpsData[i] == 0 && spsPpsData[i + 1] == 0 && spsPpsData[i + 2] == 0 && spsPpsData[i + 3] == 1) {
                    prefixIndex = i;
                }
            }
            byte[] spsData = new byte[prefixIndex];
            System.arraycopy(spsPpsData, 0, spsData, 0, prefixIndex);
            final int ppsSize = size - prefixIndex;
            byte[] ppsData = new byte[ppsSize];
            System.arraycopy(spsPpsData, prefixIndex, ppsData, 0, ppsSize);
            mediaFormat.setByteBuffer("csd-0", ByteBuffer.wrap(spsData));
            mediaFormat.setByteBuffer("csd-1", ByteBuffer.wrap(ppsData));

            this.mH264MediaCodec.configure(mediaFormat, mSurface, null, 0);
            this.mH264MediaCodec.start();
            this.mIsMediaCodecStared = true;
            start();
        } catch (Exception e) {
            e.printStackTrace();
            MediaCodecH264.this.mHaveException = true;
            release();
        }
    }

    public int onGetPacket(int size, int isKeyFrame) {
        if (!mIsMediaCodecStared || mH264MediaCodec == null) {
            return -1;
        }
//        try {
//            blockingDeque.put(0);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
        ByteBuffer[] inputBuffers = mH264MediaCodec.getInputBuffers();
        try {
            boolean haveSuccessInputPacket = false;
            while (!haveSuccessInputPacket) {
                int inputIndex = mH264MediaCodec.dequeueInputBuffer(0);
                if (inputIndex > 0) {
                    ByteBuffer byteBuffer = inputBuffers[inputIndex];
                    byteBuffer.put(mPacketCache);
                    if (size > 0) {
                        long timeStamp = (long) (30 * 1.0 / 1000 * mFrameIndex++);
                        int flag = isKeyFrame == 1 ? MediaCodec.BUFFER_FLAG_KEY_FRAME : MediaCodec.BUFFER_FLAG_PARTIAL_FRAME;
                        //Log.e("mediacodech264", "size:" + size + ",time:" + timeStamp + ",isKey:" + flag);
                        mH264MediaCodec.queueInputBuffer(inputIndex, 0, size, timeStamp, flag);
                        haveSuccessInputPacket = true;
                    } else {
                        Log.e(TAG, "input end of file");
                        while ((inputIndex = mH264MediaCodec.dequeueInputBuffer(0)) < 0) {

                        }
                        mH264MediaCodec.queueInputBuffer(inputIndex, 0, 0, -1, MediaCodec.BUFFER_FLAG_END_OF_STREAM);
                        break;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            MediaCodecH264.this.mHaveException = true;
        }
        return 0;
    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        //Log.e("MediaCodecH264", "onFrameAvailable");
        /*try {
            blockingDeque.put((++mFrameAvailableIndex));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/
    }
}
