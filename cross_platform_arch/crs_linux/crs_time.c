/*			linux                                                                                                                                                                                                                                                                                                                                                                                                     /*
*time.c
*time management
*时间的管理,计时器使用
*/

#include "crs_types.h"
#include "crs_time.h"

#include <unistd.h>
 /*
	function :

	input :
	return value :
		success :
		fail :
*/
/*
	function :
		获取开机启动时间 单位ms
	input :
	return value :
		success : 返回从开机到目前的绝对时间,get time via ticks
		fail : 	返回-1
*/
extern int64_t crs_uptime()
{
	struct sysinfo s_info;
	if ( -1 == sysinfo( &s_info ) )
	{
		crs_dbg("get uptime failed\r\n");
		return -1;
	}
	return s_info.uptime * 1000;
}

/*
	function :
		睡眠 单位us (1/10^9) second
	input :
		uint32_t microseconds ：所需要睡眠的时间
	return value :
		success : 当前task会让出cpu，在睡眠microseconds后继续运行
		fail :
*/
extern uint32_t crs_usleep(uint32_t micro_seconds)
{
	return usleep( micro_seconds );
}

/*
	function :
		睡眠 单位ms (1/10^6)second
	input :
		uint32_t milliseconds ：所需要睡眠的时间
	return value :
		success : 当前task会让出cpu，在睡眠millisconds后继续运行 return 0
		fail :
*/
extern uint32_t crs_sleep(uint32_t  milliseconds)
{
	usleep( milliseconds * 1000 );
	return 0
}
