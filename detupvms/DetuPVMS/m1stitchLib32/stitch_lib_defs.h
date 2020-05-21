/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：stitch_lib_defs.h
* 摘    要：算法库相关结构定义文件
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#ifndef _STITCH_LIB_DEFS_H_
#define _STITCH_LIB_DEFS_H_

//内存对齐
#define STL_SIZE_ALIGN(size,align)      (((size)+((align)-1))&(~((align)-1))) //对齐计算
#define STL_SIZE_ALIGN_64(size)         STL_SIZE_ALIGN(size,64)
#define STL_SIZE_ALIGN_128(size)        STL_SIZE_ALIGN(size,128)
#define STL_SIZE_ALIGN_256(size)        STL_SIZE_ALIGN(size,256)
#define STL_SIZE_ALIGN_USED(size)       STL_SIZE_ALIGN_256(size)

// 数学函数
#define STL_MAX(a,b)                    (((a) < (b)) ? (b) : (a))
#define STL_MIN(a,b)                    (((a) > (b)) ? (b) : (a))
#define STL_CLIP(v,minv,maxv)           STL_MIN((maxv),STL_MAX((v),(minv))

#define STL_PI                          (3.14159265358979323846264338327950288)
#define STL_PI_2                        (1.57079632679489661923132169163975144)
#define STL_TODEGRESS(a)                ((a) * 180.0f / STL_PI)
#define STL_TORADIANS(a)                ((a) * STL_PI / 180.0f)

#define STL_FLOAT32_MAX                 (3.40282346638528860e+38)
#define STL_FLOAT32_ZERO                (2.2204e-16)
#define STL_FLOAT32_ZERO_ROOT           (1.4901e-08)

// 数据类型定义
typedef unsigned char      STL_U08;
typedef signed char        STL_S08;
typedef unsigned short     STL_U16;
typedef short              STL_S16;
typedef unsigned int       STL_U32;
typedef int                STL_S32;
typedef long long          STL_S64;
typedef unsigned long long STL_U64;
typedef float              STL_F32;
typedef double             STL_F64;

typedef struct _STL_SIZE
{
    STL_S32 width;
    STL_S32 height;

}STL_SIZE;

typedef struct _STL_FC32
{
    STL_F32  re;
    STL_F32  im;
} STL_FC32;


// 状态码
typedef enum _STL_STATUS
{
    STL_OK               =  0,      // 处理正确

    STL_ERR              = -1,      // 处理错误

    STL_ERR_PROC_TYPE    = -2,      // 处理类型错误

    STL_ERR_IMG_TYPE     = -3,      // 图像类型错误
     
    STL_ERR_IMG_SIZE     = -4,      // 图像宽高错误

    STL_ERR_PTR_NULL     = -5,      // 指针为空错误

    STL_ERR_BAD_ARG      = -6,      // 参数不在合理范围

    STL_ERR_VECTOR_SIZE  = -7,      // vector大小错误

    STL_ERR_GPU_MEM_LACK = -8,      // GPU内存不足

    STL_ERR_CPU_MEM_LACK = -9,      // CPU内存不足

}STL_STATUS;






#endif // _STITCH_LIB_DEFS_H_

