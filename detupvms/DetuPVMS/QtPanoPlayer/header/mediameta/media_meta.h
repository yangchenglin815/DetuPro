//
//  MediaMeta.h
//  MediaMetaLib
//
//  Created by chao on 2017/1/5.
//  Copyright © 2017年 detu. All rights reserved.
//
#ifndef MediaMeta_h
#define MediaMeta_h
#define inline __inline

#include <stdio.h>
#include "media_meta_enitity.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * 从文件中获取相机图片或者视频信息
 * @param fileAbsolutePath 文件绝对路径
 * @param cameraMediaInfo 结果数据
 * @return
 */
bool mediaMetaGetCameraMediaInfo(const char *fileAbsolutePath, CameraMediaInfo *cameraMediaInfo);

/**
 * 从标定字符串获取相机图片或者视频信息
 * @param calibration 待校验的标定字符串
 * @return
 */
bool mediaMetaGetCameraMediaInfoByCalibration(const char *calibration, const char *serialNumber,
                                              CameraMediaInfo *cameraMediaInfo);

/**
 * 通过相机id获取鱼眼个数，主要放在播放的时候
 * @param mediaCameraId 相机id
 * @return 资源鱼眼个数
 */
bool mediaMetaGetFishEyeCount(MediaCameraId mediaCameraId);

/**
 * 往视频文件中写入元信息
 * @param srcAbsolutePath 源视频绝对地址
 * @param dstAbsolutePath 目标视频绝对地址
 * @param keys 元数据key集合
 * @param values 元数据value集合
 * @param count 元数据集合个数
 * @return
 */
bool mediaMetaSetVideoMetaData(const char *srcAbsolutePath, const char *dstAbsolutePath,
                               const char **keys, const char **values, int count);

/**
 * 从直播流中获取标定信息
 * @param liveAbsolutePath 直播流地址
 * @param timeOut 预设的超时时间
 * @param outLiveMediaInfo 结果数据
 * @return
 */
bool mediaMetaGetLiveMetaInfo(const char *liveAbsolutePath, int64_t timeOut, LiveMediaInfo *outLiveMediaInfo);

/**
 * 设置图片exif信息，如果srcPictureAbsolutePath和dstPictureAbsolutePath是同一文件，则在该文件中更新exif信息
 * @param srcPictureAbsolutePath 源图片绝对地址
 * @param dstPictureAbsolutePath 目标图片绝对地址
 * @param key exif信息key
 * @param value exif信息value
 */
bool mediaMetaSetPictureExif(const char *srcPictureAbsolutePath, const char *dstPictureAbsolutePath,
                             const char *key, const char *value);

 /**
 * 设置图片exif信息，如果srcPictureAbsolutePath和dstPictureAbsolutePath是同一文件，则在该文件中更新exif信息
 * @param srcPictureAbsolutePath 源图片绝对地址
 * @param dstPictureAbsolutePath 目标图片绝对地址
 * @param key exif信息key
 * @param value exif信息value
 */
bool mediaMetaSetPictureExifs(const char *srcPictureAbsolutePath, const char *dstPictureAbsolutePath,
                             const char **keys, const char **values, int count);

bool mediaMetaGetOneSphereCalibration(unsigned char* imgData, int64_t size);

#endif /* MediaMeta_h */
