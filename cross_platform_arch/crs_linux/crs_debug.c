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
/*
	debug打印可以选择性关闭和开启	
*/

/*
	function : 
		crs_debug_on开启打印调试信息			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_on(void);

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
extern int32_t crs_dbg(const char* tmplate,...);

/*
	function : 
		crs_debug_on关闭调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_off(void);

#endif /* DEBUG_H_ */
