#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "ZReproject.h"
#include "patLib/pat_lib.h"
#include "circle/circle_lib.h"
#include "blend/bld_lib.h"
#include "imgproc/imp_lib.h"

using namespace std;

#define CAPTURE_PANO_WIDTH	4096
#define CAPTURE_PANO_HEIGHT 2048

/*
宽
高

输入1
输入2
输入3
输入4

pts路径

输出

*/


void main(int argc ,char *argv[])
{
	STL_S32 i;
	STL_S32 cnt;
	STL_S32 imgNum;
	STL_S32 cudaSts;

	STL_STATUS sts = STL_ERR;
	Size  dstSize;
	Size  srcSize;

	BlendFunction      blend;
	BLD_PROC_TYPE      procType;
	RenderInputYuv     inData;
	RenderOutput       outData;
	BLD_CONFIG         cfg;

	vector<Mat>			rgbSrcCpu;
	vector<Mat>         ySrcCpu;
	vector<Mat>         uSrcCpu;
	vector<Mat>         vSrcCpu;

	STL_S64 bufSize;
	STL_U08 *workBuf;

	// 初始化
	imgNum = 4;
	dstSize.width = CAPTURE_PANO_WIDTH;
	dstSize.height = CAPTURE_PANO_HEIGHT;

	/*
	StitchExe.exe
	736
	1104
	C:/Users/detu123/Desktop/180725141518/180725141518_0.jpg
	C:/Users/detu123/Desktop/180725141518/180725141518_1.jpg
	C:/Users/detu123/Desktop/180725141518/180725141518_2.jpg
	C:/Users/detu123/Desktop/180725141518/180725141518_3.jpg
	C:/Users/detu123/AppData/Local/Pano-VMS/pts/0D5F85/pat.pts
	C:/Users/detu123/Desktop/180725141518/180725141518.jpg
	*/

	srcSize.width = atoi(argv[1]);
	srcSize.height = atoi(argv[2]);

	std::vector<std::string> src_img_path;
	src_img_path.clear();
	src_img_path.resize(0);

	src_img_path.push_back(std::string(argv[3]));
	src_img_path.push_back(std::string(argv[4]));
	src_img_path.push_back(std::string(argv[5]));
	src_img_path.push_back(std::string(argv[6]));

	std::string pts_file_path(argv[7]);

	std::string pano_path(argv[8]);

// 	srcSize.width = 736/*atoi(argv[1])*/;
// 	srcSize.height = 1104/*atoi(argv[2])*/;
// 
// 	std::vector<std::string> src_img_path;
// 	src_img_path.clear();
// 	src_img_path.resize(0);
// 
// 	src_img_path.push_back(std::string("C:/Users/detu123/Desktop/180725141518/180725141518_0.jpg"));
// 	src_img_path.push_back(std::string("C:/Users/detu123/Desktop/180725141518/180725141518_1.jpg"));
// 	src_img_path.push_back(std::string("C:/Users/detu123/Desktop/180725141518/180725141518_2.jpg"));
// 	src_img_path.push_back(std::string("C:/Users/detu123/Desktop/180725141518/180725141518_3.jpg"));
// 
// 	std::string pts_file_path("C:/Users/detu123/AppData/Local/Pano-VMS/pts/0D5F85/pat.pts");
// 
// 	std::string pano_path("C:/Users/detu123/Desktop/180725141518/180725141518.jpg");

	cv::Mat PanoImg(CAPTURE_PANO_HEIGHT, CAPTURE_PANO_WIDTH, CV_8UC3);

	// 配置参数
	cfg.photoPm.clear();
	cfg.photoPm.resize(0);

	loadPhotoParamFromPTS(pts_file_path, cfg.photoPm);
	//分辨率不相同，需要适当缩放
	if (fabs(float(srcSize.width - cfg.photoPm[0].width)) > 2 || fabs(float(srcSize.height - cfg.photoPm[0].height)) > 2)
	{
		for (int i = 0; i < imgNum; i++)
		{
			cfg.photoPm[i].cropX = (STL_S32(cfg.photoPm[i].cropX*1.0f*srcSize.width / cfg.photoPm[i].width + 0.5f));
			cfg.photoPm[i].cropY = (STL_S32(cfg.photoPm[i].cropY*1.0f*srcSize.width / cfg.photoPm[i].width + 0.5f));
			cfg.photoPm[i].cropWidth = (STL_S32(cfg.photoPm[i].cropWidth*1.0f*srcSize.width / cfg.photoPm[i].width + 0.5f));
			cfg.photoPm[i].cropHeight = (STL_S32(cfg.photoPm[i].cropHeight*1.0f*srcSize.width / cfg.photoPm[i].width + 0.5f));
			cfg.photoPm[i].d = cfg.photoPm[i].d*dstSize.width / cfg.photoPm[i].width;
			cfg.photoPm[i].e = cfg.photoPm[i].e*dstSize.width / cfg.photoPm[i].width;
			cfg.photoPm[i].width = srcSize.width;
			cfg.photoPm[i].height = srcSize.height;
		}
	}
	cfg.dstSize = dstSize;
	cfg.srcSize = srcSize;
	cfg.uvType = MULTI_UV_LINEAR;


	//输入
	rgbSrcCpu.clear();
	rgbSrcCpu.resize(4);

	ySrcCpu.clear();
	ySrcCpu.resize(4);

	uSrcCpu.clear();
	uSrcCpu.resize(4);

	vSrcCpu.clear();
	vSrcCpu.resize(4);

	for (int i = 0; i < imgNum; i++)
	{
		rgbSrcCpu[i].create(srcSize, CV_8UC3);
		rgbSrcCpu[i] = imread(src_img_path[i]);

		ySrcCpu[i].create(srcSize, CV_8UC1);
		uSrcCpu[i].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);
		vSrcCpu[i].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);

		IMP_DataConvert_bgr2yuv420(rgbSrcCpu[i].data, srcSize.width, srcSize.height, ySrcCpu[i].data, uSrcCpu[i].data, vSrcCpu[i].data);
	}

	//输入内存
	inData.yImgCpu = ySrcCpu;
	inData.uImgCpu = uSrcCpu;
	inData.vImgCpu = vSrcCpu;

	// 输出内存
	outData.data[0] = (STL_U08 *)malloc(dstSize.width * dstSize.height * sizeof(STL_U08));
	outData.data[1] = (STL_U08 *)malloc(dstSize.width * dstSize.height / 4 * sizeof(STL_U08));
	outData.data[2] = (STL_U08 *)malloc(dstSize.width * dstSize.height / 4 * sizeof(STL_U08));


	//拼接准备
	procType = BLD_CPU_LINEAR;
	sts = blend.BLD_PrepareYuv(procType, cfg);
	if (STL_OK != sts)
	{
		goto PROC_EXIT;
	}

	//拼接
	sts = blend.BLD_ProcessYuv(&inData, procType, cfg, &outData);
	if (STL_OK != sts)
	{

		goto PROC_EXIT;
	}

	//写全景图
	IMP_DataConvert_yuv4202bgr(outData.data[0], outData.data[1], outData.data[2], dstSize.width, dstSize.height, PanoImg.data);
	cv::imwrite(pano_path, PanoImg);

PROC_EXIT:
	blend.BLD_ReleaseMemory();



	if (NULL != outData.data[0])
	{
		free(outData.data[0]);
		outData.data[0] = NULL;
	}
	if (NULL != outData.data[1])
	{
		free(outData.data[1]);
		outData.data[1] = NULL;
	}
	if (NULL != outData.data[2])
	{
		free(outData.data[2]);
		outData.data[2] = NULL;
	}
}