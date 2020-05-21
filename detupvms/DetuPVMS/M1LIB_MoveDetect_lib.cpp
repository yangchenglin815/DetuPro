
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include "M1LIB_MoveDetect_lib.h"

using namespace std;
using namespace cv;

//#define MMD_DEBUG


int MMD_CheckParam(cv::Mat backGoundImg, cv::Mat curImg, std::vector<cv::Point2f> targetPts,
                   MMD_RESULT *result)
{
    if (NULL == backGoundImg.data || NULL == curImg.data)
    {
        return -1;
    }
    if (backGoundImg.cols <= 0 || backGoundImg.rows <= 0)
    {
        return -1;
    }
    if ((curImg.cols != backGoundImg.cols) || (curImg.rows != backGoundImg.rows))
    {
        return -1;
    }

    if (NULL == result)
    {
        return -1;
    }
    
    return 0;
}

void MMD_LumaBlance(Mat &groundImg, Mat &procImg)
{
    int i, j;
    int width,height;
    int data;
    float sum0, sum1;
    float ratio;
    uchar *pImg0, *pImg1;

    width  = groundImg.cols;
    height = procImg.rows;

    // 亮度均匀
    sum0 = 0;
    sum1 = 0;
    for (j = 0; j < height; j++)
    {
        pImg0 = groundImg.ptr<uchar>(j);
        pImg1 = procImg.ptr<uchar>(j);
        for (i = 0; i < width; i++)
        {
            sum0 += pImg0[i];
            sum1 += pImg1[i];
        }
    }

    ratio = sum0 / sum1;

    for (j = 0; j < height; j++)
    {
        pImg1 = procImg.ptr<uchar>(j);
        for (i = 0; i < width; i++)
        {
            data = (uchar)(pImg1[i] * ratio + 0.5f);
            if (data > 255)
            {
                data = 255;
            }
            pImg1[i] = data;
        }
    }
}

void MMD_PreProcess(Mat &groundImg, Mat &procImg)
{
    // 亮度均匀
    MMD_LumaBlance(groundImg, procImg);

    // 
}

/***************************************************************************************************
* 功  能： 检测物体是否有变化
* 参  数：
           backGoundImg：    -I         背景图像
           curImg：          -I         当前检测图像
           targetPts：       -I         需跟踪的目标点
           result：          -O         检测结果
* 返回值： 0： 处理成功
*         -1： 处理失败
* 备  注： 如果输入的目标点为空，会自动检测目标点
***************************************************************************************************/
int MMD_MoveDetect(cv::Mat backGoundImg, cv::Mat curImg, std::vector<cv::Point2f> targetPts,
                   MMD_RESULT *result)
{
    int             i;
    int             detectNum;
    int             oriNum;
    int             difNum;
    int             sts;
    int             difTh;
    float           dist;
    float           distSum;
    Size            winSize;
    Size            subPixWinSize;
    vector<Point2f> curPts;
    vector<uchar>   status;
    vector<float>   err;
    TermCriteria    termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);

    // 参数检测
    sts = MMD_CheckParam(backGoundImg, curImg, targetPts, result);
    if (0 != sts)
    {
        return sts;
    }

    // 一些参数
    difTh = 4;
    winSize.width  = 17;
    winSize.height = 17;
    subPixWinSize.width  = 8;
    subPixWinSize.height = 8;

    oriNum = targetPts.size();
    if (0 == oriNum)
    {
        // 输入必须单通道图像
		cv::Mat grayImg;
		if (backGoundImg.channels() == 3)
		{
			cv::cvtColor(backGoundImg, grayImg, COLOR_BGR2GRAY);
		}
		goodFeaturesToTrack(grayImg, targetPts, 500, 0.01, 10, Mat(), 3, 0, 0.04);
		cornerSubPix(grayImg, targetPts, subPixWinSize, Size(-1, -1), termcrit);


        oriNum = targetPts.size();
    }

#ifdef MMD_DEBUG
    // test
    Mat test1 = backGoundImg;
    Mat test2 = curImg;
    {
        for (i = 0; i < oriNum; i++)
        {
            circle(test1, targetPts[i], 3, Scalar(0, 255, 0), -1, 8);
        }
    }
#endif

    // 预处理
    MMD_PreProcess(backGoundImg, curImg);

    // 关键点跟踪
    calcOpticalFlowPyrLK(backGoundImg, curImg, targetPts, curPts, status, err, winSize, 3, termcrit, 0, 0.001);
    detectNum = 0;
    for (i = 0; i < oriNum; i++)
    {
        if (1 == status[i])
        {
            detectNum++;

#ifdef MMD_DEBUG
            // test
            {
                circle(test2, curPts[i], 3, Scalar(0), -1, 8);
            }
#endif
        }
    }

#ifdef MMD_DEBUG
    // test
    {
        cv::namedWindow("test1", cv::WINDOW_NORMAL);
        cv::imshow("test1", test1);
        namedWindow("test2", WINDOW_NORMAL);
        imshow("test2", test2);
        waitKey(0);
        destroyAllWindows(); 
    }
#endif

    // 是否一致判断
    // 跟踪点的数量要足够多
    if ((detectNum < oriNum * 0.8) || (0 == detectNum))
    {
        *result = MMD_DIFF;
        return 0;
    }

    // 距离不能超过阈值
    difNum  = 0;
    distSum = 0.0f;
    for (i = 0; i < oriNum; i++)
    {
        if (1 == status[i])
        {
            dist = sqrt( (curPts[i].x - targetPts[i].x) * (curPts[i].x - targetPts[i].x)/
                        + (curPts[i].y - targetPts[i].y) * (curPts[i].y - targetPts[i].y) );
            distSum += dist;
            if (dist > difTh)
            {

                difNum++;
            }
        }
    }

    distSum /= detectNum;
    if (difNum > detectNum * 0.3 || distSum > difTh)
    {
        *result = MMD_DIFF;
    }
    else
    {
        *result = MMD_SAME;
    }

    return 0;
}



