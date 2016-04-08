/*
*mutex.h
*mutex management
*mutex锁的创建,使用和删除等操作
*/
#include "crs_mutex.h"
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
typedef struct crs_mutex_handler_s crs_mutex_handler_t;

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
	return (crs_mutex_handler_t *)xSemaphoreCreateRecursiveMutex();
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
		return crs_failed;
	}
	else
	{
		int ret = (int)xQueueTakeMutexRecursive((QueueHandle_t)mutex, portMAX_DELAY);
		if(crs_failed == ret)
		{
			crs_dbg("mutex lock failed\r\n");
			return crs_failed;
		}
		return crs_success;
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
		return crs_failed;
	}
	else
	{
		int ret = (int)xQueueGiveMutexRecursive(mutex);
		if(crs_failed == ret)
		{
			crs_dbg("crs_mutex mutex unlock failed\r\n");
			return crs_failed;
		}
		return crs_success;
	}
}
 /*
	function : 
			销毁mutex并释放内存		
	input : crs_mutex_handler_t *mutex -- mutex handler
	return value : 
		success :	返回1
		fail : 	返回0
*/
extern int32_t crs_mutex_destroy(crs_mutex_handler_t *mutex)
{
	if(NULL == mutex)
	{
		return crs_failed;
	}
	crs_memfree(mutex);
	return crs_success;
}
