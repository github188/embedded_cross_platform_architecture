/*
*time management
	linux platform
*时间的管理
*/
#include <time.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include "crs_time.h"
#include "crs_dbg.h"
#include "crs_mem.h"

/*
	function :
		获取开机启动时间 单位us
	input :
	return value :
		success : 返回从开机到目前的绝对时间,get time via ticks
		fail : 	返回0
*/
extern int64_t crs_uptime()
{
	struct sysinfo info;
	
	if (NULL == crs_memset(&info, 0, sizeof(info)) )
	{
		crs_dbg("failed to memset\r\n");
		return 0;
	}
	
	if(sysinfo( &info))
	{
		crs_dbg("failed to get sysinfo\r\n");
		return 0;
	}
	return info.uptime * 1000000;
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
extern uint32_t crs_usleep( uint32_t micro_seconds )
{
	return usleep( micro_seconds );
}
/*
	function :
		睡眠 单位ms (1/10^6)second
	input :
		uint32_t milliseconds ：所需要睡眠的时间
	return value :
		success : 当前task会让出cpu，在睡眠millisconds后继续运行
		fail :
*/
extern uint32_t crs_sleep(uint32_t  milliseconds);
{
	return usleep( milliseconds * 1000 );
}