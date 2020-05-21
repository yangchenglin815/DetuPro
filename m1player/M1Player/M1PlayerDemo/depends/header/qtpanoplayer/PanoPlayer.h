#ifndef PanoPlayer_h__
#define PanoPlayer_h__

#include "GLSurfaceRender.h"
#include "PlayerOption.h"
#include <iostream>
#include <vector>
#include <map>
#include "Plugin.h"
#include "IPanoPlayerListener.h"
#include "IPanoPlayerPluginListener.h"
#include "ScreenShotListener.h"
#include "PanoPlayerDef.h"
#include "IPanoPlayerRenderEventListener.h"

using namespace std;

struct PanoRenderWithCompatibility;

namespace DetuPanoPlayer {
    class PanoPlayerPrivate;

    class PanoPlayer;

    typedef void(*FrameFunction)(PanoPlayer *PanoPlayer);

    class PanoPlayer : public GLSurfaceRender, public PluginListener {
        friend class PanoPlayerPrivate;

    public:
        PanoPlayer();

        PanoPlayer(PanoPlayerPlatform platForm);

        ~PanoPlayer();

        int windowWidth;
        int windowHeight;
        ScreenShotListener *screenShotListener;
        unsigned char *screenShotData;
        ScreenShot screenShot;
        PanoRenderWithCompatibility *renderWithCompatibility;
        vector<PluginMetaData> pluginMetaDatas;
        Plugin *plugin;
        PanoramaData panoData;
        bool stopRenderFlag;
        PanoPlayerPlatform platForm;
        IPanoPlayerListener *panoPlayerListener;
        IPanoPlayerPluginListener *panoPlayerPluginListener;
        IPanoPlayerRenderEventListener *panoPlayerRenderEventListener;
    public:
        void onSurfaceCreated();

        virtual void onSurfaceChanged(int width, int height);

        void onDrawFrame();

    public:
        void setPanoPlayerListener(IPanoPlayerListener *panoPlayerListener);

        void setPanoPlayerPluginListener(IPanoPlayerPluginListener *panoPlayerPluginListener);

        void setPanoPlayerRenderEventListener(IPanoPlayerRenderEventListener *panoRenderEventListener);

        virtual void play(PanoramaData panoData);

        virtual void play(PanoramaData panoData, vector<PlayerOption> options);

        void close();

        GestureData *getcurrentGestureData();

        void setpausetime(float time);

        void setautoplay(bool autoplay);

        void autoplayhlookat(float hlookat);

        void setAnimationViewMode(PanoViewMode viewMode, int duration, EaseTypes type);

        void setAnimationViewMode(PanoViewMode viewMode, EaseTypes type);

        void setViewMode(PanoViewMode viewMode);
		void setweight(string weightpath);

        void setZoomEnable(bool toggle);

        void setGestureEnable(bool toggle);

        void getScreenShot(ScreenShotListener *listener);

        Plugin *getPlugin();

        /**
         *
         */
        void setLogLevel(PanoLogLevel logLevel);

    protected:
        vector<FrameFunction> frameFunctions;
        PanoPlayerPrivate *panoPlayerPrivate;
        PanoLogLevel logLevel;
    protected:
        void onPluginStateChanged(PluginState state, string tip);

        void onPluginGetFrames(PluginFrame *frames, int size);

        void onPluginProgressChanged(long playTime, long bufferTime, long duration);

        virtual Plugin *configPlugin(PanoramaData panoData, vector<PlayerOption> options);

        virtual void handlePanoPlayerRenderBefore();

        virtual void handlePanoPlayerRenderAfter();

        virtual void handlePanoPlayerRenderOneFrame();

        PluginLimits pluginLimits;
    };
}
#endif // PanoPlayer_h__
