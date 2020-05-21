#ifndef DEBUG_FLAT_RENDER_H
#define DEBUG_FLAT_RENDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "rc_opengl_const.h"

struct DebugFlatRender;

typedef struct DebugFlatRender DebugFlatRender;

DebugFlatRender *debugFlatRender_new();

bool debugFlatRender_initProgram(DebugFlatRender *flatRender);

void debugFlatRender_drawFrame(DebugFlatRender *flatRender);

void debugFlatRender_delete(DebugFlatRender *flatRender);

#ifdef __cplusplus
}
#endif
#endif //DEBUG_FLAT_RENDER_H
