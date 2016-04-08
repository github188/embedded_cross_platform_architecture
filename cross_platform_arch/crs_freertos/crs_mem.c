/*
*crs_mem.c
*	memory management
*	
	内存的创建,删除
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "osi.h"
#include "crs_mem.h"
#include "uart_if.h"
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
/*
	function : 内存分配函数
	input : size_t size
	success-返回所分配size_t大小空间的首地址,单位 byte
	fail-返回NLL
*/

extern void *crs_malloc(size_t size)
{	
    return  mem_Malloc(size);
}
/*
	function : 内存分配函数
	input : size_t nmemb
			  size_t size
	分配size_t个nmemb大小的空间
	success-返回所分配内存的地址
	fail-返回NULL
*/
extern void *crs_calloc(size_t nmemb, size_t size)
{
    char * _pt = mem_Malloc(nmemb * size); 
    if(_pt == NULL){
		return NULL;
    }

    mem_set(_pt,0,nmemb * size);
    return _pt;        
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
    mem_Free(ptr);
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
    mem_copy(dest,(void *)src,n);
    return dest;
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
     mem_set(s, c, n);
     return s;
}
/*
	function : 
			求字符串长度		
	input : 	
			字符串s
	return value : 
		success :	
			返回s的长度,到 '\0'为止
		fail : 	
			返回NULL
*/
extern uint32_t crs_strlen(const char *s)
{
    return strlen(s);
}
/*
	function : 
			将字符串形式表示的数字转化为十进制数		
	input : 
			字符串形式的数值
	return value : 			
		success :
			字符串所表示数值的大小
		fail : 	
			
*/
extern int32_t crs_atoi(const char *s)
{
    return atoi(s);
}
/*
	function : 
					
	input : 
	return value : 
	success :	
	fail : 	
*/
extern int32_t crs_vsnprintf(char *s, uint32_t size, const char *template, va_list ap)
{
    return vsnprintf(s,size,template, ap);
}
/*
	function : 
			格式化打印		
	input : 
			格式化数据
	return value : 
	success :	
	fail : 	
*/
extern void  crs_printf(char *pcFormat,...) 
	{
	int iRet = 0;
#ifndef NOTERM
	char *pcBuff, *pcTemp;
	int iSize = 256;

	va_list list;
	pcBuff = (char*)malloc(iSize);
	if(pcBuff == NULL)
	{
		return ;
	}
	while(1)
	{
		va_start(list,pcFormat);
		iRet = vsnprintf(pcBuff,iSize,pcFormat,list);
		va_end(list);
		if(iRet > -1 && iRet < iSize)
		{
			break;
		}
		else
		{
			iSize*=2;
			if((pcTemp=realloc(pcBuff,iSize))==NULL)
			{ 
				Message("Could not reallocate memory\n\r");
				iRet = -1;
				break;
			}
			else
			{
				pcBuff=pcTemp;
			}
		  
		}
	}
	Message(pcBuff);
	free(pcBuff);  
#endif
}                  
//TODO strlen atoi printf
