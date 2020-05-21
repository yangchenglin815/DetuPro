
#ifndef PLUGIN_LISTENER_H
#define PLUGIN_LISTENER_H

#include <stdint.h>

#define PLUGIN_MAX_PLANE 4 //Frame���ͨ����

namespace DetuPanoPlayer {

    typedef enum PluginState {
        PluginState_PREPARED,
        PluginState_PLAYING,
        PluginState_PAUSE,
        PluginState_STOP,
        PluginState_SEEK_COMPLETE,
        PluginState_COMPLETED,
        PluginState_ERROR,
        PluginState_DECODER_CHANGE,
		PluginState_Gopsize,
		PluginState_Decodefps,
    } PluginState;

    typedef enum PluginColorFormat {
        PluginColorFormat_RGBA,
        PluginColorFormat_ARGB,
        PluginColorFormat_ABGR,
        PluginColorFormat_BGRA,
        PluginColorFormat_RGB24,
        PluginColorFormat_BGR24,
        PluginColorFormat_YUV420P,
        PluginColorFormat_YV12,
        PluginColorFormat_NV12,
        PluginColorFormat_NV21,
        PluginColorFormat_UYVY422,
        PluginColorFormat_OPENGL_TEXTURE,
        PluginColorFormat_MEDIACODEC,
        PluginColorFormat_VIDEOTOOLBOX,
        PluginColorFormat_VDA,
		PluginColorFormat_CUDA,
    } PluginColorFormat;

    typedef struct PluginFrame {
        uint8_t *data[PLUGIN_MAX_PLANE];
        int linesize[PLUGIN_MAX_PLANE];
        int width;
        int height;
        int planes;
        PluginColorFormat colorFormat;
        void *opaque; //opengl texture ����iosӲ������
    } PluginFrame;

    class PluginListener {
    public:
        PluginListener() {}

        virtual ~PluginListener() {}

        virtual void onPluginStateChanged(PluginState state, string tip) = 0;

        virtual void onPluginGetFrames(PluginFrame *frame, int count) = 0;

        virtual void onPluginProgressChanged(long playTime, long bufferTime, long duration) = 0;
    };

}
#endif
