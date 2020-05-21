#ifndef IMAGE_LOADING_LISTENER_H
#define IMAGE_LOADING_LISTENER_H

namespace DetuPanoPlayer {

typedef enum ImageColorFormat {
	ImageColorFormat_RGBA32,
	ImageColorFormat_RGB24,
}ImageColorFormat;

typedef enum ImageLoaderState 
{
	ImageLoaderState_STARTED,
	ImageLoaderState_COMPLETE,
	ImageLoaderState_FAILURED,
	ImageLoaderState_CANCEL,
}ImageLoaderState;

typedef struct ImageInfo {
	unsigned char* bytes;
	long size;
	int width;
	int height;
	ImageColorFormat colorFormat;
}ImageInfo;

class ImageLoadingListener
{

public:
	ImageLoadingListener(){};
	~ImageLoadingListener(){};
	virtual void onImageLoadingStateChanged(const char* imagePath, ImageLoaderState state, ImageInfo* imageInfo) = 0;
};
}
#endif
