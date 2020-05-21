//
//  VtbH264Decoder.cpp
//  M1Decoder
//
//  Created by chao on 2017/11/8.
//  Copyright © 2017年 detu. All rights reserved.
//

#include "VtbH264Decoder.h"
#import "H264Utils.h"
#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>

typedef enum {
    SGFFVideoToolBoxErrorCodeExtradataSize,
    SGFFVideoToolBoxErrorCodeExtradataData,
    SGFFVideoToolBoxErrorCodeCreateFormatDescription,
    SGFFVideoToolBoxErrorCodeCreateSession,
    SGFFVideoToolBoxErrorCodeNotH264,
}SGFFVideoToolBoxErrorCode;

class VtbH264DecoderPrivate {
public:
    H264Utils* h264Utils;
    CVImageBufferRef imageBuffer;
    VTDecompressionSessionRef _vt_session;
    CMFormatDescriptionRef _format_description;
    bool vtSessionToken;
    bool needConvertNALSize3To4;
    bool convert_bytestream;
    bool isWrite;
    int64_t frameIndex;
    AVCodecContext* codecContext;
    AVFrame * tempFrame;
    unsigned char* spsPpsData;
    int identityId;
    long releaseIndex;
    long outputIndex;
public:
    VtbH264DecoderPrivate() {
        this->isWrite = false;
        this->vtSessionToken = false;
        this->_format_description = nil;
        this->_vt_session = nil;
        this->convert_bytestream = false;
        this->h264Utils = [[H264Utils alloc]init];
        this->frameIndex = 0;
        this->spsPpsData = NULL;
        this->identityId = 0;
        this->releaseIndex = 0;
        this->outputIndex = 0;
    }
    
    ~VtbH264DecoderPrivate() {
        
    }
    
    void setCodecContext(AVCodecContext* codecContext) {
        this->codecContext = codecContext;
    }
    
    void setSpsPpsInfo(unsigned char* spsPpsData) {
        this->spsPpsData = spsPpsData;
    }
    
    void setIdentityId(int identityId) {
        this->identityId = identityId;
    }
    
    bool trySetupVTSession() {
        if (!this->vtSessionToken) {
            NSError * error = setupVTSession();
            if (!error) {
                this->vtSessionToken = YES;
                NSLog(@"trySetupVTSession  scuess ");
            }else{
                NSLog(@"trySetupVTSession  failed %d ",[error code]);
            }
        }
        return this->vtSessionToken;
    }
    
    int decodeVideo(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt) {
        tempFrame = picture;
        BOOL setupResult = trySetupVTSession();
        if (!setupResult) return false;
        BOOL result = NO;
        CMBlockBufferRef blockBuffer = NULL;
        OSStatus status = noErr;
        picture->opaque = NULL;
        
        uint8_t * buffer = avpkt->data;
        int bufferSize = avpkt->size;
        if(this->convert_bytestream) {
            unsigned char* outData = NULL;
            int outSize = 0;
            bool ret = [h264Utils annexbToAvcPacket:avpkt->data size:avpkt->size outData:&outData outSize:&outSize];
            if(ret) {
                buffer = outData;
                bufferSize = outSize;
            }
        }
        
        if (this->needConvertNALSize3To4) {

        } else {
            status = CMBlockBufferCreateWithMemoryBlock(NULL, buffer, bufferSize, kCFAllocatorNull, NULL, 0, bufferSize, FALSE, &blockBuffer);
        }
        
        if (status == noErr) {
            CMSampleBufferRef sampleBuffer = NULL;
            status = CMSampleBufferCreate(NULL, blockBuffer, TRUE, 0, 0, this->_format_description, 1, 0, NULL, 0, NULL, &sampleBuffer);
            if (status == noErr) {
                status = VTDecompressionSessionDecodeFrame(this->_vt_session, sampleBuffer, 0, (void*)picture, 0);
                if (status == noErr) {
                    //status = VTDecompressionSessionWaitForAsynchronousFrames(this->_vt_session);
                    result = picture->opaque != NULL;
                } else {
                    result = NO;
                }
            } else {
                result = NO;
            }
            if (sampleBuffer) {
                CFRelease(sampleBuffer);
            }
        } else {
            result = NO;
        }
        if (blockBuffer) {
            CFRelease(blockBuffer);
        }
        if(this->convert_bytestream) {
            av_free(buffer);
        }
        
//        NSLog(@"this is vtb decoder pixel at:%d ,num:%ld, ret:%d", identityId, outputIndex, result);
//        outputIndex += 1;
        *got_picture_ptr = result;
        return result;
    }
    
    static void cf_dict_set_data(CFMutableDictionaryRef dict, CFStringRef key, uint8_t * value, uint64_t length)
    {
        CFDataRef data;
        data = CFDataCreate(NULL, value, (CFIndex)length);
        CFDictionarySetValue(dict, key, data);
        CFRelease(data);
    }
    
    static void cf_dict_set_int32(CFMutableDictionaryRef dict, CFStringRef key, int32_t value)
    {
        CFNumberRef number;
        number = CFNumberCreate(NULL, kCFNumberSInt32Type, &value);
        CFDictionarySetValue(dict, key, number);
        CFRelease(number);
    }
    
    static void cf_dict_set_string(CFMutableDictionaryRef dict, CFStringRef key, const char * value)
    {
        CFStringRef string;
        string = CFStringCreateWithCString(NULL, value, kCFStringEncodingASCII);
        CFDictionarySetValue(dict, key, string);
        CFRelease(string);
    }
    
    static void cf_dict_set_boolean(CFMutableDictionaryRef dict, CFStringRef key, BOOL value)
    {
        CFDictionarySetValue(dict, key, value ? kCFBooleanTrue: kCFBooleanFalse);
    }
    
    static void cf_dict_set_object(CFMutableDictionaryRef dict, CFStringRef key, CFTypeRef *value)
    {
        CFDictionarySetValue(dict, key, value);
    }
    
    static void outputCallback(void * decompressionOutputRefCon, void * sourceFrameRefCon, OSStatus status, VTDecodeInfoFlags infoFlags, CVImageBufferRef imageBuffer, CMTime presentationTimeStamp, CMTime presentationDuration)
    {
        
        VtbH264DecoderPrivate * decoderPrivate = (VtbH264DecoderPrivate *)decompressionOutputRefCon;
        AVFrame* frame = (AVFrame* )sourceFrameRefCon;
        if (status != 0 || imageBuffer == NULL) {
            frame->opaque = NULL;
            return;
        }
        CVPixelBufferRef pixelBuffer = CVPixelBufferRetain(imageBuffer);
        
        AVCodecContext* codecContext = decoderPrivate->codecContext;
        frame->width = codecContext->width;
        frame->height = codecContext->height;
        frame->opaque = pixelBuffer;
        frame->format = AV_PIX_FMT_VIDEOTOOLBOX;
        size_t count = CVPixelBufferGetPlaneCount(pixelBuffer);
        NSLog(@"this is vtb output pixel at:%d ,num:%ld, %x", decoderPrivate->identityId, decoderPrivate->outputIndex, pixelBuffer);
        decoderPrivate->outputIndex += 1;
        for(int i = 0; i < count; i++) {
            frame->linesize[i] = (int)CVPixelBufferGetBytesPerRowOfPlane(pixelBuffer, i);
            CVPixelBufferLockBaseAddress(pixelBuffer, i);
            void * pb = CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, i);
            frame->data[i] = (uint8_t *)pb;
            CVPixelBufferUnlockBaseAddress(pixelBuffer, i);
        }
    }
    
    static CMFormatDescriptionRef CreateFormatDescription(CMVideoCodecType codec_type, int width, int height, const uint8_t * extradata, int extradata_size)
    {
        CMFormatDescriptionRef format_description = NULL;
        OSStatus status;
        
        CFMutableDictionaryRef par = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        CFMutableDictionaryRef atoms = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        CFMutableDictionaryRef extensions = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        
        // CVPixelAspectRatio
        cf_dict_set_int32(par, CFSTR("HorizontalSpacing"), 0);
        cf_dict_set_int32(par, CFSTR("VerticalSpacing"), 0);
        
        // SampleDescriptionExtensionAtoms
        cf_dict_set_data(atoms, CFSTR("avcC"), (uint8_t *)extradata, extradata_size);
        
        // Extensions
        cf_dict_set_string(extensions, CFSTR ("CVImageBufferChromaLocationBottomField"), "left");
        cf_dict_set_string(extensions, CFSTR ("CVImageBufferChromaLocationTopField"), "left");
        cf_dict_set_boolean(extensions, CFSTR("FullRangeVideo"), FALSE);
        cf_dict_set_object(extensions, CFSTR ("CVPixelAspectRatio"), (CFTypeRef *)par);
        cf_dict_set_object(extensions, CFSTR ("SampleDescriptionExtensionAtoms"), (CFTypeRef *)atoms);
        
        status = CMVideoFormatDescriptionCreate(NULL, codec_type, width, height, extensions, &format_description);
        
        CFRelease(extensions);
        CFRelease(atoms);
        CFRelease(par);
        
        if (status != noErr) {
            return NULL;
        }
        return format_description;
    }
    
    
    NSError* setupVTSession()
    {
        NSError * error;
        
        enum AVCodecID codec_id = this->codecContext->codec_id;
        uint8_t * extradata = this->spsPpsData;
        int extradata_size = this->codecContext->extradata_size;
        
        
//        NSString *docFolder = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
//        NSString *outputPath = [docFolder stringByAppendingPathComponent:@"extra1.dat"];
//        FILE* file = fopen([outputPath UTF8String], "wb+");
//        fwrite(extradata, extradata_size, 1, file);
//        fclose(file);

        if (codec_id == AV_CODEC_ID_H264) {
            if (extradata_size < 7 || extradata == NULL) {
                error = [NSError errorWithDomain:@"extradata error" code:SGFFVideoToolBoxErrorCodeExtradataSize userInfo:nil];
                return error;
            }
            if ((extradata[0] == 0 && extradata[1] == 0 && extradata[2] == 0 && extradata[3] == 1) ||
                (extradata[0] == 0 && extradata[1] == 0 && extradata[2] == 1)) {
                bool ret = [h264Utils annexbToAvcExtraSize:&extradata size:&extradata_size];
                if(ret) {
                    this->convert_bytestream = true;
                }
                NSLog(@"annexb to avc:%d", ret);
            }
            
            if (extradata[0] == 1) {
                if (extradata[4] == 0xFE) {
                    extradata[4] = 0xFF;
                    this->needConvertNALSize3To4 = YES;
                }
                this->_format_description = CreateFormatDescription(kCMVideoCodecType_H264, codecContext->width, codecContext->height, extradata, extradata_size);
                if (this->_format_description == NULL) {
                    error = [NSError errorWithDomain:@"create format description error" code:SGFFVideoToolBoxErrorCodeCreateFormatDescription userInfo:nil];
                    return error;
                }
                
                CFMutableDictionaryRef destinationPixelBufferAttributes = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
                cf_dict_set_int32(destinationPixelBufferAttributes, kCVPixelBufferPixelFormatTypeKey, kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange);
                cf_dict_set_int32(destinationPixelBufferAttributes, kCVPixelBufferWidthKey, codecContext->width);
                cf_dict_set_int32(destinationPixelBufferAttributes, kCVPixelBufferHeightKey, codecContext->height);
                
#if SGPLATFORM_TARGET_OS_MAC
                //            cf_dict_set_boolean(destinationPixelBufferAttributes, kCVPixelBufferOpenGLCompatibilityKey, YES);
                //            cf_dict_set_boolean(destinationPixelBufferAttributes, kCVPixelBufferOpenGLTextureCacheCompatibilityKey, YES);
#elif SGPLATFORM_TARGET_OS_IPHONE
              cf_dict_set_boolean(destinationPixelBufferAttributes, kCVPixelBufferOpenGLESCompatibilityKey, YES);
              cf_dict_set_boolean(destinationPixelBufferAttributes, kCVPixelBufferOpenGLESTextureCacheCompatibilityKey, YES);
#endif
                
                cf_dict_set_boolean(destinationPixelBufferAttributes, kCVPixelBufferOpenGLESCompatibilityKey, YES);
                
                VTDecompressionOutputCallbackRecord outputCallbackRecord;
                outputCallbackRecord.decompressionOutputCallback = outputCallback;
                outputCallbackRecord.decompressionOutputRefCon = this;
                
                OSStatus status = VTDecompressionSessionCreate(kCFAllocatorDefault, this->_format_description, NULL, destinationPixelBufferAttributes, &outputCallbackRecord, &this->_vt_session);
                if (status != noErr) {
                    error = [NSError errorWithDomain:@"create session error" code:SGFFVideoToolBoxErrorCodeCreateSession userInfo:nil];
                    return error;
                }
                CFRelease(destinationPixelBufferAttributes);
                return nil;
            } else {
                error = [NSError errorWithDomain:@"deal extradata error" code:SGFFVideoToolBoxErrorCodeExtradataData userInfo:nil];
                return error;
            }
        } else {
            error = [NSError errorWithDomain:@"not h264 error" code:SGFFVideoToolBoxErrorCodeNotH264 userInfo:nil];
            return error;
        }
        
        return error;
    }
    
    void cleanVTSession()
    {
        if (this->_format_description) {
            CFRelease(this->_format_description);
            this->_format_description = NULL;
        }
        if (this->_vt_session) {
            //VTDecompressionSessionWaitForAsynchronousFrames(this->_vt_session);
            VTDecompressionSessionInvalidate(this->_vt_session);
            CFRelease(this->_vt_session);
            this->_vt_session = NULL;
        }
        this->needConvertNALSize3To4 = NO;
        this->vtSessionToken = NO;
        NSLog(@"video toolbox cleanVTSession!");
    }
    
    void unRefFrame(AVFrame *picture) {
        CVPixelBufferRelease((CVBufferRef)picture->opaque);
        NSLog(@"this is vtb pixel release at:%d, num:%ld, %x", this->identityId, releaseIndex, picture->opaque);
        releaseIndex += 1;
    }
    
    void closeDecoder() {
        cleanVTSession();
    }

};

VtbH264Decoder::VtbH264Decoder() {
    decoderPrivate = new VtbH264DecoderPrivate;
}
VtbH264Decoder::~VtbH264Decoder() {
    if(decoderPrivate != NULL) {
        delete decoderPrivate;
        decoderPrivate = NULL;
    }
}

int VtbH264Decoder::InitDecoder(int identityId, unsigned char* spsPpsData, int length, int width, int height) {
    int ret = H264DecoderBase::InitDecoder(identityId, spsPpsData, length, width, height);
    decoderPrivate->setCodecContext(m_codec_ctx);
    decoderPrivate->setSpsPpsInfo(spsPpsData);
    decoderPrivate->setIdentityId(identityId);
    return ret;
}

void VtbH264Decoder::unRefFrame(AVFrame *picture) {
    decoderPrivate->unRefFrame(picture);
}

int VtbH264Decoder::DecodeVideo(AVFrame *picture,int *got_picture_ptr, AVPacket *avpkt) {
    return decoderPrivate->decodeVideo(picture, got_picture_ptr, avpkt);
}

void VtbH264Decoder::CloseDecoder(void) {
    H264DecoderBase::CloseDecoder();
    decoderPrivate->closeDecoder();
}
