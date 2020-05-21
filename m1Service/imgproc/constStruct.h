//��������ض���
#pragma once

#define CAPTURE_PANO_WIDTH	4096
#define CAPTURE_PANO_HEIGHT 2048

#define MASK_WIDTH	2880
#define MASK_HEIGHT 1440

const int CLIENT_VERSION = 2210;

//VR��ͼģ��״̬
typedef enum MapPageState
{
	COMMON_STATE = 0,
	LINK_PATH_STATE = 1,
	CREATE_PATH = 2,
};



//Ŀ�����Ϣ
typedef struct TargetInfo
{
	int  img_id;			//ͼƬ���
	int  target_id;			//ͼƬ���
	int  pos_x;				//����
	int  pos_y;
	int  w;					//���
	int  h;		

	TargetInfo()
	{
		img_id = -1;		//ͼƬ���
		target_id = -1;		//ͼƬ���
		pos_x = -1;			//����
		pos_y = -1;
		w = -1;				//���
		h = -1;
	}

}TargetInfo_t;


