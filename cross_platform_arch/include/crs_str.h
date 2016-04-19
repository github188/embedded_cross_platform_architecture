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
extern uint32_t crs_strlen(const int8_t *s);

/*
	function : 
		�ַ������ƣ���src���ַ������Ƶ�dest��ָ����ַ�����			
	args : 
		int8_t *dest : Ŀ���ַ�����������ֵ���ַ���
		int8_t *src �� Դ�ַ���
	return value : 
		success : ����dest�ĵ�ַ	
		fail : 	����NULL
*/
extern int8_t* strcpy(int8_t* dest,const int8_t* src);

/*
	function : 
		�ַ������ƣ���src��ǰn�ֽڵ����ݸ��Ƶ�dest��			
	args : 
		int8_t *dest	: ���ַ�����������ֵ���ַ���
		int8_t *src : Դ�ַ���
		uint32_t n : ��Ҫ���Ƶ��ַ����ĳ���
	return value : 
		success :	����dest�ĵ�ַ
		fail : 	����NULL
*/
extern int8_t* strncpy(int8_t* dest, const int8_t* src, uint32_t n);

/*
	function : 
		�Ƚ��ַ���dest��src�Ĵ�С�����Ƚ�dest��src���ַ��������ֽڵ���һ�Ƚ�
		
	args : 
		int8_t* dest : ���Ƚϵ��ַ�����ָ��
		
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
extern int32_t strcmp(const int8_t* dest,const int8_t* src);
/*
	function : 
		�Ƚ��ַ���dest��src��ǰn���ֽڵĴ�С			
	args : 
		const int8_t * dest �����Ƚϵ��ַ���
		const int8_t * src �� ���Ƚϵ��ַ���
		size_t n �� ��Ҫ�Ƚϵ��ַ����ĳ���
	return value : 		
		success :
			ǰn���ֽ���
			dest	>	src, ����1
			dest	==	src, ����0
			dest	<	src, ����-1
		fail : 	����NULL
*/
extern int32_t strncmp ( const int8_t * dest, const int8_t * src, size_t n );

/*
	function : 
			��ʽ����ӡ		
	args : 
			��ʽ������
	return value : 
		success :	
		fail : 	
*/
extern void  crs_printf(int8_t *args,...) ; 
/*
	function : 
		���ɱ������ʽ�������һ���ַ�����			
	args : 
		int8_t *str [out],�����ɵĸ�ʽ�����ַ������������.
		size_t size [in], str�ɽ��ܵ�����ַ���[1]  (���ֽ�����UNICODEһ���ַ������ֽ�),��ֹ��������Խ��.
		const int8_t *template [in], ָ�������ʽ���ַ�����������������Ҫ�ṩ�Ŀɱ���������͡�������˳��
		va_list ap [in], va_list����. va:variable-argument:�ɱ����
	return value : 
		success :����д�뵽�ַ�����str�е��ַ���������������ֹ��������󲻳���size
		fail : 	���ظ�ֵ
*/
extern int32_t crs_vsnprintf(int8_t *s, uint32_t size, const int8_t *template, va_list ap);
/*
	function : 
		���ַ�����ʾ������ת��Ϊint�͵�����		
	args : 	
		const int8_t *s �� �ַ�����ʽ�����֣��硰123��;	
	return value : 
		success :	�������ֱ�ʾ��������
			
		fail : 	����0
			
*/
extern int32_t crs_atoi(const int8_t *s);

#ifdef __cplusplus
extern "C"
{
#endif
#endif