#ifndef ONENETCOMMON_H
#define ONENETCOMMON_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H


/*
在嵌入式系统中，可通过定义HAVE_ONENET_CONFIG_H并使用onenet_config.h覆盖默认的定义。
*/
#ifdef HAVE_ONENET_CONFIG_H
#include "onenet_config.h"
#endif // HAVE_ONENET_CONFIG_H

#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"

/*
内存分配
*/
#ifndef OneNETMalloc
#define OneNETMalloc malloc
#endif // OneNETMalloc

/*
内存释放
*/
#ifndef OneNETFree
#define OneNETFree free
#endif // OneNETFree

/*
拷贝字符串
*/
#ifndef OneNETStrdup
#define OneNETStrdup strdup
#endif // OneNETStrdup

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


/** \brief Common初始化
 *
 *
 */
void OneNETCommonInit();

/** \brief 判断字符串是否相同
 *
 * \param str1 const char* 字符串1
 * \param str2 const char* 字符串2
 * \return bool 是否相同
 *
 */
bool OneNETStringIsSame(const char * str1,const char * str2);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ONENETCOMMON_H
