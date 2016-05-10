/*		ucos-ii
*sem.c
*semaphore management
*信号量的创建,使用,删除等
*/
#include "crs_mem.h"
#include "crs_sem.h"
#include "crs_types.h"

#include "semphr.h"
/*
	function : 
		信号量的handle			
	input : 
	return value : 
		success :	
		fail : 	
*/
struct crs_sem_handler_s
{
	SemaphoreHandle_t sem_cb;
};

/*
	function : 
		创建一个信号量			
	input : 
		无
	return value : 
		success :	返回所创建的信号量的内存空间
		fail : 	返回NULL
*/
crs_sem_handler_t * crs_sem_create()
{
	crs_sem_handler_t *crs_sem_handler = (crs_sem_handler_t *)crs_malloc(sizeof(crs_sem_handler_t));
	if (NULL == crs_sem_handler)
	{
		return NULL;
	}

	vSemaphoreCreateBinary(crs_sem_handler->sem_cb);
	if(NULL == crs_sem_handler->sem_cb)
	{
		crs_dbg("crs_sem.c vSemaphoreCreateBinary failed\r\n");
		return NULL;
	}
	return crs_sem_handler;
}

 /*
	function : 
		活得信号量
	input : 
		crs_sem_handler_t *sem : 信号量的handle
	return value : 
		success : 返回0
		fail : 	返回-1
*/
int32_t crs_sem_take(crs_sem_handler_t *sem)
{
	int32_t ret = xSemaphoreTake( sem->sem_cb, crs_wait_forever );
	if( 0 == ret )
	{
		crs_dbg("crs_sem_take falied\r\n");
		return -1;
	}
	else
	{
		return 0;
	}
}

 /*
	function : 
		释放信号量
	input : 
	return value : 
		success : return 0
		fail : 	return -1
*/
int32_t crs_sem_give(crs_sem_handler_t *sem)
{
	int ret = xSemaphoreGive( sem -> sem_cb );
	if(0 == ret)
	{
		crs_dbg("crs_sem_give falied\r\n");
		return -1;
	}
	else
	{
		return 0;
	}
}

 /*
	function : 
		销毁信号量			
	input : 
		crs_sem_handler_t *sem  
	return value : 
		success :	
		fail : 	
*/
void crs_sem_destroy(crs_sem_handler_t *sem)
{
	vSemaphoreDelete(sem -> sem_cb);
	crs_free( sem );
}
