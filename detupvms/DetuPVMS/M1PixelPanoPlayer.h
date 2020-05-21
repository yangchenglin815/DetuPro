/************************************************
* \file M1PixelPanoPlayer.h
*
* \author HuZhengdong
* \date 20171114
* GL���ſ����࣬�̳��Կ�ƽ̨�� PixelPanoPlayer
************************************************/

#pragma once
#include "QtPanoPlayer/header/qtpanoplayer/QtPanoPlayer.h"
#include "QtPanoPlayer/header/qtpanoplayer/PixelPlugin.h"

namespace DetuPanoPlayer{

	class M1PixelPanoPlayer :public QtPanoPlayer
	{
	public:
		M1PixelPanoPlayer();
		~M1PixelPanoPlayer();

		PixelPlugin* getPixelPlugin() const;
	protected:
		Plugin* configPlugin(PanoramaData panoData, vector<PlayerOption> options);
	private:
		PixelPlugin* mPixelPlugin;
	};
}

