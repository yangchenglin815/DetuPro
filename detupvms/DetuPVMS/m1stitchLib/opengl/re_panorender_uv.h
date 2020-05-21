#pragma once

#include <stdio.h>
#include "re_opengl_const.h"

bool pano_initShader(GLES2_Renderer *renderer);

void pano_initPointCoords(GLES2_Renderer *renderer);

void pano_initTexCoords(GLES2_Renderer *renderer);

void pano_draw(GLES2_Renderer *renderer);

ReVector3 pano_getImageXY(GLES2_Renderer *renderer, int x, int y, re_lens len);


