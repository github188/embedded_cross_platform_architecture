/*			linux
*mutex.c
*mutex management
*mutex锁的创建,使用和删除等操作
*/

#include "crs_types.h"
#include "crs_mutex.h"
#include "crs_mem.h"
#include "crs_debug.h"

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
	pthread_mutex_t mutex_cb;
};
 /*
	function : 
				分配内存并创建mutex,创建失败
	input : 
	return value : 
		success :	返回所创建的mutex_handler类型的地址的指针
		fail : 	返回NULL
*/
extern crs_mutex_handler_t* crs_mutex_create ()
{
	crs_mutex_handler_t *mutex_handle = ( crs_mutex_handler_t * ) crs_malloc ( sizeof ( crs_mutex_handler_t ) );
	if( NULL == mutex_handle )
	{
		crs_dbg( "mutex create failed\r\n" );
		return NULL;
	}
	pthread_mutex_init( &( mutex_handle -> mutex_cb ), NULL );
	return mutex_handle;
}

 /*
	function : 
			锁住mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回0
		fail : 	返回!0
			EINVAL
			The value specified by mutex does not refer to an initialized mutex object.
			EAGAIN
			The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded.
			The pthread_mutex_lock() function may fail if:
			EDEADLK
			The current thread already owns the mutex.
*/
extern int32_t crs_mutex_lock ( crs_mutex_handler_t *mutex )
{
	if( NULL == mutex )
	{
		crs_dbg( "NULL mutex\r\n" );
		return 0;
	}
	pthread_mutex_lock ( &( mutex -> mutex_cb) );
}
 /*
	function : 
			trylock mutex
			尝试着去加锁，如果不能加锁，则立马返回，放弃加锁
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success : 0
		fail : 	!0
*/
extern int32_t crs_mutex_trylock( crs_mutex_handler_t *mutex )
{
	return pthread_mutex_trylock( &( mutex -> mutex_cb) );
}

 /*
	function : 
			解锁mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回0
		fail : 	!0值

*/
extern int32_t   crs_mutex_unlock(crs_mutex_handler_t *mutex)
{
	if( NULL == mutex )
	{
		crs_dbg( "NULL mutex\r\n" );
		return -1;
	}
	pthread_mutex_unlock( &( mutex -> mutex_cb) );
}

 /*
	function : 
			销毁mutex并释放内存		
	input : crs_mutex_handler_t *mutex -- mutex handler
	return value : 
		success : 0
		fail : -1
*/
extern int32_t crs_mutex_destroy(crs_mutex_handler_t *mutex)
{
	if( NULL == mutex )
	{
		crs_dbg( "crs_mutex_destroy failed : mutex == NULL\r\n");
		return -1;
	}
	pthread_mutex_destroy( &( mutex->mutex_cb ) );
	dana_free(mutex);
	mutex = NULL;
	return 0;
}
