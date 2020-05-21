LOCAL_PATH := $(call my-dir)

M1PLAYER_PATH := $(realpath ../../M1Player)

include $(CLEAR_VARS)
LOCAL_MODULE    := IjkFfmpeg
LOCAL_SRC_FILES := other/libs/$(TARGET_ARCH_ABI)/libijkffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := PiliRtmp
LOCAL_SRC_FILES := other/libs/$(TARGET_ARCH_ABI)/libPiliRtmp.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -D__STDC_CONSTANT_MACROS=1
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/other/headers/pilirtmp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/other/headers/
LOCAL_C_INCLUDES += $(M1PLAYER_PATH)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_CFLAGS += -mfloat-abi=soft
endif

LOCAL_SRC_FILES += $(M1PLAYER_PATH)/DataSource.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/CircularQueue.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/FlvParser.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/FfmpegH264Decoder.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/M1Player.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/M1PlayerImp.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/MessageQueue.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/PrivateSource.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/RtmpSource.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/H264DecoderBase.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/DefaultGenerator.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/AudioDecoder.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/AudioGlobal.cpp
LOCAL_SRC_FILES += $(M1PLAYER_PATH)/AudioOutBase.cpp

LOCAL_SRC_FILES += MediaCodecDecoder.cpp
LOCAL_SRC_FILES += M1Decoder.cpp
LOCAL_SRC_FILES += M1RenderDemoJni.cpp
LOCAL_SRC_FILES += android_audiotrack.c
LOCAL_SRC_FILES += android_byte_buffer.c
LOCAL_SRC_FILES += AudioTrackOut.cpp
LOCAL_SRC_FILES += jni_utils.c


LOCAL_MODULE    := M1Player
LOCAL_LDLIBS := -llog -lm -lz
LOCAL_SHARED_LIBRARIES := IjkFfmpeg PiliRtmp
include $(BUILD_SHARED_LIBRARY)
