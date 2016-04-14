/*
	�ַ�����������
*/
#include "string.h"
#include "stdio.h"
#include "crs_str.h"
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
extern uint32_t crs_strlen(const char *s)
{
    return strlen(s);
}

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
extern char* crs_strcpy(char* dest,const char* src)
{
	return strcpy(dest, src);
}
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
extern char* crs_strncpy(char* dest, const char* src, uint32_t n)
{
	return strncpy(dest, src, n);
}
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
extern int32_t crs_strcmp(const char* dest,const char* src)
{
	return strcmp(dest, src);
}
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
extern int32_t crs_strncmp ( const char * dest, const char * src, size_t n )
{
	return strncmp(dest, src, n);
}
/*
	function : 
			��ʽ����ӡ		
	args : 
			��ʽ������
	return value : 
		success :	
		fail : 	
*/
extern void  crs_printf(char *args,...)
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
				iRet = -1;
				break;
			}
			else
			{
				pcBuff=pcTemp;
			}
		  
		}
	}
	printf(pcBuff);
	free(pcBuff);  
#endif
}                  
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
extern int32_t crs_vsnprintf(char *s, uint32_t size, const char *template, va_list ap)
{
	return vsprintf(s, size, template, ap);
}
/*
	function : 
		���ַ�����ʾ������ת��Ϊint�͵�����		
	args : 	
		const char *s �� �ַ�����ʽ�����֣��硰123��;	
	return value : 
		success :	�������ֱ�ʾ��������
			
		fail : 	����0
			
*/
extern int32_t crs_atoi(const char *s)
{
    return atoi(s);
}