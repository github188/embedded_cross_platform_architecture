/*
*crs_mem.h
*	memory management
*	
	内存的创建,删除
*/
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef _CRS_MEM_H_
#define _CRS_MEM_H_

#ifdef __cplusplus
extern "C"
{
#endif
/*
	function : 内存分配函数
	input : size_t size
	success-返回所分配size_t大小空间的首地址,单位 byte
	fail-返回NLL
*/
extern void *crs_malloc(size_t size);

/*
	function : 内存分配函数
	input : size_t nmemb
			  size_t size
	分配size_t个nmemb大小的空间
	success-返回所分配内存的地址
	fail-返回NULL
*/
extern void *crs_calloc(size_t nmemb, size_t size);

/*
	function : 内存释放
					
	input : void *ptr--指向一片内存空间的指针
	return value : 无
	success :	释放内存空间
	fail : 	未能释放
*/
extern void crs_memfree(void *ptr);

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
extern void *crs_memcpy(void *dest, const void *src, size_t n);
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
extern void *crs_memset(void *s, int c, size_t n);
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
extern uint32_t crs_strlen(const char *s);
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
extern int32_t crs_atoi(const char *s);
/*
	function : 
					
	input : 
	return value : 
	success :	
	fail : 	
*/
extern int32_t crs_vsnprintf(char *s, uint32_t size, const char *template, va_list ap);
/*
	function : 
			格式化打印		
	input : 
			格式化数据
	return value : 
	success :	
	fail : 	
*/
extern void  crs_printf(char *args,...) ;                   
//TODO strlen atoi printf

#ifdef __cplusplus
extern "C"
{
#endif
#endif
