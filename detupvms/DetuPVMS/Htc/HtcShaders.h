#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式

static const char FragmentShader[] = "uniform lowp sampler2D u_Texture; \n"
"varying mediump vec2 v_TexCoordinate; \n"
"uniform bool isYuv420; \n"
"uniform lowp sampler2D SamplerY; \n"
"uniform lowp sampler2D SamplerU; \n"
"uniform lowp sampler2D SamplerV; \n"
"uniform mediump mat3 colorConversionMatrix; \n"
"void main(){\n"
"if (!isYuv420){\n"
"gl_FragColor = texture2D(u_Texture, v_TexCoordinate);\n"
"}\n"
"else{\n"
"mediump vec3 yuv;\n"
"lowp vec3 rgb;\n"
"yuv.x = (texture2D(SamplerY, v_TexCoordinate).r - (16.0 / 255.0));\n"
"yuv.y = (texture2D(SamplerU, v_TexCoordinate).r - 0.5);\n"
"yuv.z = (texture2D(SamplerV, v_TexCoordinate).r - 0.5);\n"
"rgb = colorConversionMatrix * yuv;\n"
"gl_FragColor = vec4(rgb, 1); //texture2D(SamplerY, v_TexCoordinate); \n"
"}}";


static const char VertexShader[] =
"uniform mat4 transform;\n"
"attribute vec3 a_Position;\n"
"attribute vec2 a_TexCoordinate;\n"
"varying vec2 v_TexCoordinate;\n"
"void main()\n"
"{\n"
"	v_TexCoordinate = a_TexCoordinate;\n"
"	gl_Position = transform * vec4(a_Position, 1.0f);\n"
"}\n";

