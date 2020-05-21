/************************************************
* \file HtcQglRenderer.h
*
* \author HuZhengDong 
* \date 2017 08 24
* 全局htc头盔渲染
************************************************/

#pragma once
#include <QtGui/qopenglfunctions_2_0.h>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLDebugMessage>
#include <QtGui/QOpenGLDebugLogger>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QOpenGLWidget>

#include <QtGui/QOpenGLTexture>
#include <QtGui/QImage>
#include <gl/glu.h>

#include <openvr.h>

#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"

#include "LibGLStitch/qt_gl_def.h"
#include "LibGLStitch/qt_gl_interface.h"

//需要写成单例类，整个客户端只有一个头盔类
#include "UiSingleton.h"

#define  HtcQglRendererIns HtcQglRenderer::Instance()

class MainWindow;

typedef struct HTC_GLES2_Texture
{
	GLuint textures[3];
	GLint uniformSamplers[3];
	GLint uniform[1];

	int width;
	int height;

	HTC_GLES2_Texture(){
		memset(textures, 0, sizeof(GLuint) * 3);
		memset(uniformSamplers, 0, sizeof(GLint) * 3);
		memset(uniform, 0, sizeof(GLint) * 1);
	}

	
}HTC_GLES2_Texture;

typedef struct HTC_GLES2_Renderer
{
	GLuint isYuv420Handle;
	int isyuv420;

	HTC_GLES2_Texture tex;
	GLuint vertex;
	GLuint texCoord;

	GLuint transform;

	HTC_GLES2_Renderer()
	{
		isyuv420 = 1;//默认为RGB
		isYuv420Handle = 1;
	}
}; 

class DetuPVMS;


class HtcQglRenderer : public QObject, protected QOpenGLFunctions_2_0, public CUiSingleton<HtcQglRenderer>
{
	Q_OBJECT
	friend class CUiSingleton<HtcQglRenderer>;

private:
	HtcQglRenderer();

public:
	virtual ~HtcQglRenderer();

	void SetMainWindow(DetuPVMS* main_window);

	bool open();
    int setTextureData(video_data& frame);
	int setRgbTexture(QImage overlay);
	void close();

    void SetMainWindow(MainWindow* main_window);

	QVector<GLfloat> readObj(const QString &filename);
signals:
	void SigImage(const QImage img);

private:
	bool is_close_flag_;
	bool thread_run_flag_;
	boost::shared_ptr<boost::thread> rendering_thread_;
	QOffscreenSurface *m_offscreenSurface_;
	QOpenGLContext *m_context;
	QSurfaceFormat* surface_format_;

private:
	void renderingLoopFunc();
	void initGL();
	void clearGL();
	bool initStreamVR();
	void renderScene();
	void updatePoses();
	void updateTexture();// x
	void updateRGBTexture();
private:
	void renderEye(vr::Hmd_Eye eye);

private:
	bool compileShader(QOpenGLShaderProgram &shader);
	void createTUVTexture(struct video_data *overlay);  //X
	void createRGBTexture(QImage *overlay);
private:
	QMatrix4x4 vrMatrixToQt(const vr::HmdMatrix34_t &mat);
	QMatrix4x4 vrMatrixToQt(const vr::HmdMatrix44_t &mat);
	QMatrix4x4 viewProjection(vr::Hmd_Eye eye);
	
private:
	vr::IVRSystem *m_hmd_;//vr::IVRSystem界面提供显示配置信息,跟踪数据,变形功能,控制器状态,事件和设备属性。OpenVR的主要接口,可以与OpenVR:初始化和检索:VR_Init函数。
	vr::TrackedDevicePose_t m_trackedDevicePose_[vr::k_unMaxTrackedDeviceCount];//跟踪设备构成
	QMatrix4x4 m_matrixDevicePose_[vr::k_unMaxTrackedDeviceCount];//4X4矩阵变量

	QMatrix4x4 m_leftProjection_, m_leftPose_;
	QMatrix4x4 m_rightProjection_, m_rightPose_;
	QMatrix4x4 m_hmdPose_;

	QOpenGLShaderProgram m_shader_;//OpenGL着色器程序
	QOpenGLBuffer m_vertexBuffer_;//缓冲区对象
	QOpenGLVertexArrayObject m_vao_;//OpenGL顶点数组对象

	uint32_t m_eyeWidth_, m_eyeHeight_;
	QOpenGLFramebufferObject *m_leftBuffer_;//左边框架缓冲对象（左眼睛）
	QOpenGLFramebufferObject *m_rightBuffer_;//右边框架缓冲对象
	QOpenGLFramebufferObject *m_resolveBuffer_;
	int m_vertCount_;
private:
	HTC_GLES2_Renderer glesrender_;
	boost::mutex tex_mtx_;
	bool tex_updated_;
	QImage rgb_texture_overlay_;
    MainWindow* main_window_;
private:
	bool is_inited_;
};

