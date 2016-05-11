/*				linux
*sem.c
*semaphore management
*信号量的创建,使用,删除等
*/

#include "crs_types.h"
#include "crs_mem.h"
#include "crs_dbg.h"
#include "crs_sem.h"

#include <semaphore.h>

/*
	function :
		信号量的handle
	input :
	return value :
		success :
		fail :
*/
struct crs_sem_handler
{
	struct semaphore sem_cb;
};

/*
	function :
		创建一个信号量,初始值为0
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
	crs_memset( crs_sem_handler, 0, sizeof(crs_sem_handler_t));
	sem_init( &(crs_sem_handler->sem_cb ), 1, 0);
	return crs_sem_handler;
}

 /*
	function :
		等待信号量
	input :
		crs_sem_handler_t *sem : 信号量的handle
	return value :
		success : 获取信号另
		fail :
*/
int32_t crs_sem_wait(crs_sem_handler_t *sem)
{
	return sem_wait( &( sem->sem_cb ) );
}

 /*
	function :
		触发信号量
	input :
		crs_sem_handler_t *sem : 信号量的控制块
	return value :
		success : 0
		fail : -1
*/
int32_t crs_sem_post(crs_sem_handler_t *sem)
{
	return sem_post( &( sem -> sem_cb ) );
}

 /*
	function :
		销毁信号量
	input :
		crs_sem_handler_t *sem : 信号量的控制块
	return value :
		success :
		fail :
*/
void crs_sem_destroy(crs_sem_handler_t *sem)
{
	sem_destroy( &( sem -> sem_cb ) );
}

