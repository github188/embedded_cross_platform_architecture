/*
*debug.h
*debug manaement
*调试的时候进行打印
*/

#ifndef CRS_DEBUG_H
#define CRS_DEBUG_H
#include <stdint.h>
/*
	debug打印可以选择性关闭和开启
	crs_debug_on开启打印调试信息
*/
extern void crs_dbg_on(void);

/*
	进行调试信息的打印
*/
extern int32_t crs_dbg(const char* tmplate,...);

/*
	关闭调试信息的打印
*/
extern void crs_dbg_off(void);

#endif /* DEBUG_H_ */
