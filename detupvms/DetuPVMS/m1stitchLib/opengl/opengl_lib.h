#pragma once

#include <mutex>
#include <condition_variable>
#include <thread> 
#include <opencv2/core/core.hpp>

#include "re_opengl.h"

#ifdef WIN32
#include "../stitch_lib_defs.h"
#include "../ZReproject.h"
#else
#include "stitch_lib_defs.h"
#include "ZReproject.h"
#endif


class OPENGL_REPROJECTION
{
public:
    OPENGL_REPROJECTION();
	~OPENGL_REPROJECTION();

	bool GetMasksForOpenGL(const std::vector<PhotoParam>& params,
		                    const cv::Size& srcSize,
		                    const cv::Size& dstSize,
		                    std::vector<cv::Mat>& masks);

    bool reprojectForOpenGL(int i, const cv::Mat& src, PhotoParam params, cv::Size& srcSize,
                            cv::Size& dstSize, cv::Mat& dst);

private:

	void initGLES2_Renderer();
	void getFrameDataFromOpenGL(const cv::Mat&  videomat, cv::Mat& dstmat);
	//void getFrameDataFromOpenGL(const cv::Mat&  videomat, void* cuda_data);
	void getFrameDataAndLock(OPENGL_SOURCE_FRAME *frame);
	bool onRender();
	void getPixelData();

private:
	GLES2_Renderer renderer;

	GLFWwindow* window;
	bool is_close_flag;

    int onRenderOk_;	

	std::mutex lock_;
	std::condition_variable condNonEmpty;

	std::vector<PhotoParam> params_;

	OPENGL_SOURCE_FRAME *g_frame;	

	bool is_have_frame;
	bool is_render_frame;
	bool is_end_frame;

	std::shared_ptr<std::thread> runThread_;
	
	cv::Size srcSize_;
	cv::Size dstSize_;

	cv::Mat g_reproject_pano_mat[RE_MAX_LEN_CAMERA];
	void* g_reproject_pano_cuda[RE_MAX_LEN_CAMERA];

	long long int beg, end;
	double freq, elapsed;

};






