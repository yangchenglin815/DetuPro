//解决类型重定义
#pragma once

#define CAPTURE_PANO_WIDTH	4096
#define CAPTURE_PANO_HEIGHT 2048

#define MASK_WIDTH	2880
#define MASK_HEIGHT 1440

const int CLIENT_VERSION = 2210;

//VR地图模块状态
typedef enum MapPageState
{
	COMMON_STATE = 0,
	LINK_PATH_STATE = 1,
	CREATE_PATH = 2,
};



//目标点信息
typedef struct TargetInfo
{
	int  img_id;			//图片序号
	int  target_id;			//图片序号
	int  pos_x;				//坐标
	int  pos_y;
	int  w;					//宽高
	int  h;		

	TargetInfo()
	{
		img_id = -1;		//图片序号
		target_id = -1;		//图片序号
		pos_x = -1;			//坐标
		pos_y = -1;
		w = -1;				//宽高
		h = -1;
	}

}TargetInfo_t;


