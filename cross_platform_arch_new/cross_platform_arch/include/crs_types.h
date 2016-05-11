/*
 * crs_types.h
*types management
*类型的宏定义
*/
/**********************************************************
	c语言中数据基本类型有6种
	*char
	*short
	*int
	*float
	*long
	*double
***********************************************************/

#ifndef __CRS_TYPE_H
#define __CRS_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/*boolean*/
#ifndef bool
	typedef unsigned char        	   bool;
#endif

#ifndef BOOL
	typedef unsigned char			   BOOL;
#endif
/*boolean values*/
#ifndef FALSE
	#define FALSE               (0)
#endif
#ifndef TRUE
	#define TRUE                (1)
#endif
#ifndef false
	#define false               (0)
#endif
#ifndef true
	#define true                (1)
#endif

/*signed*/
typedef char                       int8_t;
typedef short                      int16_t;
typedef int                        int32_t;
typedef long long				   int64_t;

/*unsigned*/
typedef unsigned char          	   uint8_t;
typedef unsigned short         	   uint16_t;
typedef unsigned int               uint32_t;
typedef unsigned int 			   size_t;
typedef unsigned long long		   uint64_t;

/* NULL */
#ifndef NULL
#define NULL                ((void *)0)
#endif


#ifdef __cplusplus
}
#endif

#endif