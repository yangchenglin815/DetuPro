#ifndef MATH_SUPPORT_H
#define MATH_SUPPORT_H
#ifdef __cplusplus
extern "C" {
#endif

#if defined(MAC_QT)

#elif defined(__APPLE__)

#elif defined(WIN32)
#define _USE_MATH_DEFINES
#else

#endif

#include <math.h>
#ifdef __cplusplus
}
#endif
#endif //MATH_SUPPORT_H