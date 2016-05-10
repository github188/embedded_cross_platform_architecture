/*			ucos-ii
*crs_task.c
*task management
任务的创建, 删除
*/
#include "crs_mem.h"
#include "crs_types.h"
#include "crs_task.h"

/************************ task 接口 *********************************/
struct crs_task_handler_s {
	TaskHandle_t task_handle;
};

 /*
	function :

	input :
	return value :
		success :
		fail :
*/
typedef void crs_task_return_t ;
typedef crs_task_return_t (*crs_task_entry)(void *);

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
extern crs_task_handler_t* crs_task_create(uint8_t priority, int32_t stack_size, crs_task_entry start_routine, void* arg)
{
	crs_task_handler_t *crs_handle = NULL;
	TaskHandle_t *xHandle = NULL;
	xTaskCreate( start_routine, "task", stack_size, arg, priority, xHandle );
	if(NULL == xHandle)
	{
		crs_dbg("crs_task_create falied\r\n");
		return NULL;
	}
	crs_handle->task_handle = xHandle;
	return crs_handle;
}

/*
	function :
		销毁由crs_task_create创建的线程
	input :
		task handler
	return value :
		success : 1
		fail : 0
*/
extern int32_t crs_task_destroy(crs_task_handler_t *task)
{
	int32_t ret = vTaskDelete(task->task_handle);
	if(0 == ret)
	{
		crs_dbg("crs_task_destroy failed\r\n");
		return 0;
	}
	crs_memfree(task);
	return 1;
}
