/*
*debug.c
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

#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"

#include "stdio.h"
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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
void crs_dbg_on( )
{
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
int32_t crs_dbg(const int8_t *tmplate, ...)
{
        if( crs_dbg_flag )
        {
			static char buf_print[512]={ 0 };
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
		crs_debug_on关闭调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
void crs_dbg_off( )
{
    crs_dbg_flag = 0;
}

