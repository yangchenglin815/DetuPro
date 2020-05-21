#ifndef M1PLAYERDEMO_H
#define M1PLAYERDEMO_H

#include "GLSurfaceWidget.h"
#include "PixelPanoPlayer.h"
#include <QtWidgets/QMainWindow>
#include "ui_m1playerdemo.h"
#include <QButtonGroup> 
#include "ScreenShotListener.h"
#include "Global.h"
#include "Error.h"
#include "M1Player.h"
#include "VideoPlugin.h"

extern "C" {
#include <pthread/pthread.h>
}
#define M_PI       3.14159265358979323846

using namespace std;
using namespace DetuPanoPlayer;

class QtM1PlayerDemo : public QMainWindow, public IPanoPlayerPluginListener,
	public ScreenShotListener,
	public IPanoPlayerListener,
	public IPanoPlayerRenderEventListener
{
	Q_OBJECT

public:
	QtM1PlayerDemo(QWidget *parent = 0);
	~QtM1PlayerDemo();

signals:
	void updateSig(long process, long duration);
	void updateMediaInfoSig(PluginMetaData* mediaMeta);

private:
	PixelPanoPlayer* panoPlayer;
	GestureData gestureData;
	string codecDes = "cuda";
	pthread_t fovThread;
	int chooseviewmode = 1;
	float reservedegree=0;
	vector<PluginMetaData> pluginMetaDatas;
	float fov;
	private slots:
	void updateUI(long process, long duration);
	void updateMediaInfoUI(PluginMetaData* mediaMeta);
	void onBtPlayButtonClicked();
	void onBtAudioButtonClicked();
	void onBtScreenShotButtonClicked();
	void onBtSelectFileButtonClicked();
	void onBtReverseButtonClicked();
	void onBtInputUrlButtonClicked();
	void onViewModeGroupButtonChecked(int id, bool checked);
	void onCodecGroupButtonChecked(int id, bool checked);
	void closeEvent(QCloseEvent *event);
private:
	Ui::QtM1PlayerDemoClass ui;
	GLSurfaceWidget *glWidget_;
	void onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip);
	void onPanoPlayerPluginStatisticsDataChanged(PanoPluginStatisticsData* statisticsData) {}
	void onPanoPlayerPluginProgressChanged(long playProgress, long bufferProgress, long duration);
	void onScreenShotFinished(ScreenShot* screenShot);

	void onPanoPlayerLoading();
	void onPanoPlayerLoaded();
	void onPanoPlayerError(PanoPlayerErrorCode errorCode);

	void onPanoPlayerRenderBefore();
	void onPanoPlayerRenderAfter();
	QButtonGroup* rgViewMode;

	QButtonGroup* rgCodec;
private:
	void play(const char* filePath, PanoResourceType resoureType, const char* calibration, PanoDeviceId deviceId);

public:
	void  fovGetThreadFunc();

//add by chenliang
public:
	void onSigaction(int message_type, long attach);
	void onVideoFrames(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp);

private:
	void init_m1_player(string url);

private:
	CM1Player*	 m_m1_player;
	PixelPlugin* m_pixelPlugin;
	bool		 m_first_frames;
	bool		 m_is_m1_player;
	bool		 m_audio_pause_on;
	int			 m_vcodec_type;
	long		 m_signal_id;
	PluginFrame  m_frames[PLUGIN_MAX_PLANE];
};

#endif // M1PLAYERDEMO_H
