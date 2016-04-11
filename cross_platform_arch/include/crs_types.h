/*
 * crs_types.h
*types management
*类型的宏定义
*/


#ifndef __CRS_TYPE_H__
#define __CRS_TYPE_H__

#ifdef __LITEOS__
#include <stdint.h>
// TODO
#include <inttypes.h>
#else // 其他平台 #elif defined
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h> // size_t
#endif

// TODO 编译器没有相关定义的需要自定义

#endif /* __CRS_TYPE_H__ */

