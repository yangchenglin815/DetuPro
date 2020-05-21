package com.detu.m1decoderdemo;

import android.opengl.GLES20;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created by chao on 2017/7/17.
 */

public class FlatRenderFourToOne {

    private static final String VERTEXT_SHADER =
            "attribute vec4 a_Position;\n" +
            "attribute vec2 a_TexCoordinate;\n" +
            "varying vec2 v_TexCoordinate;\n" +
            "void main() {\n" +
            "     v_TexCoordinate = a_TexCoordinate;\n" +
            "     gl_Position = a_Position;\n" +
            "}";

    private static final String FRAGMENT_SHADER =
            "#extension GL_OES_EGL_image_external : require\n" +
            "precision mediump float;" +
            "varying vec2 v_TexCoordinate;\n" +
            "uniform samplerExternalOES sample;\n" +
            "void main() {\n" +
            "   gl_FragColor = texture2D(sample, v_TexCoordinate);\n" +
            "}";

    private int program;

    private int aPostionLocation;

    private int aTextureCoordLocation;

    private int uniSample;

    private FloatBuffer bufferVertex;

    private FloatBuffer bufferTexture;

    public void initProgram() {
        program = GLutils.createProgram(VERTEXT_SHADER, FRAGMENT_SHADER);
        aPostionLocation = GLES20.glGetAttribLocation(program, "a_Position");
        aTextureCoordLocation = GLES20.glGetAttribLocation(program, "a_TexCoordinate");
        uniSample = GLES20.glGetUniformLocation(program, "sample");
        initCoords();
    }

    private void initCoords() {
        float squareVertices[] = {
                -1.0f, 1.0f,
                -1.0f, -1.0f,
                1.0f, 1.0f,
                1.0f, -1.0f,
        };
        bufferVertex = ByteBuffer.allocateDirect(squareVertices.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
        bufferVertex.put(squareVertices);
        bufferVertex.position(0);

        float textureCoordinates[] = {
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
        };
        bufferTexture = ByteBuffer.allocateDirect(textureCoordinates.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();;
        bufferTexture.put(textureCoordinates);
        bufferTexture.position(0);
    }

    public void drawFrame() {
        GLES20.glUseProgram(program);
        GLES20.glEnableVertexAttribArray(aPostionLocation);
        GLES20.glVertexAttribPointer(aPostionLocation, 2, GLES20.GL_FLOAT, false, 0, bufferVertex);
        GLES20.glEnableVertexAttribArray(aTextureCoordLocation);
        GLES20.glVertexAttribPointer(aTextureCoordLocation, 2, GLES20.GL_FLOAT, false, 0, bufferTexture);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
    }

    public void release() {
        GLES20.glDeleteProgram(program);
    }

}
