/*
*debug.h
*debug manaement
*调试的时候进行打印
*/
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef CRS_DEBUG_H
#define CRS_DEBUG_H

#include <stdint.h>
#include "stdio.h"
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "uart_if.h"
#include "common.h"
/*
	debug打印可以选择性关闭和开启	
*/
static bool crs_dbg_flag = 0;
/*
	function : 
		crs_debug_on开启打印调试信息			
	input : 
	return value : 
		success :	
		fail : 	
*/
void crs_dbg_on(void) {
    crs_dbg_flag = 1;   
}

/*
	进行调试信息的打印
*/
/*
	function : 
		crs_debug_on打印调试信息			
	input : 格式化信息
	return value : 
		success :	返回打印的字符数
		fail : 	返回0
*/
int32_t crs_dbg(const char *tmplate, ...)
{
	int iRet = 0;
	
	char *pcBuff, *pcTemp;
	int iSize = 256;

	va_list list;
	pcBuff = (char*)malloc(iSize);
	if(pcBuff == NULL)
	{
	  return 0;
	}
	while(1 && crs_dbg_flag)
	{
		va_start(list,tmplate);
		iRet = vsnprintf(pcBuff,iSize,tmplate,list);
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
	Message("\r\n");
	free(pcBuff);                 
	return 0;
}

/*
	function : 
		crs_debug_on关闭调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
void crs_dbg_off(void) {
    crs_dbg_flag = 0;
}
#endif /* DEBUG_H_ */
