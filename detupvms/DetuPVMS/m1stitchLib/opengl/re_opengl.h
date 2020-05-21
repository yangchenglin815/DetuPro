#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>





#include "re_texture.h"
#include "re_opengl_const.h"
#include "re_matrix4.h"




bool Re_GLES2_Setup(GLES2_Renderer* renderer);


void Re_GLES_SetTexture(GLES2_Renderer* renderer,OPENGL_SOURCE_FRAME *overlay);

void Re_GLES2_Render(GLES2_Renderer* renderer);

void Re_GLES2_Render_createDataFBO(GLES2_Renderer* renderer);


void Re_GLES2_ParserOffset(GLES2_Renderer* renderer,const char* desc);

void Re_GLES2_Distory(GLES2_Renderer* renderer);

