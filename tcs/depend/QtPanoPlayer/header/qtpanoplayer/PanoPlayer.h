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
#include "Fragment.h"

#if defined(__ANDROID__)
#include <jni.h>
#endif

using namespace std;

struct PanoRenderWithCompatibility;

namespace DetuPanoPlayer {
    class PanoPlayerPrivate;

    class PanoPlayer;
    
    class DecorView;

    typedef void(*FrameFunction)(PanoPlayer *PanoPlayer);

	typedef struct PanoPlayerEvent {
		void* opaque;
		void(*onInvoke)(void* opaque);
	} PanoPlayerEvent;

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
        PanoPlayerPlatform platForm;
        IPanoPlayerListener *panoPlayerListener;
        IPanoPlayerPluginListener *panoPlayerPluginListener;
        IPanoPlayerRenderEventListener *panoPlayerRenderEventListener;
        PanoPlayerPrivate *panoPlayerPrivate;
		void* platformOpaque;
        PanoPluginStatisticsData mStatisticsData;
        DecorView* mDecorView;
		PanoViewMode curviewmode;
		vector<string> weightPath;
		bool isCreateWeightTextureID;
	private:
		bool createWeightTextureID();
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

        
        virtual void grabPixel(int width, int height, unsigned char* outData);

        GestureData *getcurrentGestureData();
        void setcurImageData_cali(string cali);
        
        void setpausetime(float time);

		void setAutoRotate(bool autoplay, float hlookat);
        void setAutoVertical(bool autoVertical);
		void setPointSelectingSwitch(bool isPointSelecting);
		void setreverse(bool is_up_down);
        void setAnimationViewMode(PanoViewMode viewMode, float duration, EaseTypes type);

        void setAnimationViewMode(PanoViewMode viewMode, EaseTypes type);
        void setanimationfov(float detafov, float duration, EaseTypes easeType);//设置m1离场动画

        void setViewMode(PanoViewMode viewMode);
		void setweight(std::vector<string> weightpath);
        void getClipsparam(float *fov, float *hlookat, float*vlookat);//get clips param
		void setClipsparam( float fov, float hlookat, float vlookat, float near, float zoffset); //set clips param
		void setClipsswitch( bool isclips);//clips switch
        /*
         * Mutual conversion between latitude and longitude and screen coordinates
         */
        void calDegByWinPoint(float px, float py,float*outdeg);
        void calDegByWinPointleft(float px, float py,float *outdeg);
        void calDegByWinPointRight(float px, float py,float *outdeg);
        //-180-180 -90-90
        void calWinPointByDeg(float degX, float degY, int sw, int sh,float *out);
        void calWinPointByDegleft(float degX, float degY, int sw, int sh,float *out);
        void calWinPointByDegright(float degX, float degY, int sw, int sh,float *out);
        
        void getScreenShot(ScreenShotListener *listener);

		void setPlatformOpaque(void* opaque);

        Plugin *getPlugin();

		void postEvent(PanoPlayerEvent event);
        
        void dispatchTouchEvent(MotionEvent* motionEvent);
        
        void setFragment(Fragment* fragment);
        /**
         *
         */
        void setLogLevel(PanoLogLevel logLevel);

#if defined(__ANDROID__)
		void setJniVm(JavaVM* vm);
#endif

    protected:
        vector<FrameFunction> frameFunctions;
        PanoLogLevel logLevel;
    protected:
        virtual void onPluginStateChanged(PluginState state, string tip);

        virtual void onPluginGetFrames(PluginFrame *frames, int size);

        virtual void onPluginProgressChanged(long playTime, long bufferTime, long duration);

        virtual Plugin *configPlugin(PanoramaData panoData, vector<PlayerOption> options);
       
        virtual void handlePanoPlayerRenderBefore();

        virtual void handlePanoPlayerRenderAfter();

        virtual void handlePanoPlayerRenderOneFrame();
        
        void panoDegreeToWindowPoint(float ath, float atv, int width, int height, float windowPoint[2]);

        PluginLimits pluginLimits;
    };
}
#endif // PanoPlayer_h__
