/*
*			linux
*crs_mem.c
*	memory management
*	
	内存的创建,删除
	首先创建一个heap，然后在heap进行动态的分配和回收内存。
*/

#include "crs_types.h"
#include "crs_str.h"

#include <stdlib.h>
#include <string.h>

/*
	function : 
		内存分配函数
	input : size_t size 所分配的内存的大小
	return ：
		success-返回所分配size_t大小空间的首地址,单位 byte
		fail-返回NULL
*/
extern void *crs_malloc(size_t size)
{
	return malloc( size );
}

/*
	function : 
		内存分配函数
	input : 
		size_t nmemb 
		size_t size 分配size_t个nmemb大小的空间
	return :
		success-返回所分配内存的地址
		fail-返回NULL
*/
extern void *crs_calloc( size_t nmemb, size_t size )
{
	return calloc( nmemb, size );
}
/*
	function : 
		内存释放
					
	input : 
		void *ptr--指向一片内存空间的指针
	return value : 无
		success :	
		fail : 	
*/
extern void crs_free(void *p)
{
	 if ( p == NULL )
	 {
	     return;
	 }
	free( p );
}

/*
	function : 
		内存复制,将src中前n个void *格式的内存复制到dest中,如void为char时,即将src中前n个字节的内容复制到dest中					
	input : 
		void *dest : 目的内存地址,可以是字符串名
		const void *src : 源内存地址
		size_t n : 指定的n个void大小的内存
	return value : 	 
		success :	返回dest地址
		fail : 	返回NULL
*/
extern void *crs_memcpy(void *dest, const void *src, size_t n)
{
	return memcpy(dest, src, n);
}
/*
	function : 
		内存比较,比较dest和src的前n个字节的内容		
	input : 
		dest ：待比较的内存的地址
		src : 比较的内存的地址
	return value : 
		当dest	<	src时，返回值	<	0
		当dest	==	src时，返回值	==	0
		当dest	>	src时，返回值	>	0  	
*/
extern uint8_t crs_memcmp(void *dest, void *src, size_t n)
{
	return memcmp(dest, src, n);
}

/*
	function : 
			内存赋值
			将s所指向内存的前n个字节内容赋值为c
	input : 
			void *s : 制定内存的地址
			int32_t c : 所赋值的值
			size_t n : 字节数
	return value : 
		success :	返回指向s的指针
		fail : 	NULL
*/
extern void *crs_memset(void *s, int32_t c, size_t n)
{
	return memset(s, c, n);
}
