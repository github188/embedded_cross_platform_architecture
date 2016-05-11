/*
*task.h
*task management
任务的创建, 删除
*/
#ifndef _CRS_TASK_H_
#define _CRS_TASK_H_

#ifdef __cplusplus
extern "C"
{
#endif

/************************ task 接口 *********************************/
#ifdef UCOS_II
#define crs_task_return
typedef void  crs_task_return_t;
#else
typedef void *  crs_task_return_t;
#define crs_task_return  NULL
#endif

 /*
	function :
		task handler
	input :
	return value :
		success :
		fail :
*/
typedef struct crs_task_handler_s crs_task_handler_t;

// ptask_t_is_valid
// detach
// join
 /*
	function :

	input :
	return value :
		success :
		fail :
*/
typedef crs_task_return_t (*crs_task_start_routine)(void *);

/*
 * 创建线程
 * task: 线程句柄 ，包含线程控制块 和线程回调函数
 * priority ：SDK若期望使用系统默认值， 则在调用时会传入0
 * stack_size ：线程需要使用的栈大小
 * callback ：线程的执行函数体
 * arg ：callback的参数
 */
  /*
	function :
		创建线程
	input :
		task: 线程句柄 ，包含线程控制块 和线程回调函数
		priority ：SDK若期望使用系统默认值， 则在调用时会传入0
		stack_size ：线程需要使用的栈大小
		callback ：线程的执行函数体
		arg ：callback的参数
	return value :
		success :
		fail :
*/
extern crs_task_handler_t* crs_task_create(uint8_t priority, int32_t stack_size, crs_task_start_routine start_routine, void* arg);


/*
	function :
		销毁由crs_task_create创建的线程
	input :
		task handler
	return value :
		success :
		fail :
*/
extern int32_t crs_task_destroy(crs_task_handler_t *task);

#ifdef __cplusplus
extern "C"
{
#endif

#endif
