
#include <assert.h>
#include <QFile>
#include "HtcQglRenderer.h"

#include "HtcShaders.h"
#include "HtcVertexBufferArray.h"

#define NEAR_CLIP 0.1f
#define FAR_CLIP 10000.0f

static const GLfloat htc_kColorConversion709[3][3] = {
	1.164f, 1.164f, 1.164f,
	0.0f, -0.213f, 2.112f,
	1.793f, -0.533f, 0.0f,
};

HtcQglRenderer::HtcQglRenderer() :
m_hmd_(0), 
m_vertCount_(0),
m_eyeWidth_(0), 
m_eyeHeight_(0), 
m_leftBuffer_(0), 
m_rightBuffer_(0),
is_close_flag_(false),
tex_updated_(false),
is_inited_(false)
{
	memset(&texture_overlay_, 0, sizeof(video_data));
	gl_window_ = new GLView();
}

HtcQglRenderer::~HtcQglRenderer()
{
	close();
}

bool HtcQglRenderer::open()
{
	if (!is_inited_)
	{
		// Loading the SteamVR Runtime
		if (!initStreamVR()){
			return false;
		}

		if (rendering_thread_ != NULL && rendering_thread_->joinable())
		{
			rendering_thread_->join();
		}
		rendering_thread_.reset(new boost::thread(&HtcQglRenderer::renderingLoopFunc, this));

		thread_run_flag_ = true;

		is_inited_ = true;
	}

	return true;
}

void HtcQglRenderer::SetMainWindow(MainWindow* main_window)
{
    main_window_ = main_window;
}

int HtcQglRenderer::setTextureData(video_data& overlay)
{
	boost::lock_guard<boost::mutex> lock(tex_mtx_);
    int width  = overlay.width;
    int height = overlay.height;
    int lineSize[3];
    lineSize[0] = overlay.linesize[0];
    lineSize[1] = overlay.linesize[1];
    lineSize[2] = overlay.linesize[2];

    int pixelNum = width * height;

    if (texture_overlay_.width != width &&  texture_overlay_.height != height)
	{
        texture_overlay_.width  = width;
        texture_overlay_.height = height;
        texture_overlay_.timestamp = overlay.timestamp;
		texture_overlay_.data[0] = (unsigned char *)malloc(pixelNum * sizeof(unsigned char));
		texture_overlay_.data[1] = (unsigned char *)malloc(pixelNum / 4 * sizeof(unsigned char));
		texture_overlay_.data[2] = (unsigned char *)malloc(pixelNum / 4 * sizeof(unsigned char));

        texture_overlay_.linesize[0] = width;
        texture_overlay_.linesize[1] = width / 2;
        texture_overlay_.linesize[2] = width / 2;
	}

    if (lineSize[0] != width)
    {
        unsigned char *frameY = texture_overlay_.data[0];
        unsigned char *frameY_ = overlay.data[0];

        for (int i = 0; i <= height - 1; i++)
        {
            memcpy(frameY, frameY_, width * sizeof(unsigned char));

            frameY  += width;
            frameY_ += lineSize[0];
        }
    }
    else
    {
        memcpy(texture_overlay_.data[0], overlay.data[0], pixelNum * sizeof(unsigned char));
    }
    
    if (lineSize[1] != width / 2)
    {
        unsigned char *frameU = texture_overlay_.data[1];
        unsigned char *frameU_ = overlay.data[1];

        for (int i = 0; i <= height / 2 - 1; i++)
        {
            memcpy(frameU, frameU_, width / 2 * sizeof(unsigned char));

            frameU  += width / 2;
            frameU_ += lineSize[1];
        }
    }
    else
    {
        memcpy(texture_overlay_.data[1], overlay.data[1], pixelNum / 4 * sizeof(unsigned char));
    }
    
    if (lineSize[2] != width / 2)
    {
        unsigned char *frameU = texture_overlay_.data[2];
        unsigned char *frameU_ = overlay.data[2];

        for (int i = 0; i <= height / 2 - 1; i++)
        {
            memcpy(frameU, frameU_, width / 2 * sizeof(unsigned char));

            frameU  += width / 2;
            frameU_ += lineSize[2];
        }
    }
    else
    {
        memcpy(texture_overlay_.data[2], overlay.data[2], pixelNum / 4 * sizeof(unsigned char));
    }
	tex_updated_ = true;
	
	return 0;
}

int HtcQglRenderer::setRgbTexture(QImage overlay)
{
	boost::lock_guard<boost::mutex> lock(tex_mtx_);
	rgb_texture_overlay_ = overlay.copy();
	tex_updated_ = true;
	return 0;
}

void HtcQglRenderer::createTUVTexture(struct video_data *overlay){

	if (overlay == NULL || overlay->data[0] == NULL)
	{
		return;
	}
	const int frameHeight = overlay->height;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (0 == glesrender_.tex.textures[1] && 0 != glesrender_.tex.textures[0])
	{
		glDeleteTextures(1, glesrender_.tex.textures);
	}
	if (0 == glesrender_.tex.textures[1])
	{
		glGenTextures(3, glesrender_.tex.textures);
	}
	GLenum error;
	 error = glGetError();
	Log::Debug("texture id %d,%d,%d error %d \r\n", glesrender_.tex.textures[0], glesrender_.tex.textures[1], glesrender_.tex.textures[2], error);
	
	const uint8_t *pixels[3] = { overlay->data[0], overlay->data[1], overlay->data[2] };
	const int widths[3] = { overlay->linesize[0], overlay->linesize[1], overlay->linesize[2] };
	const int heights[3] = { frameHeight, frameHeight / 2, frameHeight / 2 };

	glesrender_.tex.width = (int)widths[0];
	glesrender_.tex.height = (int)heights[0];

	int maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	for (int i = 0; i < 3; ++i) {

		glBindTexture(GL_TEXTURE_2D, glesrender_.tex.textures[i]);

		error = glGetError();
		Log::Error("GL Error: glBindTexture %d,maxTextureSize %d\r\n", error, maxTextureSize);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, (int)widths[i], (int)heights[i], 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels[i]);

	
		error = glGetError();
		Log::Error("GL Error: glTexImage2D %d, GL_INVALID_VALUE %d \r\n", error, GL_INVALID_VALUE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}

void HtcQglRenderer::createRGBTexture(QImage *overlay)
{
	if (overlay == NULL || overlay->bits() == NULL)
	{
		return;
	}

	assert(overlay->bits());

	int channel = 4;
	int width = overlay->width();
	int height = overlay->height();

	//QImage black_texture;
	//black_texture = QImage(width, height, QImage::Format_RGBA8888);
	//black_texture.fill(QColor(240, 240, 240));

	void *data = overlay->bits();

	glesrender_.tex.width = width;
	glesrender_.tex.height = height;
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (glesrender_.tex.textures[0] == 0) {
		glGenTextures(1, glesrender_.tex.textures);
	}

	glBindTexture(GL_TEXTURE_2D, glesrender_.tex.textures[0]);
	Log::Debug("width = %d, height = %d, data len = %d, correct length = %d", width, height, sizeof(data), 4 * width * height);
	//Qt_checkGLError();
	
	//指定纹理图像
	if (channel == 2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_SHORT_5_6_5, data);
	}
	else if (channel == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	}
	else if (channel == 4){
		Log::Debug("GL Error: glTexImage2D 1");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		Log::Debug("GL Error: glTexImage2D 2");
		//Qt_checkGLError(); 
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glDisable(GL_TEXTURE_2D);
}

void HtcQglRenderer::updateTexture()
{
	if (tex_updated_)
    {
		{
			boost::lock_guard<boost::mutex> lock(tex_mtx_);
			
			createTUVTexture(&texture_overlay_);

			tex_updated_ = false;
		}		
	}
}

void HtcQglRenderer::updateRGBTexture()
{
	if (tex_updated_)
	{
		{
			boost::lock_guard<boost::mutex> lock(tex_mtx_);

			createRGBTexture(&rgb_texture_overlay_);

			tex_updated_ = false;
		}
	}
}

void HtcQglRenderer::close()
{
	if (thread_run_flag_)
	{
		thread_run_flag_ = false;
	}

	if (rendering_thread_ != NULL && rendering_thread_->joinable())
	{
		rendering_thread_->join();
	}


	if (is_close_flag_ == false)
	{
		if (m_hmd_)
		{
			//clearGL();
			vr::VR_Shutdown();
			m_hmd_ = 0;
		}

		for (int i = 0; i < 8; i++)
		{
			if (texture_overlay_.data[i] != NULL)
			{
				free(texture_overlay_.data[i]);
			}
		}
		is_close_flag_ = true;
	}

	is_inited_ = false;
}

// QImage HtcQglRenderer::SetImage()
// {
// 	return m_resolveBuffer_->toImage(QImage::Format_ARGB32);
// }

void HtcQglRenderer::renderingLoopFunc()
{
    initGL();
	while (thread_run_flag_)
	{
        if (1/*main_window_->is_updateTexture_*/)
        {
            assert(m_hmd_);
            updatePoses();
            //updateRGBTexture();		
            updateTexture();
            renderScene();
        }
	}
	clearGL();
}

void HtcQglRenderer::initGL()
{
	surface_format_ = new QSurfaceFormat();
	surface_format_->setMajorVersion(2);
	surface_format_->setMinorVersion(0);

	m_context = new QOpenGLContext();
	m_context->setFormat(*surface_format_);
	m_context->create();

	assert(m_context->isValid());

	m_offscreenSurface_ = new QOffscreenSurface();
	m_offscreenSurface_->setFormat(*surface_format_);
	m_offscreenSurface_->create();

	assert(m_offscreenSurface_->isValid());

	m_context->makeCurrent(m_offscreenSurface_);

	/////////////Create data buffers////////////////////////////////////
	// get eye matrices获取眼睛矩阵
	m_rightProjection_ = vrMatrixToQt(m_hmd_->GetProjectionMatrix(vr::Eye_Right, NEAR_CLIP, FAR_CLIP, vr::API_OpenGL));
	m_rightPose_ = vrMatrixToQt(m_hmd_->GetEyeToHeadTransform(vr::Eye_Right)).inverted(); //inverted是逆矩阵

	m_leftProjection_ = vrMatrixToQt(m_hmd_->GetProjectionMatrix(vr::Eye_Left, NEAR_CLIP, FAR_CLIP, vr::API_OpenGL));
	m_leftPose_ = vrMatrixToQt(m_hmd_->GetEyeToHeadTransform(vr::Eye_Left)).inverted();
	
	// 设置帧缓冲区的眼睛
	m_hmd_->GetRecommendedRenderTargetSize(&m_eyeWidth_, &m_eyeHeight_);
	
	QOpenGLFramebufferObjectFormat buffFormat;                 //opengl 帧缓冲对象格式
	buffFormat.setAttachment(QOpenGLFramebufferObject::Depth);
	buffFormat.setInternalTextureFormat(GL_RGB);
	buffFormat.setSamples(3);

	m_leftBuffer_ = new QOpenGLFramebufferObject(m_eyeWidth_, m_eyeHeight_, buffFormat);
	m_rightBuffer_ = new QOpenGLFramebufferObject(m_eyeWidth_, m_eyeHeight_, buffFormat);

	QOpenGLFramebufferObjectFormat resolveFormat;
	resolveFormat.setInternalTextureFormat(GL_RGB);
	buffFormat.setSamples(0);

	m_resolveBuffer_ = new QOpenGLFramebufferObject(m_eyeWidth_ * 2, m_eyeHeight_, resolveFormat);

	/////////////officially init opengl 初始化OpenGL函数///////////////////////////////////////////////////////////
	initializeOpenGLFunctions();   

	glEnable(GL_DEPTH_TEST); //开启更新深度缓冲区的功能
	glEnable(GL_TEXTURE_2D); //开启纹理2D

	// compile our shader
	compileShader(m_shader_);//编译着色器

	// build out sample geometry
	m_vao_.create();
	m_vao_.bind();

	std::vector<GLfloat> vecPoints;
	vecPoints.insert(vecPoints.begin(), VertexBufferArray, VertexBufferArray + HTC_VBO_SIZE);       //加载顶点数据
	QVector<GLfloat> points = QVector<GLfloat>::fromStdVector(vecPoints);
	//QVector<GLfloat> points = readObj(":/sphere_radius2_256.obj");         //加载顶点数据
	m_vertCount_ = points.length();

	m_vertexBuffer_.create();
	m_vertexBuffer_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vertexBuffer_.bind();

	m_vertexBuffer_.allocate(points.data(), points.length() * sizeof(GLfloat));

	m_shader_.bind();	

	glesrender_.vertex = m_shader_.attributeLocation("a_Position");
	glesrender_.texCoord = m_shader_.attributeLocation("a_TexCoordinate");
	glesrender_.tex.uniformSamplers[0] = m_shader_.uniformLocation("SamplerY");
	glesrender_.tex.uniformSamplers[1] = m_shader_.uniformLocation("SamplerU");
	glesrender_.tex.uniformSamplers[2] = m_shader_.uniformLocation("SamplerV");
	glesrender_.tex.uniform[0] = m_shader_.uniformLocation("colorConversionMatrix");
	glesrender_.transform = m_shader_.uniformLocation("transform");
	glesrender_.isYuv420Handle = m_shader_.uniformLocation("isYuv420");
}

void HtcQglRenderer::clearGL()
{
	m_vertexBuffer_.destroy();
	m_vao_.destroy();

	if (m_leftBuffer_){
		delete m_leftBuffer_;
	}
	
	if (m_rightBuffer_){
		delete m_rightBuffer_;
	}

	if (m_resolveBuffer_){
		delete m_resolveBuffer_;
	}
	
}

bool HtcQglRenderer::initStreamVR() //初始化VR，打开steamVR软件
{
	vr::EVRInitError error = vr::VRInitError_None;
	m_hmd_ = vr::VR_Init(&error, vr::VRApplication_Scene);

	if (error != vr::VRInitError_None)
	{
		Log::Warn("Failed to init steamVR, error code %d!\n", (int)error);
		m_hmd_ = 0;
		return false;
	}

	if (!vr::VRCompositor())
	{
		Log::Warn("Failed to turn on VRCompositor");
		return false;
	}

	return true;
}

void HtcQglRenderer::renderScene()  //将图片渲染到眼睛上
{
	glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
	glViewport(0 , 0, m_eyeWidth_, m_eyeHeight_);  //放大显示----1，改变后两个参数

	QRect sourceRect(0, 0, m_eyeWidth_, m_eyeHeight_);

	glEnable(GL_MULTISAMPLE);
	m_leftBuffer_->bind();
	renderEye(vr::Eye_Left);
	m_leftBuffer_->release();

	QRect targetLeft(0, 0, m_eyeWidth_, m_eyeHeight_);
	QOpenGLFramebufferObject::blitFramebuffer(m_resolveBuffer_, targetLeft,
		m_leftBuffer_, sourceRect);

	glEnable(GL_MULTISAMPLE);
	m_rightBuffer_->bind();
	renderEye(vr::Eye_Right);
	m_rightBuffer_->release();
	QRect targetRight(m_eyeWidth_, 0, m_eyeWidth_, m_eyeHeight_);
	QOpenGLFramebufferObject::blitFramebuffer(m_resolveBuffer_, targetRight,
		m_rightBuffer_, sourceRect);

	vr::VRTextureBounds_t leftRect = { 0.0f, 0.0f, 0.5f, 1.0f };   
	vr::VRTextureBounds_t rightRect = { 0.5f, 0.0f, 1.0f, 1.0f };
// 	vr::VRTextureBounds_t leftRect = { 0.1f, 0.1f, 0.4f, 0.9f };
// 	vr::VRTextureBounds_t rightRect = { 0.6f, 0.1f, 0.9f, 0.9f };
	vr::Texture_t composite = { (void*)m_resolveBuffer_->texture(), vr::API_OpenGL, vr::ColorSpace_Gamma };

	vr::VRCompositor()->Submit(vr::Eye_Left, &composite, &leftRect);
	vr::VRCompositor()->Submit(vr::Eye_Right, &composite, &rightRect);

	emit SigImage(m_resolveBuffer_->toImage());
	
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// 	glViewport(0, 0, width_, height_);
// 	//glEnable(GL_MULTISAMPLE);//开启多重缓存   
// 	glDisable(GL_MULTISAMPLE);//关闭多重缓存 
// 	renderEye(vr::Eye_Right);             //将图片从VR右眼睛显示在界面上
}

void HtcQglRenderer::updatePoses()
{
	vr::VRCompositor()->WaitGetPoses(m_trackedDevicePose_, vr::k_unMaxTrackedDeviceCount, NULL, 0);
	for (unsigned int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++)
	{ 
		if (m_trackedDevicePose_[i].bPoseIsValid)
		{
			m_matrixDevicePose_[i] = vrMatrixToQt(m_trackedDevicePose_[i].mDeviceToAbsoluteTracking);
		}
	}

	if (m_trackedDevicePose_[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_hmdPose_ = m_matrixDevicePose_[vr::k_unTrackedDeviceIndex_Hmd].inverted();
	}
}

void HtcQglRenderer::renderEye(vr::Hmd_Eye eye)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	m_vao_.bind();
	m_shader_.bind();
	
	m_shader_.setAttributeBuffer(glesrender_.vertex, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
	m_shader_.enableAttributeArray(glesrender_.vertex);

	m_shader_.setAttributeBuffer(glesrender_.texCoord, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));
	m_shader_.enableAttributeArray(glesrender_.texCoord);
	//待定
	if (1/*main_window_->is_updateTexture_*/)
	{
        glesrender_.isyuv420 = 1;
    }
    else
    {
        glesrender_.isyuv420 = 0;
    }
	if (glesrender_.isyuv420 == 1)
	{
		for (int i = 0; i < 3; ++i) 
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, glesrender_.tex.textures[i]);
			m_shader_.setUniformValue(glesrender_.tex.uniformSamplers[i], i);

			GLenum error = glGetError();
			Log::Error("GL Error: HtcQglRenderer::renderEye %d\r\n", error);
		}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, glesrender_.tex.textures[0]);
		m_shader_.setUniformValue(glesrender_.tex.uniformSamplers[0], 0);
	}

	m_shader_.setUniformValue(glesrender_.tex.uniform[0], htc_kColorConversion709);
	m_shader_.setUniformValue(glesrender_.isYuv420Handle, glesrender_.isyuv420);
	m_shader_.setUniformValue(glesrender_.transform, viewProjection(eye));

	glDrawArrays(GL_TRIANGLES, 0, m_vertCount_);

	GLenum error = glGetError();
	Log::Error("GL Error: HtcQglRenderer::renderEye glDrawArrays %d\r\n", error);
}

bool HtcQglRenderer::compileShader(QOpenGLShaderProgram &shader)
{
	bool result = shader.addShaderFromSourceCode(QOpenGLShader::Vertex, VertexShader);
	if (!result)
		qCritical() << shader.log();

	result = shader.addShaderFromSourceCode(QOpenGLShader::Fragment, FragmentShader);
	if (!result)
		qCritical() << shader.log();

	result = shader.link();
	if (!result)
		qCritical() << "Could not link shader program:" << shader.log();

	return result;
}

QMatrix4x4 HtcQglRenderer::vrMatrixToQt(const vr::HmdMatrix34_t &mat)
{
	return QMatrix4x4(
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
		mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
		0.0, 0.0, 0.0, 1.0f
		);
}

QMatrix4x4 HtcQglRenderer::vrMatrixToQt(const vr::HmdMatrix44_t &mat)
{
	return QMatrix4x4(
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
		mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
		mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
		);
}

QMatrix4x4 HtcQglRenderer::viewProjection(vr::Hmd_Eye eye)
{
	QMatrix4x4 s;
	s.scale(1000.0f);

	if (eye == vr::Eye_Left)
		return m_leftProjection_ * m_leftPose_ * m_hmdPose_ * s;
	else
		return m_rightProjection_ * m_rightPose_ * m_hmdPose_ * s;
}

QVector<GLfloat> HtcQglRenderer::readObj(const QString &filename)
{
	QVector<GLfloat> result;

	QFile inputFile(filename);
	if (inputFile.open(QIODevice::ReadOnly))
	{
		QVector<GLfloat> verts, uvs;

		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			QStringList data = line.split(" ");

			if (data[0] == "v")
			{
				verts.append(data[1].toFloat());
				verts.append(data[2].toFloat());
				verts.append(data[3].toFloat());
			}
			else if (data[0] == "vt")
			{
				uvs.append(data[1].toFloat());
				uvs.append(data[2].toFloat());
			}
			else if (data[0] == "f")
			{
				if (data.length() == 5) // quads
				{
					// triangulate in the laziest way possible
					int tris[] = { 0, 1, 2, 0, 2, 3 };
					QStringList row;

					for (int i = 0; i < 6; i++)
					{
						row = data[tris[i] + 1].split("/");
						int v = row[0].toInt() - 1;
						int vt = row[1].toInt() - 1;
						for (int j = 0; j < 3; j++)
						{
							result.append(verts.at(v * 3 + j));
						}
						for (int j = 0; j < 2; j++)
						{
							result.append(uvs.at(vt * 2 + j));
						}
					}
				}
				else
				{
					QStringList row;
					for (int i = 1; i < 4; i++)
					{
						row = data[i].split("/");
						int v = row[0].toInt() - 1;
						int vt = row[1].toInt() - 1;
						for (int j = 0; j < 3; j++)
						{
							result.append(verts.at(v * 3 + j));
						}
						for (int j = 0; j < 2; j++)
						{
							result.append(uvs.at(vt * 2 + j));
						}
					}
				}
			}
		}
	}

	return result;
}