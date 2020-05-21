#include "PanoCalibraterAndCapturer.h"

#include <QProcess>

#include "DetuPVMSIni.h"
#include "logging.hpp"
#include "commonFun.h"

#include "QtPanoPlayer\header\getweight\GetResult.h"

//全局控制器
#include "TcpDataManager.hpp"
#include "MyMd5.h" 

#include "M1LIB_MoveDetect_lib.h"


PanoCalibraterAndCapturer::PanoCalibraterAndCapturer()
	:pano_size_(CAPTURE_PANO_WIDTH, CAPTURE_PANO_HEIGHT)
	,srcSize_(0, 0)
{
}


PanoCalibraterAndCapturer::~PanoCalibraterAndCapturer()
{
}

void PanoCalibraterAndCapturer::setDevice(QString m1_device)
{
	select_m1_device_ = m1_device;
}

void PanoCalibraterAndCapturer::InitRealTimeCapture(m1_video_frame_s** frame_sync)
{
	if (frame_sync[0]->data[0] != NULL&&frame_sync[1]->data[0] != NULL&&frame_sync[2]->data[0] != NULL&&frame_sync[3]->data[0] != NULL)
	{
		switch (frame_sync[0]->format)
		{
		case PIX_FMT_YUV420P:   //坑//软解
		{
			srcSize_.width = frame_sync[0]->w;
			srcSize_.height = frame_sync[0]->h;//人为填充
			//写RGB图片
			cv::Mat sourceImg(srcSize_.height, srcSize_.width, CV_8UC3);

			mutex_capture_.lock();

			//线性拼接用
			ySrcCpu_.resize(4);
			uSrcCpu_.resize(4);
			vSrcCpu_.resize(4);
			for (int j = 0; j < 4; j++)
			{
				ySrcCpu_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
			}

			//截断copy
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < srcSize_.height; i++)
				{
					memcpy(ySrcCpu_[j].data + i*srcSize_.width, frame_sync[j]->data[0] + i*frame_sync[j]->linesize[0], srcSize_.width);
					if (i < srcSize_.height / 2)
					{
						memcpy(uSrcCpu_[j].data + i*srcSize_.width / 2, frame_sync[j]->data[1] + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
						memcpy(vSrcCpu_[j].data + i*srcSize_.width / 2, frame_sync[j]->data[2] + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				IMP_DataConvert_yuv4202bgr(ySrcCpu_[i].data, uSrcCpu_[i].data, vSrcCpu_[i].data, srcSize_.width, srcSize_.height, sourceImg.data);

				QString path1 = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/" + QString::number(i) + ".jpg";
				QString path = TcpDataManagerIns.getCapturePath() + "/" + QString::number(i) + QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".jpg";

				cv::imwrite(path1.toStdString(), sourceImg);
			}
			mutex_capture_.unlock();
		}
		break;
		case PIX_FMT_NV12:
		{
			srcSize_.width = frame_sync[0]->w;
			srcSize_.height = frame_sync[0]->h;//人为填充
			//写RGB图片
			cv::Mat sourceImg(srcSize_, CV_8UC3);


			ySrcCpu_.resize(4);
			uSrcCpu_.resize(4);
			vSrcCpu_.resize(4);

			ySrcCpu_nv12_.resize(4);
			uSrcCpu_nv12_.resize(4);
			vSrcCpu_nv12_.resize(4);

			for (int j = 0; j < 4; j++)
			{
				ySrcCpu_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);

				ySrcCpu_nv12_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_nv12_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_nv12_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
			}


			mutex_capture_.lock();
			for (int i = 0; i < 4; i++)
			{
				//NV12转YUV420
				commonFun::yuv420sp_to_yuv420p(frame_sync[i]->data[0], frame_sync[i]->data[1], ySrcCpu_[i].data, uSrcCpu_[i].data, vSrcCpu_[i].data, srcSize_.width, srcSize_.height);

				//截断
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < srcSize_.height; i++)
					{
						memcpy(ySrcCpu_nv12_[j].data + i*srcSize_.width, ySrcCpu_[j].data + i*frame_sync[j]->linesize[0], srcSize_.width);
						if (i < srcSize_.height / 2)
						{
							memcpy(uSrcCpu_nv12_[j].data + i*srcSize_.width / 2, uSrcCpu_[j].data + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
							memcpy(vSrcCpu_nv12_[j].data + i*srcSize_.width / 2, vSrcCpu_[j].data + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
						}
					}
				}

				//截断copy
				IMP_DataConvert_yuv4202bgr(ySrcCpu_nv12_[i].data, uSrcCpu_nv12_[i].data,
					vSrcCpu_nv12_[i].data, srcSize_.width, srcSize_.height, sourceImg.data);

				QString path1 = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/" + QString::number(i) + ".jpg";
				cv::imwrite(path1.toStdString(), sourceImg);

			}
			mutex_capture_.unlock();
		}
		break;
		default:
			break;
		}
	}
}



int PanoCalibraterAndCapturer::Calibration()
{
	int bufSize;
	int sts;
	int imgNum;
	int cropX, cropY;
	int cropW, cropH;
	int score;

	FILE *fpCase = NULL;
	uchar *workBuf = NULL;
	string ptsFile;

	vector<PAT_CORP_CIRCLE> cropFind;

	QString pts_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/pat.pts";
	algrithom_cfg_.ptsPath = pts_path.toStdString();

	QString output = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_;
	Log::Info("calibration: pat.pts path :%s", output.toLocal8Bit().data());
	Log::Info("calibration: PAT_M1ViewAdjust");

	//客户端标定完成后生成pts校验文件
	QString md5_path = output + "/md5.txt";
	//初始化
	algrithom_cfg_.imgFile.resize(algrithom_cfg_.imgNum);
	cropFind.resize(algrithom_cfg_.imgNum);

	for (int i = 0; i < algrithom_cfg_.imgNum; i++)
	{
		// 算法找圆
		CIRCLE_Process(algrithom_cfg_.srcImg[i], &cropX, &cropY, &cropW, &cropH);
		cropFind[i].cropX = cropX;
		cropFind[i].cropY = cropY;
		cropFind[i].cropWidth = cropW;
		cropFind[i].cropHeight = cropH;
	}
	// 工作内存
	PAT_BufferSize(10, &bufSize);
	workBuf = (uchar *)malloc(bufSize);
	if (NULL == workBuf)
	{
		Log::Info("PAT_BufferSize failed: sts = %d", sizeof(workBuf));
		goto PROC_EXIT;
	}


	sts = PAT_M1Calibration(algrithom_cfg_.srcImg, algrithom_cfg_.imgFile, cropFind, output.toStdString(), algrithom_cfg_.photoPm, &score, workBuf);
	if (sts == STL_ERR)
	{
		Log::Info("PAT_M1Calibration failed: sts = %d", sts);
		goto PROC_EXIT;
	}

	if (NULL != workBuf)
	{
		free(workBuf);
		workBuf = NULL;
	}
	if (NULL != fpCase)
	{
		fclose(fpCase);
		fpCase = NULL;
	}

	if (algrithom_cfg_.score >= DetuPVMSIni::getCalibrationScore())
	{

		Log::Info("calibration optimize_pts: calibration score =%d >= %d", algrithom_cfg_.score, DetuPVMSIni::getCalibrationScore());
		return PLAY_STATUS_CALIBRATION_HIGH_SCORE;

	}
	else
	{
		Log::Info("calibration optimize_pts: calibration score =%d < %d", algrithom_cfg_.score, DetuPVMSIni::getCalibrationScore());

		return PLAY_STATUS_CALIBRATION_LOW_SCORE;

	}


PROC_EXIT:

	if (NULL != workBuf)
	{
		free(workBuf);
		workBuf = NULL;
	}
	if (NULL != fpCase)
	{
		fclose(fpCase);
		fpCase = NULL;
	}
	return PLAY_STATUS_CALIBRATION_ERROR;
}

int PanoCalibraterAndCapturer::OptimizePts()
{
	Log::Info("playModeWgt::optimize_pts() ");
	memset(&algrithom_cfg_, 0, sizeof(algrithom_cfg_));

	//配置參數
	QString pts_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/pat.pts";
	algrithom_cfg_.ptsPath = pts_path.toStdString();

	algrithom_cfg_.width = MASK_WIDTH;
	algrithom_cfg_.height = MASK_HEIGHT;
	algrithom_cfg_.dstSize = cv::Size(MASK_WIDTH, MASK_HEIGHT);
	algrithom_cfg_.blendWidth = 20;
	algrithom_cfg_.imgNum = 4;

	// 读取模板
	loadPhotoParamFromPTS(algrithom_cfg_.ptsPath, algrithom_cfg_.photoPm);
	if (algrithom_cfg_.photoPm.size() == 0)
	{
		Log::Info("pat.pts is wrong, please check");
		return PLAY_STATUS_PTS_WT_PTS_ERROR;
	}

	PAT_BufferSize(algrithom_cfg_.imgNum, &algrithom_cfg_.pat_bufSize);
	algrithom_cfg_.pat_workBuf = (STL_U08 *)malloc(algrithom_cfg_.pat_bufSize);

	//读取RGB图片
	for (int i = 0; i < 4; i++)
	{
		QString path1 = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/" + QString::number(i) + ".jpg";
		cv::Mat temp(srcSize_.height, srcSize_.width, CV_8UC3);
		temp = imread(path1.toStdString());
		algrithom_cfg_.srcImg.push_back(temp);
		algrithom_cfg_.imgFile.push_back(path1.toStdString());
	}


	QString output = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_;
	Log::Info("optimize_pts: pat.pts path :%s", output.toLocal8Bit().data());
	Log::Info("optimize_pts: PAT_M1ViewAdjust");
	int res = PAT_M1ViewAdjust(algrithom_cfg_.srcImg, algrithom_cfg_.imgFile, output.toStdString(), algrithom_cfg_.photoPm, &algrithom_cfg_.score, algrithom_cfg_.pat_workBuf);

	//归一化标定参数
	if (fabs(float(srcSize_.width - algrithom_cfg_.photoPm[0].width)) > 2 || fabs(float(srcSize_.height - algrithom_cfg_.photoPm[0].height)) > 2)
	{
		for (int i = 0; i < algrithom_cfg_.imgNum; i++)
		{
			algrithom_cfg_.photoPm[i].cropX = (STL_S32(algrithom_cfg_.photoPm[i].cropX*1.0f*srcSize_.width / algrithom_cfg_.photoPm[i].width + 0.5f));
			algrithom_cfg_.photoPm[i].cropY = (STL_S32(algrithom_cfg_.photoPm[i].cropY*1.0f*srcSize_.width / algrithom_cfg_.photoPm[i].width + 0.5f));
			algrithom_cfg_.photoPm[i].cropWidth = (STL_S32(algrithom_cfg_.photoPm[i].cropWidth*1.0f*srcSize_.width / algrithom_cfg_.photoPm[i].width + 0.5f));
			algrithom_cfg_.photoPm[i].cropHeight = (STL_S32(algrithom_cfg_.photoPm[i].cropHeight*1.0f*srcSize_.width / algrithom_cfg_.photoPm[i].width + 0.5f));
			algrithom_cfg_.photoPm[i].d = algrithom_cfg_.photoPm[i].d*algrithom_cfg_.width / algrithom_cfg_.photoPm[i].width;
			algrithom_cfg_.photoPm[i].e = algrithom_cfg_.photoPm[i].e*algrithom_cfg_.width / algrithom_cfg_.photoPm[i].width;
			algrithom_cfg_.photoPm[i].width = srcSize_.width;
			algrithom_cfg_.photoPm[i].height = srcSize_.height;
		}
	}

	if (NULL != algrithom_cfg_.fpCfg)
	{
		fclose(algrithom_cfg_.fpCfg);
		algrithom_cfg_.fpCfg = NULL;
	}
	if (NULL != algrithom_cfg_.workBuf)
	{
		free(algrithom_cfg_.workBuf);
		algrithom_cfg_.workBuf = NULL;
	}

	if (algrithom_cfg_.score >= DetuPVMSIni::getCalibrationScore())
	{

		Log::Info("optimize_pts: PAT_M1ViewAdjust score =%d >= %d", algrithom_cfg_.score, DetuPVMSIni::getCalibrationScore());
		return PLAY_STATUS_OPTIMIZE_HIGH_SCORE;

	}
	else
	{
		Log::Info("optimize_pts: PAT_M1ViewAdjust score =%d  < %d", algrithom_cfg_.score, DetuPVMSIni::getCalibrationScore());
		return PLAY_STATUS_OPTIMIZE_LOW_SCORE;
	}
}

int PanoCalibraterAndCapturer::CreatMaskAndWeight()
{
	Mat wt = cv::Mat(algrithom_cfg_.dstSize, CV_8UC1);

	QString pts_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/pat.pts";
	QString md5_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/md5.txt";

	//此处需要从文件读取标定信息
	QString pts_file_path = QDir::homePath() + "/AppData/Local/Pano-VMS/pts/" + select_m1_device_ + "/pat.pts";

	WeightAndMaskData weightdata;
	std::vector<std::string>weight_path;
	weight_path.resize(4);
	weight_path[0] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt0.jpg").toStdString();
	weight_path[1] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt1.jpg").toStdString();
	weight_path[2] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt2.jpg").toStdString();
	weight_path[3] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt3.jpg").toStdString();

	bool result = getResultwithpath(pts_path.toStdString(), weightdata, weight_path);
	if (!result)
	{
		return PLAY_STATUS_PTS_WT_OK;
	}

	//写标定txt
	QString biaoding_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/biaoding.txt";
	FILE* biaoding_txt = fopen(biaoding_path.toLocal8Bit(), "wb+");
	std::string temp = weightdata.biaoding;
	fwrite(temp.c_str(), 1, temp.size(), biaoding_txt);
	fclose(biaoding_txt);


	MyMd5Ins.WriteMd5FromPts(pts_path, md5_path);
	printf("playModeWgt::creat_mask_wt done!\n");

	this->LinearStitch();
	return PLAY_STATUS_PTS_WT_OK;
}

void PanoCalibraterAndCapturer::LinearStitch()
{
	STL_S32 i;
	STL_S32 cnt;
	STL_S32 imgNum;
	STL_S32 width, height;
	STL_S32 cudaSts;
	STL_U08 *yImg = NULL;
	STL_U08 *uImg = NULL;
	STL_U08 *vImg = NULL;
	STL_STATUS sts = STL_ERR;

	BlendFunction      blend;
	BLD_PROC_TYPE      procType;
	RenderInputYuv     inData;
	RenderOutput       outData;
	BLD_CONFIG         cfg;

	Mat					yDst;
	Mat					uDst;
	Mat					vDst;

	LINEAR_CPU_SPEC_YUV spec;
	STL_S64 bufSize;
	STL_U08 *workBuf;

	// 初始化
	imgNum = 4;
	width = algrithom_cfg_.dstSize.width;
	height = algrithom_cfg_.dstSize.height;
	algrithom_cfg_.dstSize.width = width;
	algrithom_cfg_.dstSize.height = height;

	//写全景图
	Mat pano_mat_;
	pano_mat_.create(algrithom_cfg_.dstSize.height, algrithom_cfg_.dstSize.width, CV_8UC3);
	//写RGB图片
	QString path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/pano.jpg";
	// 输出内存
	outData.data[0] = (STL_U08 *)malloc(width * height * sizeof(STL_U08));
	outData.data[1] = (STL_U08 *)malloc(width * height / 4 * sizeof(STL_U08));
	outData.data[2] = (STL_U08 *)malloc(width * height / 4 * sizeof(STL_U08));

	// 配置参数
	cfg.photoPm = algrithom_cfg_.photoPm;
	cfg.dstSize = algrithom_cfg_.dstSize;
	cfg.srcSize = srcSize_;
	cfg.uvType = MULTI_UV_LINEAR;

	// prepare
	procType = BLD_CPU_LINEAR;
	sts = blend.BLD_PrepareYuv(procType, cfg);
	if (STL_OK != sts)
	{
		goto PROC_EXIT;
	}

	inData.yImgCpu = ySrcCpu_;
	inData.uImgCpu = uSrcCpu_;
	inData.vImgCpu = vSrcCpu_;

	sts = blend.BLD_ProcessYuv(&inData, procType, cfg, &outData);
	if (STL_OK != sts)
	{
		goto PROC_EXIT;
	}

	IMP_DataConvert_yuv4202bgr(outData.data[0], outData.data[1], outData.data[2], algrithom_cfg_.dstSize.width, algrithom_cfg_.dstSize.height, pano_mat_.data);
	cv::imwrite(path.toStdString(), pano_mat_);


PROC_EXIT:

	blend.BLD_ReleaseMemory();

	if (NULL != yImg)
	{
		free(yImg);
		yImg = NULL;
	}
	if (NULL != uImg)
	{
		free(uImg);
		uImg = NULL;
	}
	if (NULL != vImg)
	{
		free(vImg);
		vImg = NULL;
	}

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


void PanoCalibraterAndCapturer::RealTimeCapture(m1_video_frame_s** frame_sync)
{
	QString dir_path = TcpDataManagerIns.getCapturePath() + "/" + QDateTime::currentDateTime().toString("yyMMddhhmmss");
	QString pts_path = QDir::homePath() + "/AppData/Local/Pano-VMS/pts/" + select_m1_device_ + "/pat.pts";
	QString pano_path = dir_path + "/" + QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".jpg";
	QDir dir(dir_path);
	if (!dir.exists())
	{
		bool ret = dir.mkdir(dir_path);
	}

	vector<QString> path1;

	if (frame_sync[0]->data[0] != NULL&&frame_sync[1]->data[0] != NULL&&frame_sync[2]->data[0] != NULL&&frame_sync[3]->data[0] != NULL)
	{
		switch (frame_sync[0]->format)
		{
		case PIX_FMT_YUV420P:   //坑//软解
		{
			srcSize_.width = frame_sync[0]->w;
			srcSize_.height = frame_sync[0]->h;//人为填充
			//写RGB图片
			cv::Mat sourceImg(srcSize_.height, srcSize_.width, CV_8UC3);

			mutex_capture_.lock();

			//线性拼接用
			ySrcCpu_.resize(4);
			uSrcCpu_.resize(4);
			vSrcCpu_.resize(4);
			for (int j = 0; j < 4; j++)
			{
				ySrcCpu_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
			}

			//截断copy
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < srcSize_.height; i++)
				{
					memcpy(ySrcCpu_[j].data + i*srcSize_.width, frame_sync[j]->data[0] + i*frame_sync[j]->linesize[0], srcSize_.width);
					if (i < srcSize_.height / 2)
					{
						memcpy(uSrcCpu_[j].data + i*srcSize_.width / 2, frame_sync[j]->data[1] + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
						memcpy(vSrcCpu_[j].data + i*srcSize_.width / 2, frame_sync[j]->data[2] + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				IMP_DataConvert_yuv4202bgr(ySrcCpu_[i].data, uSrcCpu_[i].data, vSrcCpu_[i].data, srcSize_.width, srcSize_.height, sourceImg.data);

				QString temp = dir_path + "/" + QDateTime::currentDateTime().toString("yyMMddhhmmss") + "_" + QString::number(i) + ".jpg";
				path1.push_back(temp);
				cv::imwrite(temp.toStdString(), sourceImg);
			}
			mutex_capture_.unlock();
		}
		break;
		case PIX_FMT_NV12:
		{
			srcSize_.width = frame_sync[0]->w;
			srcSize_.height = frame_sync[0]->h;//人为填充
			//写RGB图片
			cv::Mat sourceImg(srcSize_, CV_8UC3);

			ySrcCpu_.resize(4);
			uSrcCpu_.resize(4);
			vSrcCpu_.resize(4);

			ySrcCpu_nv12_.resize(4);
			uSrcCpu_nv12_.resize(4);
			vSrcCpu_nv12_.resize(4);

			for (int j = 0; j < 4; j++)
			{
				ySrcCpu_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);

				ySrcCpu_nv12_[j].create(srcSize_, CV_8UC1);
				uSrcCpu_nv12_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
				vSrcCpu_nv12_[j].create(srcSize_.height / 2, srcSize_.width / 2, CV_8UC1);
			}


			mutex_capture_.lock();
			for (int i = 0; i < 4; i++)
			{
				//NV12转YUV420
				commonFun::yuv420sp_to_yuv420p(frame_sync[i]->data[0], frame_sync[i]->data[1], ySrcCpu_[i].data, uSrcCpu_[i].data, vSrcCpu_[i].data, srcSize_.width, srcSize_.height);

				//截断
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < srcSize_.height; i++)
					{
						memcpy(ySrcCpu_nv12_[j].data + i*srcSize_.width, ySrcCpu_[j].data + i*frame_sync[j]->linesize[0], srcSize_.width);
						if (i < srcSize_.height / 2)
						{
							memcpy(uSrcCpu_nv12_[j].data + i*srcSize_.width / 2, uSrcCpu_[j].data + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
							memcpy(vSrcCpu_nv12_[j].data + i*srcSize_.width / 2, vSrcCpu_[j].data + i*frame_sync[j]->linesize[0] / 2, srcSize_.width / 2);
						}
					}
				}
				//截断copy
				IMP_DataConvert_yuv4202bgr(ySrcCpu_nv12_[i].data, uSrcCpu_nv12_[i].data,
					vSrcCpu_nv12_[i].data, srcSize_.width, srcSize_.height, sourceImg.data);

				QString temp = dir_path + "/" + QDateTime::currentDateTime().toString("yyMMddhhmmss") + "_" + QString::number(i) + ".jpg";
				path1.push_back(temp);
				cv::imwrite(temp.toStdString(), sourceImg);

			}
			mutex_capture_.unlock();
		}
		break;
		default:
			break;
		}

		//调用exe拼接
		QString exiftool = "StitchExe.exe";
		QString ProjectionType = "-xmp:UsePanoramaViewer=true -xmp:ProjectionType=equirectangular";


		QString write_exif_exeProc = 
			exiftool 
			+ " " + QString::number(srcSize_.width)
			+ " " + QString::number(srcSize_.height)
			+ " " + path1[0] 
			+ " " + path1[1] 
			+ " " + path1[2] 
			+ " " + path1[3] 
			+ " " + pts_path
			+ " " + pano_path;

		Log::Info("stitch argv     %s", write_exif_exeProc.toLocal8Bit().data());
		QProcess::execute(write_exif_exeProc);
	}
}

MMD_RESULT PanoCalibraterAndCapturer::CheckWarningBoard(m1_video_frame_s** frame_sync)
{
	//清空列表
	emit SignalToRFIDUi(200, 100);


	STL_S32 i;
	STL_S32 cnt;
	STL_S32 imgNum;
	STL_S32 cudaSts;
	STL_U08 *yImg = NULL;
	STL_U08 *uImg = NULL;
	STL_U08 *vImg = NULL;
	STL_STATUS sts = STL_ERR;
	Size  srcSize;

	vector<Mat>         ySrcCpu;
	vector<Mat>         uSrcCpu;
	vector<Mat>         vSrcCpu;

	// 初始化
	imgNum = 4;

	srcSize.width = frame_sync[0]->w;
	srcSize.height = frame_sync[0]->h;

	//写RGB图片
	cv::Mat background_img(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);


	vector<Mat>  rgb_img;
	rgb_img.resize(4);
	for (int j = 0; j < imgNum; j++)
	{
		rgb_img[j].create(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);
	}

	//拷贝内存
	ySrcCpu.resize(imgNum);
	uSrcCpu.resize(imgNum);
	vSrcCpu.resize(imgNum);
	for (int j = 0; j < imgNum; j++)
	{
		ySrcCpu[j].create(srcSize, CV_8UC1);
		uSrcCpu[j].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);
		vSrcCpu[j].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);

		rgb_img[j].create(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);
	}


	//截断copy
	for (int j = 0; j < imgNum; j++)
	{
		for (int i = 0; i < srcSize.height; i++)
		{
			memcpy(ySrcCpu[j].data + i*srcSize.width, frame_sync[j]->data[0] + i*frame_sync[j]->linesize[0], srcSize.width);
			if (i < srcSize.height / 2)
			{
				memcpy(uSrcCpu[j].data + i*srcSize.width / 2, frame_sync[j]->data[1] + i*frame_sync[j]->linesize[0] / 2, srcSize.width / 2);
				memcpy(vSrcCpu[j].data + i*srcSize.width / 2, frame_sync[j]->data[2] + i*frame_sync[j]->linesize[0] / 2, srcSize.width / 2);
			}
		}
	}

	//以下需要起线程干

	for (int j = 0; j < imgNum; j++)
	{
		IMP_DataConvert_yuv4202bgr(ySrcCpu[j].data, uSrcCpu[j].data, vSrcCpu[j].data, srcSize.width, srcSize.height, rgb_img[j].data);
	}


	int img_num = 0;
	MMD_RESULT result;
	for (std::vector<TargetInfo>::iterator iter = target_list_.begin(); iter != target_list_.end(); iter++)
	{

		QString path = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1.jpg")
			.arg(QString::number(iter->img_id));
		QString path1 = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1%2.jpg")
			.arg(QString::number(iter->img_id), QString::number(iter->target_id));
		QString path11 = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1%2rect.jpg")
			.arg(QString::number(iter->img_id), QString::number(iter->target_id));


		cv::imwrite(path1.toStdString(), rgb_img[iter->img_id]);

		background_img = imread(path.toStdString());

		//检测
		int difTh;
		cv::Rect roiArea;
		Mat curImg;
		Mat standImg, dectecImg;
		string backGroundImgName, curImgName;
		MMD_RESULT detectRes;
		std::vector<cv::Point2f> targetPts;
		
		roiArea.x = iter->pos_x;
		roiArea.y = iter->pos_y;
		roiArea.width = iter->w;
		roiArea.height = iter->h;

		standImg = background_img(roiArea);
		dectecImg = rgb_img[iter->img_id](roiArea);
		cv::imwrite(path11.toStdString(), dectecImg);

		int res = MMD_MoveDetect(standImg, dectecImg, targetPts, &result);


		if (result == 2)
		{
			//发信号给RFIDDataManager，在发给screen
			connect(this, SIGNAL(SignalToRFIDUi(int, int)), &RFIDDataManagerIns, SIGNAL(SignalToUi(int, int)));

			emit SignalToRFIDUi(200, img_num);
		}

		img_num++;
	}
	return result;
}

void PanoCalibraterAndCapturer::readList(QString list_path)
{
	target_list_.clear();
	target_list_.resize(0);

	QFile file(list_path);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd())
		{
			QString temp = QString(file.readLine());
			TargetInfo temp_info;
			temp_info.img_id = temp.mid(temp.indexOf("imageid=")+8, 1).toInt();
			temp_info.target_id = temp.mid(temp.indexOf("targetid=")+9, 1).toInt();
			temp_info.pos_x = temp.mid(temp.indexOf("pos_x=")+6, 5).toInt();
			temp_info.pos_y = temp.mid(temp.indexOf("pos_y=")+6, 5).toInt();
			temp_info.w = temp.mid(temp.indexOf("w=")+2, 5).toInt();
			temp_info.h = temp.mid(temp.indexOf("h=")+2, 5).toInt();
			target_list_.push_back(temp_info);
		}

		file.close();
	}



}
