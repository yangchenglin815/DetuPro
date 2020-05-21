#ifndef _TCS_LIVE_CHANNEL_H_
#define _TCS_LIVE_CHANNEL_H_

#include <string>
#include <memory>
#include <vector>
#include <thread>
#include "Global.h"
#include "LockingQueue.h"
#include "Muxer.h"
#include "MessageHandle.h"
#include "ImageConvert.h"

#include "GLfwSurface.h"
#include "CapturePixelPanoPlayer.h"

using namespace DetuPanoPlayer;

typedef struct transcode_param
{
	std::string		push_url;		// 推流url
	std::string		rtmp_url;		// 拉流url
	std::string		device_name;	// 设备名称
	unsigned char   stream_type;	// 码流类型
	unsigned char   fps;			// 帧率
	unsigned int    bitrate;		// 码率(kbps)
	unsigned int	socketed;		// 套接字
	unsigned int    width;			// 高
	unsigned int    height;			// 宽
}transcode_param_t;

typedef enum encode_type_e
{
	EncodeTypeSoft = 0,	//libx264软编
	EncodeTypeNvenc,	//英伟达硬编
	EncodeTypeIntel,	//英特尔硬编
}encode_type_e;

#define DEFAULT_TRANSCODE_VIDEO_WIDTH	1920
#define DEFAULT_TRANSCODE_VIDEO_HEIGHT	1080
#define IMP_128_SHIFT8          (32768)

class CM1Player;
class CTcsConfig;

class CTcsLiveChannel : public CMessageHandle, public ICapturePixelListener, public IPanoPlayerListener
{
public:
	CTcsLiveChannel();
	virtual ~CTcsLiveChannel();

public:
	void onMessage(long session_id, int message_type){}
	void onSigaction(int message_type, long attach);
	void onVideoFrames(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp);
	void onCapturePixel();

	void onPanoPlayerLoaded();
	void onPanoPlayerLoading() {}
	void onPanoPlayerError(PanoPlayerErrorCode errorCode) {}

public:
	int Init(transcode_param_t* param);
	int Start();
	int Close();
	void SetConfig(CTcsConfig* config);
	void SetNewPts(bool is_new_pts);

private:
	void handle_stream_output();

private:
	bool	m_is_closed;
	std::shared_ptr<std::thread>	m_rtmp_send_thread;

private:
	void copy_transcode_param(transcode_param_t* src);
	int  init_m1_player();
	void init_panoplayer();
	int  init_encode_param();
	int  init_dpv_render(m1_video_frame_s** av_frame_sync_list_);
	int  rtmp_write_video(unsigned char* yuv);
	std::string get_calibration();
	std::string get_work_path();
	void create_calibration_file(char* data, int length);

private:
	int imp_dataconvert_rgba2yuv420(unsigned char *srcImg, int width, int height,
		unsigned char *yImg, unsigned char *uImg, unsigned char *vImg);

private:
	transcode_param_t*	m_transcode_param;
	CTcsConfig*			m_config;
	CM1Player*			m_m1_player;
	long				m_signal_id;
	int					m_decode_type;
	int					m_encode_type;
	int					m_reserve_degress;
	int					m_rgb_size;

	bool				m_is_pts_new;
	bool				m_render_transcode_ok;
	bool				m_inited_encode_param;
	bool				m_is_error_occurred;
	Muxer*				m_rtmp_muxter;

	std::mutex			m_error_mtx;

	CapturePixelPanoPlayer*	m_pano_player;
	GLOffscreenSurface*		m_surface;
	PixelPlugin*			m_pixelPlugin;
	PluginFrame				m_frames[PLUGIN_MAX_PLANE];

	typedef CLockingQueue<unsigned  char*> rgb_lock_queue;
	rgb_lock_queue			m_rgb_queue;
	unsigned char*			m_yuv_data;
	unsigned char*			m_rgba_data;
	CImagerConvert*			m_image_convert;
};

#endif
