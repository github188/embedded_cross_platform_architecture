/*			linux
*task.c
*task management
任务的创建, 删除etc
*/

#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"
#include "crs_task.h"

#include <errno.h>
#include <pthread.h>

/************************ task 接口 *********************************/

struct dana_thread_handler_s {
	pthread_t task_id;
};

 /*
	function :
		通过typedef定义函数指针
		该函数指针表示的函数类型为 输入void *型数据，返回值为void
	input :
	return value :
		success :
		fail :
*/
typedef void* crs_task_return_t ;
typedef crs_task_return_t (*crs_task_entry)(void *);


  /*
	function :
		创建线程
	input :
		task: 线程句柄 ，包含线程控制块 和线程回调函数
		priority ：SDK若期望使用系统默认值，则在调用时会传入0
		stack_size ：线程需要使用的栈大小
		callback ：线程的执行函数体
		arg ：callback的参数
	return value :
		success : 返回所创建的任务的handle
		fail : 返回NULL
*/
extern crs_task_handler_t* crs_task_create(uint8_t priority, int32_t stack_size, crs_task_entry pentry, void* arg)
{
	crs_task_handler_t* task = ( crs_task_handler_t* ) crs_malloc( sizeof ( crs_task_handler_t ) );
	if ( NULL == task ) {
        crs_dbg("malloc task handle failed\n");
		return NULL;
	}

	if ( ptask_create ( &( task -> taskid ), NULL, (run)pentry, arg)) {
        crs_free(task);
		crs_dbg("create task error  %s\n",strerror(errno));
		return NULL;
	}
	ptask_detach(task -> taskid);
	return task;
}

/*
	function :
		销毁由crs_task_create创建的线程
	input :
		crs_task_handler_t *task ：任务的handle
			success : 返回0
			fail :
*/
extern uint32_t crs_task_destroy(crs_task_handler_t *task)
{
	crs_free(task);
	task = NULL;
	return 0;
}
