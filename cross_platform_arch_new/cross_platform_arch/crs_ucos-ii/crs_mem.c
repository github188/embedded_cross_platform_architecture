/*
*crs_mem.c
*	memory management
*	
	内存的创建,删除
*/



#include "os_dmem.h"
#include "crs_mem.h"
#include "crs_types.h"
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
/*
	function : 
		内存分配函数
	input : size_t size 所分配的内存的大小
	return ：
		success-返回所分配size_t大小空间的首地址,单位 byte
		fail-返回NULL
*/
extern void* crs_malloc(uint32_t size) {

	void *tmp = OSMMalloc(size);
	if(tmp == NULL)
	{
		dana_dbg("memory create failed\r\n");
		return NULL;
	}
	else
	{
		return tmp;
	}
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
extern void *crs_calloc(size_t nmemb, size_t size)
{
    char * _pt = OSMMalloc(nmemb * size);
    if(_pt == NULL){
		return NULL;
    }
    memset(_pt,0,nmemb * size);
    return _pt;        
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
extern void crs_free(void *ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	OS_FreeMem(ptr);
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
    memcpy(dest,(void *)src,n);
    return dest;
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
			int c : 所赋值的值
			size_t n : 字节数
	return value : 
		success :	返回s的地址
		fail : 	NULL
*/
extern void *crs_memset(void *s, int c, size_t n)
{
     memset(s, c, n);
     return s;
}

