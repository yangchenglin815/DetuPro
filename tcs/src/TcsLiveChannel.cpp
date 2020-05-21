#include "Platform.h"
#include "TcsGlobal.h"
#include "Config.h"
#include "Error.h"
#include "M1Player.h"
#include "MessageQueue.h"
#include "TcsLiveChannel.h"
#include "GetResult.h"
#include "TcsPanoplayer.h"
#include "RtmpMuxer.h"
#include "logging.h"


CTcsLiveChannel::CTcsLiveChannel()
{
	m_is_closed = false;
	m_config = NULL;
	m_m1_player = NULL;
	m_signal_id = -1;
	m_decode_type = 0;
	m_encode_type = 0;
	m_reserve_degress = 0;
	m_rgb_size = 0;
	m_is_pts_new = false;
	m_render_transcode_ok = false;
	m_inited_encode_param = false;
	m_is_error_occurred = false;
	m_rtmp_muxter = new RtmpMuxer;

	m_pano_player = NULL;
	m_surface = NULL;
	m_yuv_data = NULL;
	m_rgba_data = NULL;
	m_image_convert = new CImagerConvert;

	CMessageQueue::GetInstance().Register(std::bind(&CTcsLiveChannel::onSigaction, this, std::placeholders::_1, std::placeholders::_2), m_signal_id);
}

CTcsLiveChannel::~CTcsLiveChannel()
{

}

void CTcsLiveChannel::onSigaction(int message_type, long attach)
{
	Log::Info("message:%d recv from player,id:%d", message_type, GetID());
	if (message_type == ERROR_SOCKET_READ){
		std::unique_lock<std::mutex> lock(m_error_mtx);
		if (!m_is_error_occurred){
			m_is_error_occurred = true;
			lock.unlock();
			Log::Error("m1 player error, stop publish rtmp, id:%d", GetID());
			Notify(m_owner, GetID(), ERROR_TRANSCODE_PLAYER_ERROR);
		} else {
			lock.unlock();
			Log::Info("error already notify to owner.");
		}
	}
}

void CTcsLiveChannel::onVideoFrames(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp)
{
	if (!m_inited_encode_param) {
		init_dpv_render(av_frame_sync_list_);
		m_inited_encode_param = true;
	}

	for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
		if (av_frame_sync_list_[i]->format == PIX_FMT_YUV420P) {
			m_frames[i].colorFormat = PluginColorFormat_YUV420P;
			m_frames[i].planes = 3;
		} else if (av_frame_sync_list_[i]->format == PIX_FMT_NV12) {
			m_frames[i].colorFormat = PluginColorFormat_NV12;
			m_frames[i].planes = 2;
		}

		for (int j = 0; j < PLUGIN_MAX_PLANE; j++) {
			m_frames[i].data[j] = av_frame_sync_list_[i]->data[j];
		}
	}
	m_pixelPlugin->notifyFramesChanged((PluginFrame*)m_frames, 4);
}

void CTcsLiveChannel::onCapturePixel()
{
	//double start = av_gettime_relative() / 1000.0;

	m_surface->prepareForReadPixel();
	m_pano_player->grabPixel(m_transcode_param->width, m_transcode_param->height, m_rgba_data, false);

	//double end1 = av_gettime_relative() / 1000.0;
	//double cost1 = end1 - start;

	m_image_convert->Rgb2Yuv(DT_RGBA2YUV_I420, m_rgba_data, m_yuv_data, m_transcode_param->width, m_transcode_param->height);

	//double end2 = av_gettime_relative() / 1000.0;
	//double cost2 = end2 - end1;

	rtmp_write_video(m_yuv_data);

	//double end3 = av_gettime_relative() / 1000.0;
	//double cost3 = end3 - end2;
	//Log::Info("grab rgba cost:%fms, rgba to yuv420p cost:%fms, yuv420p to h264 cos:%fms", cost1, cost2, cost3);

	if (!m_render_transcode_ok) {
		m_render_transcode_ok = true;
	}
}

void CTcsLiveChannel::onPanoPlayerLoaded()
{
	std::vector<std::string> weight_path;
	std::string wt0 = "./pts/" + m_transcode_param->device_name + "/wt0.jpg";
	std::string wt1 = "./pts/" + m_transcode_param->device_name + "/wt1.jpg";
	std::string wt2 = "./pts/" + m_transcode_param->device_name + "/wt2.jpg";
	std::string wt3 = "./pts/" + m_transcode_param->device_name + "/wt3.jpg";
	weight_path.push_back(wt0);
	weight_path.push_back(wt1);
	weight_path.push_back(wt2);
	weight_path.push_back(wt3);
	m_pano_player->setweight(weight_path);
	Log::Info("panoplayer load weight mask successed, id:%ld", GetID());
}

int CTcsLiveChannel::Init(transcode_param_t* param)
{
	if (param == NULL) {
		Log::Error("transcode parament null, id:%ld", GetID());
		return ERROR_TRASCODE_PARAM_NULL;
	} else {
		copy_transcode_param(param);
	}

	m_surface = CTcsPanoPlayer::GetInstance().GetSurface();
	m_pano_player = (CapturePixelPanoPlayer*)m_surface->getPanoplayer();
	m_pano_player->setCapturePixelListener(this);
	m_pano_player->setPanoPlayerListener(this);
	m_pixelPlugin = m_pano_player->getPixelPlugin();
	m_surface->start(m_transcode_param->width, m_transcode_param->height);
	init_panoplayer();

	int ret = init_encode_param();
	if (ret != 0) {
		return ERROR_TRANSCODE_ENCODE;
	}

	ret = init_m1_player();
	if (ret != 0) {
		return ERROR_TRANSCODE_PLAYER_ERROR;
	}

	Log::Info("live channel init success, id:%d, device name:%s", GetID(), m_transcode_param->device_name.c_str());
	return ERROR_SUCCESS;
}

int CTcsLiveChannel::Start()
{
	if (m_rtmp_send_thread && m_rtmp_send_thread->joinable()) {
		m_rtmp_send_thread->join();
	}
	m_rtmp_send_thread.reset(new std::thread(&CTcsLiveChannel::handle_stream_output, this));

	return 0;
}

int CTcsLiveChannel::Close()
{
	if (m_m1_player) {
		m_m1_player->Close();
		delete m_m1_player;
		m_m1_player = NULL;
	}

	m_pixelPlugin->notifyStateChanged(PluginState_COMPLETED, "live channel close.");
	m_surface->stop();
	CTcsPanoPlayer::GetInstance().EnableSurface(m_surface);

	m_is_closed = true;
	if (m_rtmp_send_thread && m_rtmp_send_thread->joinable()){
		m_rtmp_send_thread->join();
	}

	if (m_rtmp_muxter){
		m_rtmp_muxter->close();
		delete m_rtmp_muxter;
		m_rtmp_muxter = NULL;
	}

	unsigned char* rgba = NULL;
	while (m_rgb_queue.size() > 0) {
		rgba = m_rgb_queue.pop();
		free(rgba);
	}
	if (m_yuv_data){
		free(m_yuv_data);
		m_yuv_data = NULL;
	}
	if (m_rgba_data){
		free(m_rgba_data);
		m_rgba_data = NULL;
	}
	if (m_image_convert) {
		delete m_image_convert;
	}

	Log::Info("live channel closed, id:%d, device name:%s", GetID(), m_transcode_param->device_name.c_str());
	return 0;
}

void CTcsLiveChannel::SetConfig(CTcsConfig* config)
{
	m_config = config;
	if (m_config){
		m_decode_type = m_config->GetDecodeType();
		m_encode_type = m_config->GetEncodeType();
		m_reserve_degress = m_config->GetReserveDegress();
		Log::Info("isreserve:%d, decode type:%d, encode type:%d", m_reserve_degress, m_decode_type, m_encode_type);
	}
}

void CTcsLiveChannel::SetNewPts(bool is_new_pts)
{
	m_is_pts_new = is_new_pts;
}

void CTcsLiveChannel::handle_stream_output()
{
	while (true)
	{
		if (m_is_closed){
			break;
		}

		if (m_render_transcode_ok){
			int ret = m_rtmp_muxter->send();
			if (ret != 0){
				std::unique_lock<std::mutex> lock(m_error_mtx);
				if (!m_is_error_occurred){
					m_is_error_occurred = true;
					lock.unlock();
					Log::Error("rtmp send error, id:%ld", GetID());
					Notify(m_owner, GetID(), ERROR_TRANSCODE_PUBLISH);
					break;
				} else {
					lock.unlock();
					Log::Info("error already notify to owner.");
					break;
				}
			}
		}
	}
	Log::Info("rtmp publish thread stop, id:%ld", GetID());
}

void CTcsLiveChannel::copy_transcode_param(transcode_param_t* src)
{
	if (src != NULL) {
		m_transcode_param = src;

		m_rgb_size = m_transcode_param->width * m_transcode_param->height * 4;
		m_yuv_data = (unsigned char*)malloc(m_transcode_param->width * m_transcode_param->height * 3 / 2);
		m_rgba_data = (unsigned char*)malloc(m_rgb_size);

		Log::Info("id:%ld, publish paraments: device name:%s, width:%d, height:%d, bitrate(kbps):%d, flie path:%s, publish url:%s",
			GetID(), m_transcode_param->device_name.c_str(), m_transcode_param->width, m_transcode_param->height, m_transcode_param->bitrate, m_transcode_param->rtmp_url.c_str(), m_transcode_param->push_url.c_str());
	}
}

int CTcsLiveChannel::init_m1_player()
{
	m_m1_player = new CM1Player(false);
	m_m1_player->SetDisplayFps(30);
	m_m1_player->SetDisplayTag(true);
	m_m1_player->SetRecordTag(false);
	m_m1_player->SetStreamType(StreamTypeRtmp);
	m_m1_player->SetOnwer(m_signal_id);
	if (m_decode_type == 1) {
		m_m1_player->SetDeocdeType(DecodeTypeIntel);
	} else if (m_decode_type == 2) {
		m_m1_player->SetDeocdeType(DecodeTypeCuda);
	} else {
		m_m1_player->SetDeocdeType(DecodeTypeSoft);
	}

	m1_player_config_s config;
	config.videoproc = std::bind(&CTcsLiveChannel::onVideoFrames, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	config.url = m_transcode_param->rtmp_url;

	int ret = m_m1_player->Init(config);
	if (ret != 0) {
		Log::Error("m1 player init error, id:%ld, publish url:%s", GetID(), m_transcode_param->push_url.c_str());
		return -1;
	}
	m_m1_player->Play();
	Log::Info("m1 player init success, id:%ld, publish url:%s", GetID(), m_transcode_param->push_url.c_str());
	return 0;
}

void CTcsLiveChannel::init_panoplayer()
{
	std::string calibration = get_calibration();

	PanoramaData panoData;
	PanoNodeImage imageData;
	imageData.panoResourceType = PanoResourceType_VIDEO;
	imageData.calibration = calibration;
	imageData.panoDeviceId = PanoDeviceId_SPHERE_DETU_M1;
	imageData.isPushFlow = true;
	if (m_reserve_degress){
		imageData.isCameraUpsideDown = true;
	} else {
		imageData.isCameraUpsideDown = false;
	}
	panoData.nodeImage = imageData;
	PanoNodeView viewData;
	viewData.curfov = viewData.deffov;
	viewData.vLookAt = 0;
	viewData.hLookAt = 0;
	viewData.viewMode = static_cast<PanoViewMode>(PanoViewMode_FLAT);
	panoData.nodeView = viewData;

	PlayerOption option;
	memset(&option, 0, sizeof(PlayerOption));
	option.type = PlayerOptionType_Player;
	option.key = PLAYER_OPTION_DETU_KEY_IS_BLOCK_FRAME;
	option.value = "true";
	std::vector<PlayerOption> options;
	options.push_back(option);
	m_pano_player->play(panoData, options);
}

int CTcsLiveChannel::init_encode_param()
{
	ffmpeg_cfg_s sconfig;
	memset(&sconfig, 0, sizeof(struct ffmpeg_cfg));

	sconfig.url = m_transcode_param->push_url.c_str();
	sconfig.format_name = NULL;
	sconfig.format_mime_type = NULL;
	sconfig.video_bitrate = m_transcode_param->bitrate;
	sconfig.audio_bitrate = 128;
	sconfig.video_encoder_id = AV_CODEC_ID_H264;

	if (m_encode_type == EncodeTypeNvenc){
		sconfig.video_encoder = "h264_nvenc";
	} else {
		sconfig.video_encoder = "libx264";
	}

	sconfig.audio_encoder_id = AV_CODEC_ID_NONE;
	sconfig.audio_encoder = "";
	sconfig.audio_settings = "";
	sconfig.format = AV_PIX_FMT_YUV420P;
	sconfig.scale_width = m_transcode_param->width;
	sconfig.scale_height = m_transcode_param->height;
	sconfig.width = m_transcode_param->width;
	sconfig.height = m_transcode_param->height;
	sconfig.color_range = AVCOL_RANGE_JPEG;
	sconfig.color_space = AVCOL_SPC_BT709;
	sconfig.muxer_settings = "";
	sconfig.fps = m_transcode_param->fps;

	sconfig.audio_samples_per_sec = 44100;
	sconfig.audio_speakers = SPEAKERS_STEREO;
	sconfig.audio_format = AUDIO_FORMAT_FLOAT_PLANAR;

	if (astrcmpi_n(sconfig.url, "rtmp://", 7) == 0){
		sconfig.audio_encoder_id = AV_CODEC_ID_NONE;
	}

	if (m_rtmp_muxter){
		int ret = m_rtmp_muxter->open(sconfig);
		if (ret != 0){
			Log::Error("open rtmp muter error, id:%ld", GetID());
			return -1;
		}
	}
	Log::Info("rtmp muxer init success, id:%ld", GetID());

	return 0;
}

int CTcsLiveChannel::init_dpv_render(m1_video_frame_s** av_frame_sync_list_)
{
	PluginMetaData metadata;
	metadata.height = av_frame_sync_list_[0]->h;
	metadata.width = av_frame_sync_list_[0]->w;
	for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
		metadata.lineSize[i] = av_frame_sync_list_[0]->linesize[i];
	}

	if (av_frame_sync_list_[0]->format == PIX_FMT_YUV420P) {
		metadata.pluginFormat = PluginColorFormat_YUV420P;
	}
	else if (av_frame_sync_list_[0]->format == PIX_FMT_NV12) {
		metadata.pluginFormat = PluginColorFormat_NV12;
	}
	vector<PluginMetaData> metadata_vector;
	metadata_vector.push_back(metadata);
	m_pixelPlugin->notifyMetaDatas(metadata_vector);
	m_pixelPlugin->notifyStateChanged(PluginState_PREPARED, "m1 player ready.");

	Log::Info("dpv renader init succesed, id:%ld", GetID());
	return 0;
}

int CTcsLiveChannel::rtmp_write_video(unsigned char* yuv)
{
	struct video_data vframe;
	vframe.width = m_transcode_param->width;
	vframe.height = m_transcode_param->height;

	vframe.data[0] = yuv;
	vframe.data[1] = yuv + m_transcode_param->width * m_transcode_param->height;
	vframe.data[2] = vframe.data[1] + m_transcode_param->width * m_transcode_param->height / 4;

	vframe.linesize[0] = m_transcode_param->width;
	vframe.linesize[1] = m_transcode_param->width / 2;
	vframe.linesize[2] = m_transcode_param->width / 2;

	for (int i = 3; i < k_NUM_DATA_POINTERS; i++){
		vframe.data[i] = NULL;
		vframe.linesize[i] = 0;
	}

	int ret = m_rtmp_muxter->writeVideo(&vframe);
	if (ret != 0){
		std::unique_lock<std::mutex> lock(m_error_mtx);
		if (!m_is_error_occurred){
			m_is_error_occurred = true;
			lock.unlock();
			Log::Error("rtmp encode video error, id:%ld", GetID());
			Notify(m_owner, GetID(), ERROR_TRANSCODE_PUBLISH);
		} else {
			lock.unlock();
			Log::Info("error already notify to owner.");
		}
	}

	//audio
	struct audio_data empty_audio;
	memset(empty_audio.data, 0, MAX_AV_PLANES);
	empty_audio.frames = 0;
	empty_audio.timestamp = 0;

	m_rtmp_muxter->writeAudio(&empty_audio);

	return 0;
}

std::string CTcsLiveChannel::get_calibration()
{
	std::string calibration;
	if (m_is_pts_new){
		std::string pts = "./pts/" + m_transcode_param->device_name + "/pat.pts";
		std::string wt0 = "./pts/" + m_transcode_param->device_name + "/wt0.jpg";
		std::string wt1 = "./pts/" + m_transcode_param->device_name + "/wt1.jpg";
		std::string wt2 = "./pts/" + m_transcode_param->device_name + "/wt2.jpg";
		std::string wt3 = "./pts/" + m_transcode_param->device_name + "/wt3.jpg";
		std::vector<std::string> result_path;
		result_path.push_back(wt0);
		result_path.push_back(wt1);
		result_path.push_back(wt2);
		result_path.push_back(wt3);
		WeightAndMaskData weightdata;
		memset(weightdata.biaoding, 0, 512);
		bool result = getResultwithpath(pts, weightdata, result_path);
		if (result){
			create_calibration_file(weightdata.biaoding, 512);
			return weightdata.biaoding;
		}
	} else {
		std::string dir = get_work_path();
		std::string filename = dir + "calibration.txt";

		char data[512] = { 0 };
		FILE* cal = fopen(filename.c_str(), "rb+");
		if (cal == NULL){
			Log::Error("can't find calibration file, id:%ld, device name:%s", GetID(), m_transcode_param->device_name.c_str());
			return calibration;
		}
		fread(data, 1, 512, cal);
		fclose(cal);
		calibration = data;
	}

	return calibration;
}

std::string CTcsLiveChannel::get_work_path()
{
	char cwd[MAX_DIRECT_LENGTH];
	getcwd(cwd, MAX_DIRECT_LENGTH);

	char pts[32] = { 0 };
	sprintf(pts, "\\pts\\%s\\", m_transcode_param->device_name.c_str());

	std::string dir = cwd;
	dir += pts;
	return dir;
}

void CTcsLiveChannel::create_calibration_file(char* data, int length)
{
	std::string calibration = data;
	std::string dir = get_work_path();
	std::string filename = dir + "calibration.txt";
	FILE* cal = fopen(filename.c_str(), "wb+");
	fwrite(calibration.c_str(), 1, calibration.size(), cal);
	fflush(cal);
	fclose(cal);
}

int CTcsLiveChannel::imp_dataconvert_rgba2yuv420(unsigned char *srcImg, int width, int height,
	unsigned char *yImg, unsigned char *uImg, unsigned char *vImg)
{
	int i, j;
	int offset;
	int offset2;
	int tmp;
	int b, g, r, a;
	int halfW, width4;
	unsigned char *pSrc = NULL;
	unsigned char *py = NULL;
	unsigned char *pu = NULL;
	unsigned char *pv = NULL;

	// ²ÎÊý¼ì²â
	if ((NULL == srcImg) || (NULL == yImg) || (NULL == uImg) || (NULL == vImg))
	{
		return -1;
	}

	width4 = width << 2;
	halfW = width >> 1;

	pSrc = srcImg;
	py = yImg;
	pu = uImg;
	pv = vImg;
	for (j = 0; j < height; j++)
	{
		if ((j & 1) == 1)
		{
			offset = 0;
			for (i = 0; i < width; i++)
			{
				r = pSrc[offset];
				g = pSrc[offset + 1];
				b = pSrc[offset + 2];
				a = pSrc[offset + 3];
				if (a > 0)
				{
					tmp = ((77 * r + 150 * g + 29 * b) >> 8);
					if (tmp > 255)
					{
						py[i] = 255;
					}
					else
					{
						py[i] = tmp;
					}
				}
				else
				{
					py[i] = 0;
				}

				offset += 4;
			}

		}
		else
		{
			offset = 0;
			for (i = 0; i < width; i++)
			{
				r = pSrc[offset];
				g = pSrc[offset + 1];
				b = pSrc[offset + 2];
				a = pSrc[offset + 3];
				if (a > 0)
				{
					tmp = ((77 * r + 150 * g + 29 * b) >> 8);
					if (tmp > 255)
					{
						py[i] = 255;
					}
					else
					{
						py[i] = tmp;
					}

					if ((i & 1) == 0)
					{
						offset2 = (i >> 1);
						tmp = ((128 * b - 43 * r - 85 * g + IMP_128_SHIFT8) >> 8);
						if (tmp >= 0 && tmp < 256)
						{
							pu[offset2] = tmp;
						}
						else if (tmp < 0)
						{
							pu[offset2] = 0;
						}
						else
						{
							pu[offset2] = 255;
						}

						tmp = ((128 * r - 107 * g - 21 * b + IMP_128_SHIFT8) >> 8);
						if (tmp >= 0 && tmp < 256)
						{
							pv[offset2] = tmp;
						}
						else if (tmp < 0)
						{
							pv[offset2] = 0;
						}
						else
						{
							pv[offset2] = 255;
						}
					}
				}
				else
				{
					py[i] = 0;
					if ((i & 1) == 0)
					{
						offset2 = (i >> 1);
						pu[offset2] = 0;
						pv[offset2] = 0;
					}
				}

				offset += 4;
			}
			pu += halfW;
			pv += halfW;
		}

		py += width;
		pSrc += width4;
	}


	return 0;
}
