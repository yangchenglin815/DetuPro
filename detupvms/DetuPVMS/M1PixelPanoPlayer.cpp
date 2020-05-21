#include "M1PixelPanoPlayer.h"
namespace DetuPanoPlayer
{
	M1PixelPanoPlayer::M1PixelPanoPlayer()
	{
		mPixelPlugin = new PixelPlugin;
	}


	M1PixelPanoPlayer::~M1PixelPanoPlayer()
	{
// 		if (mPixelPlugin != NULL) {
// 			delete mPixelPlugin;
// 			mPixelPlugin = NULL;
// 		}
	}

	DetuPanoPlayer::PixelPlugin* M1PixelPanoPlayer::getPixelPlugin() const
	{
		return mPixelPlugin;
	}

	DetuPanoPlayer::Plugin* M1PixelPanoPlayer::configPlugin(PanoramaData panoData, vector<PlayerOption> options)
	{
		if (panoData.nodeImage.panoDeviceId == PanoDeviceId_SPHERE_DETU_M1) {
			return mPixelPlugin;
		}
		else {
			return QtPanoPlayer::configPlugin(panoData, options);
		}
	}

}

