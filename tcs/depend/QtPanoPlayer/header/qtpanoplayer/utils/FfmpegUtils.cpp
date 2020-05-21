//
//  FfmpegUtils.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/28.
//

#include "FfmpegUtils.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}
#include "HttpUtils.h"

namespace DetuPanoPlayer {
    
    bool FfmpegUtils::loadImage(string fileAbsolutePath, int maxWidth, FfmpegLoadImgResult* outResult, FfmpegLoadImgFmt fmt) {
        AVFormatContext *pFormatCtx;
        AVCodecContext  *pCodecCtx;
        AVCodec         *pCodec;
        AVFrame *pFrame,*pFrameYUV;
        uint8_t *out_buffer;
        AVPacket *packet;
        int ret, got_picture;
        struct SwsContext *img_convert_ctx;
        av_register_all();
        pFormatCtx = avformat_alloc_context();
        const char* url = fileAbsolutePath.c_str();
        if((ret = avformat_open_input(&pFormatCtx, url, NULL, NULL))!=0){
            return false;
        }
        if(avformat_find_stream_info(pFormatCtx,NULL)<0){
            return false;
        }
        int videoindex = -1;
        for(int i=0; i<pFormatCtx->nb_streams; i++) {
            if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
                videoindex=i;
                break;
            }
        }
        if(videoindex==-1){
            return false;
        }
        pCodecCtx=pFormatCtx->streams[videoindex]->codec;
        pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
        if(pCodec==NULL){
            return false;
        }
        if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
            return false;
        }
        switch (pCodecCtx->codec_id) {
            case AV_CODEC_ID_PNG:
                outResult->imgType = FfmpegLoadImgType_PNG;
                break;
            case AV_CODEC_ID_MJPEG:
                outResult->imgType = FfmpegLoadImgType_JPG;
            default:
                break;
        }
        AVPixelFormat targetFmt = AV_PIX_FMT_YUV420P;
        switch (fmt) {
            case FfmpegLoadImgFmt_RGBA:
                targetFmt = AV_PIX_FMT_RGBA;
                break;
            case FfmpegLoadImgFmt_RGB:
                targetFmt = AV_PIX_FMT_RGB24;
                break;
            case FfmpegLoadImgFmt_GRAY:
                targetFmt = AV_PIX_FMT_GRAY8;
                break;
            case FfmpegLoadImgFmt_NV12:
                targetFmt = AV_PIX_FMT_NV12;
                break;
            case FfmpegLoadImgFmt_UYVY422:
                targetFmt = AV_PIX_FMT_UYVY422;
                break;
                
            default:
                targetFmt = AV_PIX_FMT_YUV420P;
                break;
        }
        pFrame=av_frame_alloc();
        pFrameYUV=av_frame_alloc();
        const int width = pCodecCtx->width;
        const int height = pCodecCtx->height;
        const double ratio = height * 1.0 / width;
        const int targetWidth = width > maxWidth ? maxWidth : width;
        const int targetHeight = width > maxWidth ? (ratio * targetWidth) : height;
        out_buffer=(unsigned char *)calloc(1, av_image_get_buffer_size(targetFmt,  targetWidth, targetHeight, 1));
        av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
                             targetFmt, targetWidth, targetHeight, 1);
        packet=(AVPacket *)av_malloc(sizeof(AVPacket));
        img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                         targetWidth, targetHeight, targetFmt, SWS_BICUBIC, NULL, NULL, NULL);
        
        while(av_read_frame(pFormatCtx, packet)>=0){
            if(packet->stream_index==videoindex){
                ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
                if(ret < 0){
                    return false;
                }
                if(got_picture){
                    sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                              pFrameYUV->data, pFrameYUV->linesize);
                    outResult->width = targetWidth;
                    outResult->height = targetHeight;
                    outResult->data = out_buffer;
                    outResult->imgFmt = fmt;
                }
            }
            av_free_packet(packet);
        }
        av_free(packet);
        sws_freeContext(img_convert_ctx);
        av_frame_free(&pFrameYUV);
        av_frame_free(&pFrame);
        avcodec_close(pCodecCtx);
        avformat_close_input(&pFormatCtx);
        return true;
    }
    
    bool FfmpegUtils::loadAndCacheHttpImage(string httpUrl, string cacheImgAbsolutePath, int maxWidth, FfmpegLoadImgResult* outResult, FfmpegLoadImgFmt fmt) {
        //本地缓存文件可能是损坏的
        bool ret = loadImage(cacheImgAbsolutePath, maxWidth, outResult, fmt);
        if(ret) {
            return true;
        }
        memset(outResult, 0, sizeof(outResult));
        HttpUtils httpUtils;
        ret = httpUtils.cacheHttpFileToLocal(httpUrl, cacheImgAbsolutePath);
        if(!ret) {
            memset(outResult, 0, sizeof(outResult));
            return false;
        }
        return loadImage(cacheImgAbsolutePath, maxWidth, outResult, fmt);
    }
    
    bool FfmpegUtils::cacheHttpImage(string httpUrl, string cacheImgAbsolutePath) {
        AVOutputFormat *ofmt = NULL;
        AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
        AVPacket pkt;
        int ret, i;
        av_register_all();
        const char* in_filename = httpUrl.c_str();
        const char* out_filename = cacheImgAbsolutePath.c_str();
        if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
            fprintf(stderr, "Could not open input file '%s'", in_filename);
            goto end;
        }
        
        if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
            fprintf(stderr, "Failed to retrieve input stream information");
            goto end;
        }
        
        //av_dump_format(ifmt_ctx, 0, in_filename, 0);
        avformat_alloc_output_context2(&ofmt_ctx, NULL, "image2", out_filename);
        if (!ofmt_ctx) {
            fprintf(stderr, "Could not create output context\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        ofmt = ofmt_ctx->oformat;
        
        for (int i = 0; i < ifmt_ctx->nb_streams; i++) {
            AVStream *in_stream = ifmt_ctx->streams[i];
            AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
            if (!out_stream) {
                fprintf(stderr, "Failed allocating output stream\n");
                ret = AVERROR_UNKNOWN;
                goto end;
            }
            
            ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
            if (ret < 0) {
                fprintf(stderr, "Failed to copy context from input to output stream codec context\n");
                goto end;
            }
            out_stream->codec->codec_tag = 0;
            if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
                out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }
        //av_dump_format(ofmt_ctx, 0, out_filename, 1);
        
        if (!(ofmt->flags & AVFMT_NOFILE)) {
            ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
            if (ret < 0) {
                fprintf(stderr, "Could not open output file '%s'", out_filename);
                goto end;
            }
        }
        
        ret = avformat_write_header(ofmt_ctx, NULL);
        if (ret < 0) {
            fprintf(stderr, "Error occurred when opening output file\n");
            goto end;
        }
        
        while (1) {
            AVStream *in_stream, *out_stream;
            
            ret = av_read_frame(ifmt_ctx, &pkt);
            if (ret < 0)
                break;
            
            in_stream  = ifmt_ctx->streams[pkt.stream_index];
            out_stream = ofmt_ctx->streams[pkt.stream_index];
            
            //log_packet(ifmt_ctx, &pkt, "in");
            
            /* copy packet */
            //pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
            //pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
            pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;
            //log_packet(ofmt_ctx, &pkt, "out");
            
            ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
            if (ret < 0) {
                fprintf(stderr, "Error muxing packet\n");
                break;
            }
            av_packet_unref(&pkt);
        }
        
        av_write_trailer(ofmt_ctx);
    end:
        
        avformat_close_input(&ifmt_ctx);
        
        /* close output */
        if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
            avio_closep(&ofmt_ctx->pb);
        avformat_free_context(ofmt_ctx);
        
        if (ret < 0 && ret != AVERROR_EOF) {
            //fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
            return false;
        }
        
        return true;
    }
   
}
