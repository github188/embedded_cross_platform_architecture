/*		linux
*debug.c
*debug management
*调试的时候进行打印
*debug打印可以选择性关闭和开启
*/
#include "crs_types.h"
#include "crs_debug.h"
#include "crs_mem.h"

#include <string.h>
#include <stdarg.h>

static bool crs_dbg_flag = 0;
/*
	function : 
		开启打印调试信息			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_on(void)
{
	crs_dbg_flag = 1;
}

/*
	function : 
		进行调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_dbg(const int8_t* tmplate,...)
{
	if( crs_dbg_flag )
	{
		int8_t buf_print[512]={ 0 };
		va_list args;
		int32_t i = 0;
		crs_memset(buf_print, 0, sizeof(buf_print));
		va_start(args, tmplate);
		i = vsnprintf(buf_print, sizeof(buf_print), tmplate, args);
		va_end(args);
		printf("%s", buf_print);
		return i;
	}
}

/*
	function : 
		关闭调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_off(void)
{
	crs_dbg_flag = 0;
}


