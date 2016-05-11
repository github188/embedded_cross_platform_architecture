/*
	常见的操作字符串操作功能
*/

#ifndef _CRS_MEM_H_
#define _CRS_MEM_H_

#include "crs_types.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*
	function : 
					
	args : 
	return value : 
		success :	
		fail : 	
*/
/*
	function : 
			求字符串长度		
	args : 	
			字符串s
	return value : 
		success :	
			返回s的长度,到 '\0'为止
		fail : 	
			返回NULL
*/
extern uint32_t crs_strlen(const int8_t *s);

/*
	function : 
		字符串复制，将src的字符串复制到dest所指向的字符串中			
	args : 
		int8_t *dest : 目的字符串，将被赋值的字符串
		int8_t *src ： 源字符串
	return value : 
		success : 返回dest的地址	
		fail : 	返回NULL
*/
extern int8_t* strcpy(int8_t* dest,const int8_t* src);

/*
	function : 
		字符串复制，将src的前n字节的内容复制到dest中			
	args : 
		int8_t *dest	: 的字符串，将被赋值的字符串
		int8_t *src : 源字符串
		uint32_t n : 需要复制的字符串的长度
	return value : 
		success :	返回dest的地址
		fail : 	返回NULL
*/
extern int8_t* strncpy(int8_t* dest, const int8_t* src, uint32_t n);

/*
	function : 
		比较字符串dest和src的大小，即比较dest和src中字符串各个字节的逐一比较
		
	args : 
		int8_t* dest : 待比较的字符串的指针
		
	return value : 	
		success :	
			dest	>	src, 返回1
			dest	==	src, 返回0
			dest	<	src, 返回-1
		例如“abc” < "abd",strcmp("abc", "abd")时, 返回值为-1
			“abc” == ""abc,strcmp("abc", "abc"), 返回值为0
			“abd” > "adc", strcmp("abd", "abc"), 返回值为1
		fail : 	NULL
*/
extern int32_t strcmp(const int8_t* dest,const int8_t* src);
/*
	function : 
		比较字符串dest和src的前n个字节的大小			
	args : 
		const int8_t * dest ：待比较的字符串
		const int8_t * src ： 待比较的字符串
		size_t n ： 需要比较的字符串的长度
	return value : 		
		success :
			前n个字节中
			dest	>	src, 返回1
			dest	==	src, 返回0
			dest	<	src, 返回-1
		fail : 	返回NULL
*/
extern int32_t strncmp ( const int8_t * dest, const int8_t * src, size_t n );

/*
	function : 
			格式化打印		
	args : 
			格式化数据
	return value : 
		success :	
		fail : 	
*/
extern void  crs_printf(int8_t *args,...) ; 
/*
	function : 
		将可变参数格式化输出到一个字符数组			
	args : 
		int8_t *str [out],把生成的格式化的字符串存放在这里.
		size_t size [in], str可接受的最大字符数[1]  (非字节数，UNICODE一个字符两个字节),防止产生数组越界.
		const int8_t *template [in], 指定输出格式的字符串，它决定了你需要提供的可变参数的类型、个数和顺序。
		va_list ap [in], va_list变量. va:variable-argument:可变参数
	return value : 
		success :返回写入到字符数组str中的字符个数（不包含终止符），最大不超过size
		fail : 	返回负值
*/
extern int32_t crs_vsnprintf(int8_t *s, uint32_t size, const int8_t *template, va_list ap);
/*
	function : 
		将字符串表示的数字转换为int型的数字		
	args : 	
		const int8_t *s ： 字符串形式的数字，如“123”;	
	return value : 
		success :	返回数字表示的整形数
			
		fail : 	返回0
			
*/
extern int32_t crs_atoi(const int8_t *s);

#ifdef __cplusplus
extern "C"
{
#endif
#endif