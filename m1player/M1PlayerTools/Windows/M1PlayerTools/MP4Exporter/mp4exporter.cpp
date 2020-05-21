#include "mp4exporter.h"
#include <QFileDialog>
#include "Mp4Muxer.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/display.h"
#include "libavutil/eval.h"
#include "libavutil/base64.h"
#include "libavutil/error.h"
#include "libavutil/opt.h"
#include "libavutil/version.h"
#include "libswresample/swresample.h"
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
}

MP4Exporter::MP4Exporter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_width = 0;
	m_height = 0;
	m_fps = 0;
	m_pos = 0;
	m_bitrate = 0;
	m_is_color = false;

	connect(ui.openfileButton, SIGNAL(clicked()), this, SLOT(onOpenFileButtonClick()));
	connect(ui.exportButton, SIGNAL(clicked()), this, SLOT(onExportButtonClick()));
	connect(this, SIGNAL(ExportBtnColorSig(bool)), this, SLOT(onExportBtnColoring(bool)));
	av_register_all();
}

MP4Exporter::~MP4Exporter()
{
	if (m_export_thread && m_export_thread->joinable()){
		m_export_thread->join();
	}
}

void MP4Exporter::onOpenFileButtonClick()
{
	m_file_path = QFileDialog::getOpenFileName(this,
		tr("Open Video"), tr("Image Files"));

	ui.lineEdit_filename->setText(m_file_path);

	QString export_name = QString("Export");
	ui.exportButton->setText(export_name);

	m_width = 0;//ui.lineEdit_width->text().toInt();
	m_height = 0;//ui.lineEdit_height->text().toInt();
	m_fps = 0;//ui.lineEdit_fps->text().toInt();
	m_bitrate = 0;//ui.lineEdit_bitRate->text().toInt();
	m_pos = 0;//ui.lineEdit_pos->text().toInt();

	char name[512] = { 0 };
	std::string input_path = m_file_path.toLocal8Bit().data();
	std::string output_path = input_path;
	output_path.append("_out.mp4");
	ansi_to_utf8(output_path.c_str(), name);

	//ffmepg
	AVFormatContext *pFormatCtx = NULL;
	AVCodecContext *pCodecCtx = NULL;
	AVCodec *pCodec = NULL;

	pFormatCtx = avformat_alloc_context();
	if (avformat_open_input(&pFormatCtx, input_path.c_str(), NULL, NULL) != 0) {
		Log::Error("open input file:%s error.", input_path.c_str());
		return;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		Log::Error("find stream info error.");
		return;
	}
	int videoindex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
		videoindex = i;
		break;
	}
	if (videoindex == -1) {
		return;
	}
	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		Log::Error("find decoder error.");
		return;
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		Log::Error("open codec error.");
		return;
	}

	if (m_width == 0){
		m_width = pCodecCtx->width;

		QString str_width = QString::number(m_width);
		ui.lineEdit_width->setText(str_width);
	}
	if (m_height == 0){
		m_height = pCodecCtx->height;

		QString str_height = QString::number(m_height);
		ui.lineEdit_height->setText(str_height);
	}
	if (m_fps == 0){
		m_fps = pCodecCtx->time_base.den / (pCodecCtx->time_base.num * pCodecCtx->ticks_per_frame);

		QString str_fps = QString::number(m_fps);
		ui.lineEdit_fps->setText(str_fps);
	}
	if (m_bitrate == 0){
		m_bitrate = pFormatCtx->bit_rate / 1000;

		QString str_bitrate = QString::number(m_bitrate);
		ui.lineEdit_bitRate->setText(str_bitrate);
	}
	if (m_pos == 0){
		m_pos = 0;

		QString str_pos = QString::number(m_pos);
		ui.lineEdit_pos->setText(str_pos);
	}

	if (pCodecCtx) {
		avcodec_close(pCodecCtx);
	}
	if (pFormatCtx) {
		avformat_close_input(&pFormatCtx);
	}
}

void MP4Exporter::onExportButtonClick()
{
	QString export_name = QString("Exporting...");
	ui.exportButton->setText(export_name);

	emit ExportBtnColorSig(true);

	if (m_export_thread && m_export_thread->joinable()){
		m_export_thread->join();
	}
	m_export_thread.reset(new std::thread(&MP4Exporter::export_mp4, this));
}

int MP4Exporter::ansi_to_utf8(const char* pszCode, char* UTF8code)
{
	WCHAR Unicode[100] = { 0, };
	char utf8[100] = { 0, };

	// read char Lenth
	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), Unicode, sizeof(Unicode));
	memset(UTF8code, 0, nUnicodeSize + 1);
	// read UTF-8 Lenth
	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, Unicode, nUnicodeSize, UTF8code, sizeof(Unicode), NULL, NULL);

	// convert to UTF-8 
	MultiByteToWideChar(CP_UTF8, 0, utf8, nUTF8codeSize, Unicode, sizeof(Unicode));
	UTF8code[nUTF8codeSize + 1] = '\0';
	return nUTF8codeSize;
}

void MP4Exporter::onExportBtnColoring(bool color)
{
	if (color)
	{
		ui.exportButton->setStyleSheet("QPushButton{background-color: #00aa00;}");
	}
	else
	{
		ui.exportButton->setStyleSheet("QPushButton{background-color: #eeeeee;}");
	}
	
}

void MP4Exporter::export_mp4(void)
{
	char name[512] = { 0 };
	std::string input_path = m_file_path.toLocal8Bit().data();
	std::string output_path = input_path;
	output_path.append("_out.mp4");
	ansi_to_utf8(output_path.c_str(), name);

	//ffmepg
	AVFormatContext *pFormatCtx = NULL;
	AVCodecContext *pCodecCtx = NULL;
	AVCodec *pCodec = NULL;
	AVFrame *pFrame = NULL;
	AVPacket *packet = NULL;

	pFormatCtx = avformat_alloc_context();
	if (avformat_open_input(&pFormatCtx, input_path.c_str(), NULL, NULL) != 0) {
		Log::Error("open input file:%s error.", input_path.c_str());
		return;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		Log::Error("find stream info error.");
		return;
	}
	int videoindex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
		videoindex = i;
		break;
	}
	if (videoindex == -1) {
		return;
	}
	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		Log::Error("find decoder error.");
		return;
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		Log::Error("open codec error.");
		return;
	}

	//Mp4Muxer init param
	ffmpeg_cfg_s sconfig;
	memset(&sconfig, 0, sizeof(struct ffmpeg_cfg));
	sconfig.url = name;
	sconfig.format_name = "mp4";
	sconfig.format_mime_type = NULL;
	sconfig.video_bitrate = m_bitrate;
	sconfig.audio_bitrate = 128;
	sconfig.video_encoder_id = AV_CODEC_ID_H264;
	sconfig.video_encoder = "libx264";
	sconfig.audio_encoder_id = AV_CODEC_ID_NONE;
	sconfig.audio_encoder = "";
	sconfig.audio_settings = "";
	sconfig.format = AV_PIX_FMT_YUV420P;
	sconfig.scale_width = m_width;
	sconfig.scale_height = m_height;
	sconfig.width = m_width;
	sconfig.height = m_height;
	sconfig.color_range = AVCOL_RANGE_JPEG;
	sconfig.color_space = AVCOL_SPC_BT709;
	sconfig.muxer_settings = "";
	sconfig.fps = m_fps;
	sconfig.audio_samples_per_sec = 44100;
	sconfig.audio_speakers = SPEAKERS_STEREO;
	sconfig.audio_format = AUDIO_FORMAT_FLOAT_PLANAR;

	Mp4Muxer* mp4muxer = new Mp4Muxer();
	int ret = mp4muxer->open(sconfig);
	if (ret != 0) {
		ret = mp4muxer->reopen(sconfig);
		if (ret != 0) {
			Log::Error("open mp4muxer error.");
			return;
		}
	}

	int frame_num = 0;
	int got_picture = 0;
	pFrame = av_frame_alloc();
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	while (av_read_frame(pFormatCtx, packet) >= 0) {
		if (packet->stream_index == videoindex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) {
				//TODO
			}
			if (got_picture) {
				frame_num++;
				if (frame_num >= m_pos) {
					struct video_data vframe;
					vframe.width = sconfig.width;
					vframe.height = sconfig.height;

					for (int i = 0; i < MAX_AV_PLANES; i++) {
						if (i < 3) {
							vframe.data[i] = pFrame->data[i];
							vframe.linesize[i] = pFrame->linesize[i];
							continue;
						}
						vframe.data[i] = NULL;
						vframe.linesize[i] = 0;
					}
					vframe.timestamp = pFrame->pts;
					ret = mp4muxer->writeVideo(&vframe);
				}
			}
		}
		av_free_packet(packet);
	}

	if (pFrame) {
		av_frame_free(&pFrame);
	}
	if (pCodecCtx) {
		avcodec_close(pCodecCtx);
	}
	if (pFormatCtx) {
		avformat_close_input(&pFormatCtx);
	}
	if (packet) {
		av_free_packet(packet);
	}
	if (mp4muxer) {
		mp4muxer->close();
	}

	QString export_name = QString("Export Successed.");
	ui.exportButton->setText(export_name);

	emit ExportBtnColorSig(false);

	Log::Info("export mp4 success.");
}
