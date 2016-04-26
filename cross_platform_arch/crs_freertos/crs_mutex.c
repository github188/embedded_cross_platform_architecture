/*			FreeRTOS
*mutex.c
*mutex management
*mutex锁的创建,使用和删除等操作
*/
#include "crs_mutex.h"
#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"

#include "FreeRTOS.h"
#include "queue.h"

/*
	function : 
				mutex handler	
	input : 
	return value : 
		success :	
		fail : 	
*/
struct crs_mutex_handler
{
	mutex_t mutex;
}

 /*
	function : 
				分配内存并创建mutex,创建失败
	input : 
	return value : 
		success :	返回所创建的mutex_handler类型的地址的指针
		fail : 	返回NULL
*/
extern crs_mutex_handler_t* crs_mutex_create(void)
{
	crs_mutex_handler_t *mutex_handler = (crs_mutex_handler_t *)crs_malloc(sizeof ( crs_mutex_handler_t ));
		crs_memset(mutex_handler, 0 , sizeof( crs_mutex_handler_t ));
		mutex_handler -> mutex = (mutex_t)xSemaphoreCreateRecursiveMutex();
	return mutex_handler;
}

 /*
	function : 
			锁住mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回1
		fail : 	返回0
*/
extern int32_t crs_mutex_lock(crs_mutex_handler_t *mutex)
{
	if(NULL == mutex)
	{
		crs_dbg("mutex is NULL\r\n");
		return -1;
	}
	else
	{
		int32_t ret = ( int32_t )xQueueTakeMutexRecursive((QueueHandle_t)mutex, portMAX_DELAY);
		if(-1 == ret)
		{
			crs_dbg("mutex lock failed\r\n");
			return -1;
		}
		return 0;
	}
}
 /*
	function : 
			解锁mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回1
		fail : 	返回0
*/
extern int32_t crs_mutex_unlock(crs_mutex_handler_t *mutex)
{
	if(NULL == mutex)
	{
		crs_dbg("mutex is NULL\r\n");
		return -1;
	}
	else
	{
		int32_t ret = ( int32_t )xQueueGiveMutexRecursive( mutex );
		if(-1 == ret)
		{
			crs_dbg("crs_mutex mutex unlock failed\r\n");
			return -1;
		}
		return 0;
	}
}
 /*
	function : 
			销毁mutex并释放内存		
	input : crs_mutex_handler_t *mutex -- mutex handler
	return value : 
		success :
		fail :
*/
extern void crs_mutex_destroy(crs_mutex_handler_t *mutex)
{
	if( NULL == mutex )
	{
		crs_dbg("mutex is NULL\r\n");
		return;
	}
	crs_free(mutex);
}
