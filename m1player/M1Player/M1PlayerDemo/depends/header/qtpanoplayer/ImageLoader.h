#pragma once
#include "ImageLoadingListener.h"
#include <string>
#include <QMutex> 
#include <QThreadPool>
#include <QNetworkAccessManager>
#include <thread>
#include <memory>

#ifdef _WIN32

#include <windows.h>

inline void os_sleep(int milliseconds) {
	Sleep(milliseconds);
}

#else

#include <time.h>

inline void os_sleep(int milliseconds)
{
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = milliseconds % 1000 * 1000000;
	nanosleep(&ts, NULL);
}

#endif


using namespace std;

namespace DetuPanoPlayer {
    
class ImageLoaderTask;
class ImageLoaderRunnable;

class ImageLoader : public QObject
{
	
public:
	static ImageLoader* getInstance();
	
	void loadImage(string imagePath, ImageLoadingListener* listener);

	void run(ImageLoaderTask imgTask);

    void stopAll();


private:
	ImageLoader();
	~ImageLoader();
	ImageLoader(const ImageLoader&);
	static ImageLoader* instance;
	QMutex* mutex;
	std::shared_ptr<std::thread> imageloader_thread_;
	

	bool isStared = false;
	bool getBytes(const char* filePath, ImageInfo* imageInfo);
	QNetworkAccessManager* netManager;

	
};
}
