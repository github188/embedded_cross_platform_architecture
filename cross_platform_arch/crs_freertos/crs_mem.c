/*			FreeRTOS
*crs_mem.c
*	memory management
*	
	内存的创建,删除
*/

#include "crs_mem.h"
#include "crs_types.h"

#include "stdlib.h"
#include <stdarg.h>
#include "portable.h"
#include <string.h>
/*
	function : 内存分配函数
	input : size_t size
	success-返回所分配size_t大小空间的首地址,单位 byte
	fail-返回NLL
*/

extern void *crs_malloc( size_t size )
{	
    return  pvPortMalloc( size );
}
/*
	function : 内存分配函数
	input : size_t nmemb
			  size_t size
	分配size_t个nmemb大小的空间
	success-返回所分配内存的地址
	fail-返回NULL
*/
extern void *crs_calloc( size_t nmemb, size_t size )
{
    char * p = pvPortMalloc(nmemb * size);
    if(p == NULL)
    {
		return NULL;
    }
    crs_memset( p, 0, nmemb * size);
    return p;
}

/*
	function : 内存释放
					
	input : void *ptr--指向一片内存空间的指针
	return value : 无
	success :	释放内存空间
	fail : 	未能释放
*/
extern void crs_free(void *ptr)
{
    vPortFree(ptr);
}
/*
	function : 内存复制
		将src中前n个void *格式的内存复制到dest中,如void为char时,即将src中前n个字节的内容复制到dest中
					
	input : 
		void *dest : 目的内存地址,可以是字符串名
		const void *src : 源内存地址
		size_t n : 指定的n个void大小的内存
	return value : 	 
		success :	
		fail : 	
*/
extern void *crs_memcpy(void *dest, const void *src, size_t n)
{
    return memcpy(dest,(void *)src,n);
}
/*
	function : 
			内存赋值
			将s所指向内存的前n个字节内容赋值为c
	input : 
			void *s : 制定内存的地址
			 int c : 所赋值的值
			 size_t n : 字节数
	return value : 
		success :	
		fail : 	
*/
extern void *crs_memset(void *s, int c, size_t n)
{
    return memset(s, c, n);
}

