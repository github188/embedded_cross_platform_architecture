/*
*debug.h
*debug management
*调试的时候进行打印
*debug打印可以选择性关闭和开启
*/

#ifndef CRS_DEBUG_H
#define CRS_DEBUG_H

/*
	function : 
		开启打印调试信息			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_on( );

/*
	function : 
		进行调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_dbg(const int8_t* tmplate,...);

/*
	function : 
		关闭调试信息的打印			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_dbg_off( );

#endif 
/* DEBUG_H_ */

