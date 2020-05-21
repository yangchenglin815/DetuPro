#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



// #if defined(__APPLE__)
// #include <OpenGLES/ES2/gl.h>
// #include <OpenGLES/ES2/glext.h>
// #elif defined(WIN32)

#include "glad.h"
#include "glfw3.h"

// #else
// 
// #include <GLES2/gl2.h>
// #include <GLES2/gl2ext.h>
// #include <GLES2/gl2platform.h>
// #endif

#include <opencv2/core/core.hpp>
#include "re_util.h"
#include "re_matrix4.h"
#include "re_vector3.h"
#include "re_vector2.h"
#include "re_glsphereutil.h"

// #include "cuda.h"
// #include "cuda_runtime.h"
// #include "cuda_gl_interop.h"

#include "../stitch_logging.h"
#include "../stitch_lib_defs.h"



#define LOGI(...) ((void)STL_LOG::Debug(   __VA_ARGS__))
#define LOGW(...) ((void)STL_LOG::Warn( __VA_ARGS__))
#define LOGE(...) ((void)STL_LOG::Error(  __VA_ARGS__))

#define STL_OPENGL_MAX_AV_PLANES    (8)
#define RE_MAX_LEN_CAMERA 8

#define RE_COUNTX 160
#define RE_COUNTY 80

#define RE_POINTCOUNT (RE_COUNTX+1)*RE_COUNTY*2
#define RE_POINT3DCOUNT RE_POINTCOUNT * 3
#define RE_POINT2DCOUNT RE_POINTCOUNT * 2

#define RE_GLES_STRINGIZE(x)   #x
#define RE_GLES_STRINGIZE2(x)  RE_GLES_STRINGIZE(x)
#define RE_GLES_STRING(x)      RE_GLES_STRINGIZE2(x)


#define TODEGRESS(a) (a * 180.0f / STL_PI)
#define TORADIANS(a) (a * STL_PI /180.0f)


// #define cutilSafeCall(err)  __cudaSafeCall(err,__FILE__,__LINE__)
// inline void __cudaSafeCall(cudaError err,
// 	const char *file, const int line){
// 	if (cudaSuccess != err) {
// 		STL_LOG::Debug("%s(%i) : cutilSafeCall() Runtime API error : %s.\n",
// 			file, line, cudaGetErrorString(err));
// 	}
// }

typedef bool(*re_findcircle_callback)(void* arg, unsigned char* data, int w, int h, int c, char* desc);

typedef struct _OPENGL_SOURCE_FRAME
{
    uint8_t             *data[STL_OPENGL_MAX_AV_PLANES];
    int                 linesize[STL_OPENGL_MAX_AV_PLANES];

    cv::Mat             framemat;
    uint32_t            width;
    uint32_t            height;
    uint64_t            timestamp;

    int   format;
    float               color_matrix[16];
    bool                full_range;
    float               color_range_min[3];
    float               color_range_max[3];
    bool                flip;

    int					index;
    int64_t             frame_index;
    int64_t					duration;

}OPENGL_SOURCE_FRAME;

typedef struct {

	//畸变校正参数
	float a;
	float b;
	float c;
	float d;
	float e;

	// 图一
	int dr;
	int centerx;
	int centery;
	float yaw; // 对应x轴旋转角度
	float pitch; // 对应y轴旋转角度
	float roll; // 对应z轴旋转角度

	float hd;// 水平平移参数
	float ve;// 垂直平移参数
	float sg;// 水平裁剪参数
	float st;// 垂直裁剪参数

	float degree;

}re_lens;

typedef struct {

	int label;
	int width;
	int height;
	int originwidth;
	int originheight;

	float maskdegree;

	bool isflip;
    bool isVerticalFlip;

	int panow;// 鱼眼对应全景的宽
	int panoh;// 鱼眼对应全景的高

	re_lens lens[RE_MAX_LEN_CAMERA];

	void *re_calback_arg;
	re_findcircle_callback callback;
}re_image;


typedef  struct texture_s{

    GLuint textures[1];
    GLint uniformSamplers[1];    
    int width;
    int height;    
    
}GLES2_Texture;


typedef struct {
    int view_w;
    int view_h;    

	int currentindex;
	int lennum;

    GLfloat plane_points[RE_POINT2DCOUNT]; // (COUNTX+1)*COUNTY*2 * 2

	GLfloat *spriteTexcoords[RE_MAX_LEN_CAMERA];// [RE_POINT2DCOUNT]; // (COUNTX+1)*COUNTY*2 * 2
	GLfloat *spriteTexcoordsExtra[RE_MAX_LEN_CAMERA];
    
    ReMatrix4 projectionMatrix;
    ReMatrix4 modelMatrix;
    ReMatrix4 viewMatrix;
    
    GLuint mProgramHandle;
    GLuint mMVPMatrixHandle;

    GLuint mPositionHandle;
    GLuint mTextureCoordinateHandle;
	GLuint mTextureCoordinate_Extra_Handle;        
    
    GLint _uniformSamplers[3];
    GLint _uniform[1];    

	GLint cx_Handle;
	GLint cy_Handle;
	GLint r_Handle;

	GLint xrate_Handle;
	GLint yrate_Handle;
    
	GLint dre_Handle;

    ReVector3 yaw_rotation;
    ReVector3 pitch_rotation;
    ReVector3 roll_rotation;
    
    ReVector3 sphere_vector;   
    
    gl_sphere_struct spheredata;
    re_image imgdata;
    
    GLES2_Texture texture;    
    
    GLuint movieFramebuffer, movieRenderbuffer;

	bool initialization;

    int onRenderEnd;
    
}GLES2_Renderer;

static inline void Re_GLES2_checkGLError(char* msg){
	GLenum error = glGetError();

	switch (error) {
	case GL_INVALID_ENUM:
		LOGE("GL Error: Enum argument is out of range %s \r\n", msg);
		break;
	case GL_INVALID_VALUE:
		LOGE("GL Error: Numeric value is out of range %s \r\n", msg);
		break;
	case GL_INVALID_OPERATION:
		LOGE("GL Error: Operation illegal in current state %s \r\n", msg);
		break;
	case GL_OUT_OF_MEMORY:
		LOGE("GL Error: Not enough memory to execute command  %s \r\n", msg);
		break;
	case GL_NO_ERROR:

		break;
	default:
		LOGE("Unknown GL Error %d ,%s \r\n", error,msg);
		break;
	}
}

static inline bool re_gles2_compileShader(GLuint *shader,GLenum type,const char *str)
{
    GLint status;
    const GLchar *source;
    
    source = str;
    *shader = glCreateShader(type);
	if (*shader == 0) {
		LOGE("Unable to create shader object");
		return false;
	}
	else if (*shader == GL_INVALID_ENUM) {
		LOGE("Incorrect or unsupported shader type specified");
		return false;
	};


	Re_GLES2_checkGLError("re_gles2_compileShader glCreateShader");
    glShaderSource(*shader, 1, &source, NULL);
	Re_GLES2_checkGLError("re_gles2_compileShader glShaderSource");
    glCompileShader(*shader);
	Re_GLES2_checkGLError("re_gles2_compileShader glCompileShader");

    GLint logLength,sourcelog_len;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
	glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &sourcelog_len);

	Re_GLES2_checkGLError("re_gles2_compileShader glGetShaderiv");
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);

		GLchar *slog = (GLchar *)malloc(sourcelog_len);
		glGetShaderInfoLog(*shader, sourcelog_len, &sourcelog_len, slog);
        
		LOGE("compileShader: shader %d,  log %s  log_length %d, %s sourcelog_len %d \n \n", *shader, log, logLength, slog, sourcelog_len);
        
        free(log);
		free(slog);

    }

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
		LOGE("glGetShaderiv GL_COMPILE_STATUS Failed");
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}

static inline bool re_gles2_linkProgram(GLuint prog)
{
    GLint status;
    
    glLinkProgram(prog);
    

    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        //av_log(NULL, AV_LOG_ERROR, "linkProgram:\n%s", log);
        
        free(log);
    }

    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0){
		LOGE("glGetProgramiv GL_LINK_STATUS Failed");
		return false;
	}
        
    
    return true;
}

static inline bool re_gles2_validateProgram(GLuint prog)
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        //av_log(NULL, AV_LOG_ERROR, "Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return false;
    
    return true;
}

static inline GLuint re_gles2_loadShaders(GLES2_Renderer *renderer,const char* vsh_str ,const char* fsh_str)
{
    GLuint vertShader, fragShader;
    
    // Create shader program
    renderer->mProgramHandle = glCreateProgram();
    
    
    if (!re_gles2_compileShader(&vertShader,GL_VERTEX_SHADER,vsh_str))
    {
        LOGE("Failed to compile vertex shader");
        return 0;
    }
    
    
    if (!re_gles2_compileShader(&fragShader,GL_FRAGMENT_SHADER,fsh_str))
    {
        LOGE("Failed to compile vertex shader");
        return 0;
    }
    
    
    // Attach vertex shader to program
    glAttachShader(renderer->mProgramHandle, vertShader);
    
    // Attach fragment shader to program
    glAttachShader(renderer->mProgramHandle, fragShader);
    
    
    // Link program
    if (!re_gles2_linkProgram(renderer->mProgramHandle))
    {
        LOGE("Failed to link program: %d", renderer->mProgramHandle);
        
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (renderer->mProgramHandle)
        {
            glDeleteProgram(renderer->mProgramHandle);
            renderer->mProgramHandle = 0;
        }
        
        return 0;
    }
    
    
    
    // Release vertex and fragment shaders
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);

	GLint del_status;
	glGetShaderiv(vertShader, GL_DELETE_STATUS, &del_status);
	if (del_status == false)
	{
		LOGE("vertShader delete Failed");
	}

	glGetShaderiv(fragShader, GL_DELETE_STATUS, &del_status);
	if (del_status == false)
	{
		LOGE("fragShader delete Failed");
	}
    
    return renderer->mProgramHandle;
}



