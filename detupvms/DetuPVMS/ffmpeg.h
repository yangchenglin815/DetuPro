#pragma once

#if _MSC_VER
#define snprintf _snprintf
#endif

extern "C"
{
#ifdef __cplusplus
	#ifndef __STDC_CONSTANT_MACROS
		#define __STDC_CONSTANT_MACROS
	#endif
	#ifdef _STDINT_H
		#undef _STDINT_H
	#endif
	# include <stdint.h>
#endif


#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/log.h>
#include <libavutil/attributes.h>
#include <libavutil/mathematics.h>
#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/imgutils.h>
#include <libavutil/fifo.h>
#include <libavutil/timestamp.h>
}


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "logging.hpp"
#include "panoutil.h"
#include "media.h"



#define MAX_AV_PLANES 8

static char err_buf[AV_ERROR_MAX_STRING_SIZE];
#define av_err2str_new(errnum) \
	av_make_error_string(err_buf, AV_ERROR_MAX_STRING_SIZE, errnum)

static char time_str_buf[AV_TS_MAX_STRING_SIZE];
#define av_ts2timestr_new(ts, tb) av_ts_make_time_string(time_str_buf, ts, tb)
#define av_ts2str_new(ts) av_ts_make_string(time_str_buf, ts)

#define av_fftime_to_milliseconds(ts) (av_rescale(ts, 1000, AV_TIME_BASE))
#define av_milliseconds_to_fftime(ms) (av_rescale(ms, AV_TIME_BASE, 1000))


typedef std::pair<std::string, std::string> FfmpegOption;

struct video_data {
	uint8_t           *data[MAX_AV_PLANES];
	uint32_t          linesize[MAX_AV_PLANES];
	uint64_t          timestamp;

	int width;
	int height;
};

struct audio_data {
	uint8_t             *data[MAX_AV_PLANES];
	uint32_t            frames;
	uint64_t            timestamp;
};


struct ffmpeg_cfg {
	const char         *url;
	std::string        save_dir;
	const char         *format_name;
	const char         *format_mime_type;
	const char         *url_options_settings;
	const char         *muxer_settings;
	int                video_bitrate;
	int                audio_bitrate;
	const char         *video_encoder;
	int                video_encoder_id;
	const char         *audio_encoder;
	int                audio_encoder_id;
	const char         *video_settings;
	const char         *audio_settings;
	enum AVPixelFormat format;
	enum AVColorRange  color_range;
	enum AVColorSpace  color_space;
	int                scale_width;
	int                scale_height;
	int                width;
	int                height;

	int               writeflag;
	char*             device_name;

			  

	uint32_t            audio_samples_per_sec;
	enum audio_format   audio_format;
	enum speaker_layout audio_speakers;
	int fps;

	ffmpeg_cfg(){
		memset(this, NULL, sizeof(struct ffmpeg_cfg));
	}
};
typedef struct ffmpeg_cfg ffmpeg_cfg_s;


struct ffmpeg_data{

	AVStream           *video;
	AVStream           *audio;
	AVCodec            *acodec;
	AVCodec            *vcodec;
	AVFormatContext    *output;
	struct SwsContext  *swscale;

	int64_t            total_frames;
	int64_t            total_audio_frames;
	AVPicture          dst_picture;
	AVFrame            *vframe;
	int                frame_size;


	int64_t            total_samples;
	uint32_t           audio_samplerate;
	enum audio_format  audio_format;
	size_t             audio_planes;
	size_t             audio_size;
	struct circlebuf   excess_frames[MAX_AV_PLANES];
	uint8_t            *samples[MAX_AV_PLANES];
	AVFrame            *aframe;

	bool               is_rtmp;
	AVFifoBuffer *fifo;
	int buffer_size;
	struct ffmpeg_cfg  config;

	bool               initialized;

	ffmpeg_data() :video(NULL), audio(NULL), acodec(NULL), vcodec(NULL), output(NULL),
		swscale(NULL), vframe(NULL){
		memset(this, NULL, sizeof(struct ffmpeg_data));
	}
};


typedef struct ffmpeg_data ffmpeg_data_s;

static inline void ffmpegOptions(const std::vector<FfmpegOption>& src, AVDictionary** dst)
{
	int size = (int)src.size();
	for (int i = 0; i < size; i++)
		av_dict_set(dst, src[i].first.c_str(), src[i].second.c_str(), 0);
}


static const enum AVPixelFormat i420_formats[] = {
	AV_PIX_FMT_YUV420P,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_YUV422P,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat nv12_formats[] = {
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_YUV420P,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat i444_formats[] = {
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_RGBA,
	AV_PIX_FMT_BGRA,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat yuy2_formats[] = {
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_YUV420P,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat uyvy_formats[] = {
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_YUV420P,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat rgba_formats[] = {
	AV_PIX_FMT_RGBA,
	AV_PIX_FMT_BGRA,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_NONE
};

static const enum AVPixelFormat bgra_formats[] = {
	AV_PIX_FMT_BGRA,
	AV_PIX_FMT_RGBA,
	AV_PIX_FMT_YUV444P,
	AV_PIX_FMT_YUYV422,
	AV_PIX_FMT_UYVY422,
	AV_PIX_FMT_NV12,
	AV_PIX_FMT_NV21,
	AV_PIX_FMT_NONE
};

static enum AVPixelFormat get_best_format(
	const enum AVPixelFormat *best,
	const enum AVPixelFormat *formats)
{
	while (*best != AV_PIX_FMT_NONE) {
		enum AVPixelFormat best_format = *best;
		const enum AVPixelFormat *cur_formats = formats;

		while (*cur_formats != AV_PIX_FMT_NONE) {
			enum AVPixelFormat avail_format = *cur_formats;

			if (best_format == avail_format)
				return best_format;

			cur_formats++;
		}

		best++;
	}

	return AV_PIX_FMT_NONE;
}

static inline enum AVPixelFormat get_closest_format(
enum AVPixelFormat format,
	const enum AVPixelFormat *formats)
{
	enum AVPixelFormat best_format = AV_PIX_FMT_NONE;

	if (!formats || formats[0] == AV_PIX_FMT_NONE)
		return format;


	switch ((int)format) {

	case AV_PIX_FMT_YUV444P:
		best_format = get_best_format(i444_formats, formats);
		break;
	case AV_PIX_FMT_YUV420P:
		best_format = get_best_format(i420_formats, formats);
		break;
	case AV_PIX_FMT_NV12:
		best_format = get_best_format(nv12_formats, formats);
		break;
	case AV_PIX_FMT_YUYV422:
		best_format = get_best_format(yuy2_formats, formats);
		break;
	case AV_PIX_FMT_UYVY422:
		best_format = get_best_format(uyvy_formats, formats);
		break;
	case AV_PIX_FMT_RGBA:
		best_format = get_best_format(rgba_formats, formats);
		break;
	case AV_PIX_FMT_BGRA:
		best_format = get_best_format(bgra_formats, formats);
		break;
	}


	return (best_format == AV_PIX_FMT_NONE) ? formats[0] : best_format;
}

static void parse_params(AVCodecContext *context, char **opts)
{
	if (!context || !context->priv_data)
		return;

	while (*opts) {
		char *opt = *opts;
		char *assign = strchr(opt, '=');

		if (assign) {
			char *name = opt;
			char *value;

			*assign = 0;
			value = assign + 1;

			av_opt_set(context->priv_data, name, value, 0);
		}

		opts++;
	}
}


static inline void copy_data(AVPicture *pic, const struct video_data *frame,
	int height)
{
	for (int plane = 0; plane < MAX_AV_PLANES; plane++) {
		if (!frame->data[plane])
			continue;

		int frame_rowsize = (int)frame->linesize[plane];
		int pic_rowsize = pic->linesize[plane];
		int bytes = frame_rowsize < pic_rowsize ?
		frame_rowsize : pic_rowsize;
		int plane_height = plane == 0 ? height : height / 2;

		for (int y = 0; y < plane_height; y++) {
			int pos_frame = y * frame_rowsize;
			int pos_pic = y * pic_rowsize;

			memcpy(pic->data[plane] + pos_pic,
				frame->data[plane] + pos_frame,
				bytes);
		}
	}
}

static inline int64_t rescale_ts(int64_t val, AVCodecContext *context,
	AVRational new_base)
{
	return av_rescale_q_rnd(val, context->time_base, new_base,
		AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
}




static inline enum audio_format convert_ffmpeg_sample_format(
enum AVSampleFormat format)
{
	switch ((uint32_t)format) {
	case AV_SAMPLE_FMT_U8:   return AUDIO_FORMAT_U8BIT;
	case AV_SAMPLE_FMT_S16:  return AUDIO_FORMAT_16BIT;
	case AV_SAMPLE_FMT_S32:  return AUDIO_FORMAT_32BIT;
	case AV_SAMPLE_FMT_FLT:  return AUDIO_FORMAT_FLOAT;
	case AV_SAMPLE_FMT_U8P:  return AUDIO_FORMAT_U8BIT_PLANAR;
	case AV_SAMPLE_FMT_S16P: return AUDIO_FORMAT_16BIT_PLANAR;
	case AV_SAMPLE_FMT_S32P: return AUDIO_FORMAT_32BIT_PLANAR;
	case AV_SAMPLE_FMT_FLTP: return AUDIO_FORMAT_FLOAT_PLANAR;
	}

	/* shouldn't get here */
	return AUDIO_FORMAT_16BIT;
}

static inline uint32_t get_audio_channels(enum speaker_layout speakers)
{
	switch (speakers) {
	case SPEAKERS_MONO:             return 1;
	case SPEAKERS_STEREO:           return 2;
	case SPEAKERS_2POINT1:          return 3;
	case SPEAKERS_SURROUND:
	case SPEAKERS_QUAD:             return 4;
	case SPEAKERS_4POINT1:          return 5;
	case SPEAKERS_5POINT1:
	case SPEAKERS_5POINT1_SURROUND: return 6;
	case SPEAKERS_7POINT1:          return 8;
	case SPEAKERS_7POINT1_SURROUND: return 8;
	case SPEAKERS_UNKNOWN:          return 0;
	}

	return 0;
}

static inline size_t get_audio_bytes_per_channel(enum audio_format format)
{
	switch (format) {
	case AUDIO_FORMAT_U8BIT:
	case AUDIO_FORMAT_U8BIT_PLANAR:
		return 1;

	case AUDIO_FORMAT_16BIT:
	case AUDIO_FORMAT_16BIT_PLANAR:
		return 2;

	case AUDIO_FORMAT_FLOAT:
	case AUDIO_FORMAT_FLOAT_PLANAR:
	case AUDIO_FORMAT_32BIT:
	case AUDIO_FORMAT_32BIT_PLANAR:
		return 4;

	case AUDIO_FORMAT_UNKNOWN:
		return 0;
	}

	return 0;
}
static inline bool is_audio_planar(enum audio_format format)
{
	switch (format) {
	case AUDIO_FORMAT_U8BIT:
	case AUDIO_FORMAT_16BIT:
	case AUDIO_FORMAT_32BIT:
	case AUDIO_FORMAT_FLOAT:
		return false;

	case AUDIO_FORMAT_U8BIT_PLANAR:
	case AUDIO_FORMAT_FLOAT_PLANAR:
	case AUDIO_FORMAT_16BIT_PLANAR:
	case AUDIO_FORMAT_32BIT_PLANAR:
		return true;

	case AUDIO_FORMAT_UNKNOWN:
		return false;
	}

	return false;
}

static inline size_t get_audio_planes(enum audio_format format,
enum speaker_layout speakers)
{
	return (is_audio_planar(format) ? get_audio_channels(speakers) : 1);
}

static inline size_t get_audio_size(enum audio_format format,
enum speaker_layout speakers, uint32_t frames)
{
	bool planar = is_audio_planar(format);

	return (planar ? 1 : get_audio_channels(speakers)) *
		get_audio_bytes_per_channel(format) *
		frames;
}

static inline enum audio_format convert_sample_format(int f)
{
	switch (f) {
	case AV_SAMPLE_FMT_U8:   return AUDIO_FORMAT_U8BIT;
	case AV_SAMPLE_FMT_S16:  return AUDIO_FORMAT_16BIT;
	case AV_SAMPLE_FMT_S32:  return AUDIO_FORMAT_32BIT;
	case AV_SAMPLE_FMT_FLT:  return AUDIO_FORMAT_FLOAT;
	case AV_SAMPLE_FMT_U8P:  return AUDIO_FORMAT_U8BIT_PLANAR;
	case AV_SAMPLE_FMT_S16P: return AUDIO_FORMAT_16BIT_PLANAR;
	case AV_SAMPLE_FMT_S32P: return AUDIO_FORMAT_32BIT_PLANAR;
	case AV_SAMPLE_FMT_FLTP: return AUDIO_FORMAT_FLOAT_PLANAR;
	default:;
	}

	return AUDIO_FORMAT_UNKNOWN;
}


static inline enum AVPixelFormat obs_to_ffmpeg_video_format(
enum video_format format)
{
	switch (format) {
	case VIDEO_FORMAT_NONE: return AV_PIX_FMT_NONE;
	case VIDEO_FORMAT_I444: return AV_PIX_FMT_YUV444P;
	case VIDEO_FORMAT_I420: return AV_PIX_FMT_YUV420P;
	case VIDEO_FORMAT_NV12: return AV_PIX_FMT_NV12;
	case VIDEO_FORMAT_YVYU: return AV_PIX_FMT_NONE;
	case VIDEO_FORMAT_YUY2: return AV_PIX_FMT_YUYV422;
	case VIDEO_FORMAT_UYVY: return AV_PIX_FMT_UYVY422;
	case VIDEO_FORMAT_RGBA: return AV_PIX_FMT_RGBA;
	case VIDEO_FORMAT_BGRA: return AV_PIX_FMT_BGRA;
	case VIDEO_FORMAT_BGRX: return AV_PIX_FMT_BGRA;
	}

	return AV_PIX_FMT_NONE;
}

static inline enum video_format ffmpeg_to_obs_video_format(
enum AVPixelFormat format)
{
	switch (format) {
	case AV_PIX_FMT_YUV444P: return VIDEO_FORMAT_I444;
	case AV_PIX_FMT_YUV420P: return VIDEO_FORMAT_I420;
	case AV_PIX_FMT_NV12:    return VIDEO_FORMAT_NV12;
	case AV_PIX_FMT_YUYV422: return VIDEO_FORMAT_YUY2;
	case AV_PIX_FMT_UYVY422: return VIDEO_FORMAT_UYVY;
	case AV_PIX_FMT_RGBA:    return VIDEO_FORMAT_RGBA;
	case AV_PIX_FMT_BGRA:    return VIDEO_FORMAT_BGRA;
	case AV_PIX_FMT_NONE:
	default:                 return VIDEO_FORMAT_NONE;
	}
}

static inline void *bzalloc(size_t size)
{
	void *mem = malloc(size);
	if (mem)
		memset(mem, 0, size);
	return mem;
}


static inline enum AVSampleFormat convert_audio_format(enum audio_format format)
{
	switch (format) {
	case AUDIO_FORMAT_UNKNOWN:      return AV_SAMPLE_FMT_S16;
	case AUDIO_FORMAT_U8BIT:        return AV_SAMPLE_FMT_U8;
	case AUDIO_FORMAT_16BIT:        return AV_SAMPLE_FMT_S16;
	case AUDIO_FORMAT_32BIT:        return AV_SAMPLE_FMT_S32;
	case AUDIO_FORMAT_FLOAT:        return AV_SAMPLE_FMT_FLT;
	case AUDIO_FORMAT_U8BIT_PLANAR: return AV_SAMPLE_FMT_U8P;
	case AUDIO_FORMAT_16BIT_PLANAR: return AV_SAMPLE_FMT_S16P;
	case AUDIO_FORMAT_32BIT_PLANAR: return AV_SAMPLE_FMT_S32P;
	case AUDIO_FORMAT_FLOAT_PLANAR: return AV_SAMPLE_FMT_FLTP;
	}

	/* shouldn't get here */
	return AV_SAMPLE_FMT_S16;
}

static inline uint64_t convert_speaker_layout(enum speaker_layout layout)
{
	switch (layout) {
	case SPEAKERS_UNKNOWN:          return 0;
	case SPEAKERS_MONO:             return AV_CH_LAYOUT_MONO;
	case SPEAKERS_STEREO:           return AV_CH_LAYOUT_STEREO;
	case SPEAKERS_2POINT1:          return AV_CH_LAYOUT_2_1;
	case SPEAKERS_QUAD:             return AV_CH_LAYOUT_QUAD;
	case SPEAKERS_4POINT1:          return AV_CH_LAYOUT_4POINT1;
	case SPEAKERS_5POINT1:          return AV_CH_LAYOUT_5POINT1;
	case SPEAKERS_5POINT1_SURROUND: return AV_CH_LAYOUT_5POINT1_BACK;
	case SPEAKERS_7POINT1:          return AV_CH_LAYOUT_7POINT1;
	case SPEAKERS_7POINT1_SURROUND: return AV_CH_LAYOUT_7POINT1_WIDE_BACK;
	case SPEAKERS_SURROUND:         return AV_CH_LAYOUT_SURROUND;
	}

	/* shouldn't get here */
	return 0;
}

enum video_scale_type {
	VIDEO_SCALE_DEFAULT,
	VIDEO_SCALE_POINT,
	VIDEO_SCALE_FAST_BILINEAR,
	VIDEO_SCALE_BILINEAR,
	VIDEO_SCALE_BICUBIC,
};

struct video_scale_info {
	enum video_format     format;
	uint32_t              width;
	uint32_t              height;
	enum video_range_type range;
	enum video_colorspace colorspace;
};


enum obs_encoder_type {
	OBS_ENCODER_AUDIO, /**< The encoder provides an audio codec */
	OBS_ENCODER_VIDEO  /**< The encoder provides a video codec */
};

/** Encoder output packet */
struct encoder_packet {
	uint8_t               *data;        /**< Packet data */
	size_t                size;         /**< Packet size */

	int64_t               pts;          /**< Presentation timestamp */
	int64_t               dts;          /**< Decode timestamp */

	int32_t               timebase_num; /**< Timebase numerator */
	int32_t               timebase_den; /**< Timebase denominator */

	enum obs_encoder_type type;         /**< Encoder type */

	bool                  keyframe;     /**< Is a keyframe */

	/* ---------------------------------------------------------------- */
	/* Internal video variables (will be parsed automatically) */

	/* DTS in microseconds */
	int64_t               dts_usec;

	/**
	* Packet priority
	*
	* This is generally use by video encoders to specify the priority
	* of the packet.
	*/
	int                   priority;

	/**
	* Dropped packet priority
	*
	* If this packet needs to be dropped, the next packet must be of this
	* priority or higher to continue transmission.
	*/
	int                   drop_priority;

	/** Audio track index (used with outputs) */
	size_t                track_idx;

};

/** Encoder input frame */
struct encoder_frame {
	/** Data for the frame/audio */
	uint8_t               *data[MAX_AV_PLANES];

	/** size of each plane */
	uint32_t              linesize[MAX_AV_PLANES];

	/** Number of frames (audio only) */
	uint32_t              frames;

	/** Presentation timestamp */
	int64_t               pts;
};

