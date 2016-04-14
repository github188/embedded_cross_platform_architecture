/*
*time.h
*time management
*时间的管理,计时器使用
*/

#ifndef _CRS_TIME_H_
#define _CRS_TIME_H_
 /*
	function :

	input :
	return value :
		success :
		fail :
*/
#ifdef __cplusplus
extern "C"
{
#endif

/*
	function :
		获取开机启动时间 单位us
	input :
	return value :
		success : 返回从开机到目前的绝对时间,get time via ticks
		fail : 	返回0
*/
extern int64_t crs_uptime();

/*
	function :
		睡眠 单位us (1/10^9) second
	input :
		uint32_t microseconds ：所需要睡眠的时间
	return value :
		success : 当前task会让出cpu，在睡眠microseconds后继续运行
		fail :
*/
extern uint32_t crs_usleep(uint32_t micro_seconds);

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

#ifdef __cplusplus
extern "C"
{
#endif
#endif
