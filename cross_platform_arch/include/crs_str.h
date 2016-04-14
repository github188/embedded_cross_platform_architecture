/*
	�����Ĳ����ַ�����������
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
			���ַ�������		
	args : 	
			�ַ���s
	return value : 
		success :	
			����s�ĳ���,�� '\0'Ϊֹ
		fail : 	
			����NULL
*/
extern uint32_t crs_strlen(const char *s);

/*
	function : 
		�ַ������ƣ���src���ַ������Ƶ�dest��ָ����ַ�����			
	args : 
		char *dest : Ŀ���ַ�����������ֵ���ַ���
		char *src �� Դ�ַ���
	return value : 
		success : ����dest�ĵ�ַ	
		fail : 	����NULL
*/
extern char* strcpy(char* dest,const char* src);

/*
	function : 
		�ַ������ƣ���src��ǰn�ֽڵ����ݸ��Ƶ�dest��			
	args : 
		char *dest	: ���ַ�����������ֵ���ַ���
		char *src : Դ�ַ���
		uint32_t n : ��Ҫ���Ƶ��ַ����ĳ���
	return value : 
		success :	����dest�ĵ�ַ
		fail : 	����NULL
*/
extern char* strncpy(char* dest, const char* src, uint32_t n);

/*
	function : 
		�Ƚ��ַ���dest��src�Ĵ�С�����Ƚ�dest��src���ַ��������ֽڵ���һ�Ƚ�
		
	args : 
		char* dest : ���Ƚϵ��ַ�����ָ��
		
	return value : 	
		success :	
			dest	>	src, ����1
			dest	==	src, ����0
			dest	<	src, ����-1
		���硰abc�� < "abd",strcmp("abc", "abd")ʱ, ����ֵΪ-1
			��abc�� == ""abc,strcmp("abc", "abc"), ����ֵΪ0
			��abd�� > "adc", strcmp("abd", "abc"), ����ֵΪ1
		fail : 	NULL
*/
extern int32_t strcmp(const char* dest,const char* src);
/*
	function : 
		�Ƚ��ַ���dest��src��ǰn���ֽڵĴ�С			
	args : 
		const char * dest �����Ƚϵ��ַ���
		const char * src �� ���Ƚϵ��ַ���
		size_t n �� ��Ҫ�Ƚϵ��ַ����ĳ���
	return value : 		
		success :
			ǰn���ֽ���
			dest	>	src, ����1
			dest	==	src, ����0
			dest	<	src, ����-1
		fail : 	����NULL
*/
extern int32_t strncmp ( const char * dest, const char * src, size_t n );

/*
	function : 
			��ʽ����ӡ		
	args : 
			��ʽ������
	return value : 
		success :	
		fail : 	
*/
extern void  crs_printf(char *args,...) ; 
/*
	function : 
		���ɱ������ʽ�������һ���ַ�����			
	args : 
		char *str [out],�����ɵĸ�ʽ�����ַ������������.
		size_t size [in], str�ɽ��ܵ�����ַ���[1]  (���ֽ�����UNICODEһ���ַ������ֽ�),��ֹ��������Խ��.
		const char *template [in], ָ�������ʽ���ַ�����������������Ҫ�ṩ�Ŀɱ���������͡�������˳��
		va_list ap [in], va_list����. va:variable-argument:�ɱ����
	return value : 
		success :����д�뵽�ַ�����str�е��ַ���������������ֹ��������󲻳���size
		fail : 	���ظ�ֵ
*/
extern int32_t crs_vsnprintf(char *s, uint32_t size, const char *template, va_list ap);
/*
	function : 
		���ַ�����ʾ������ת��Ϊint�͵�����		
	args : 	
		const char *s �� �ַ�����ʽ�����֣��硰123��;	
	return value : 
		success :	�������ֱ�ʾ��������
			
		fail : 	����0
			
*/
extern int32_t crs_atoi(const char *s);
#ifdef __cplusplus
extern "C"
{
#endif
#endif