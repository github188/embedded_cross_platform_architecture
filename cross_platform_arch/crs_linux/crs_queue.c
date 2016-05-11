/*
 * 				linux
*crs_queue.c
*queue management
*队列的创建,使用和删除等
*/

#include "crs_queue.h"
#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"
#include "crs_str.h"

#include "message_queue.h"
#include <stdlib.h>
#include <string.h>

struct crs_queue_cb
{
	struct message_queue queue_cb;
};

 /*
	function : 
		创建队列，分配内存，并初始化			
	input : 
		int8_t queue_size : 队列的元素的个数
		nt16_t element_size ：队列中每个元素的大小
		uint8_t *err_code ：错误码，返回创建队列时返回的信息
	return value : 
		success :	返回所创建的队列的指针
		fail : 	返回NULL
*/
crs_queue_cb_t *crs_create_queue(int8_t queue_size, int16_t element_size, uint8_t *err_code)
{
	crs_queue_cb_t *queue=NULL;
	queue=(crs_queue_cb_t *) crs_malloc(sizeof(crs_queue_cb_t));

	if(NULL==queue)
	{
		*err_code=QUEUE_CREATE_FAIL;
        crs_dbg("create queue failed\n");
		return NULL;
	}
	if( !message_queue_init(&(queue->queue_cb),element_size,queue_size) )
	{
		*err_code=QUEUE_CREATE_SUCCESS;
		return queue;
	}
	else
	{
        crs_free(queue);
		*err_code=QUEUE_CREATE_FAIL;
        crs_dbg("init message queue failed\n");
		return NULL;
	}
}
 /*
	function : 
		将data写入队列			
	input : 
		crs_queue_cb_t* cb
		void* data: 存储保存的数据
		int32_t timeout_ms : 0表示forever，非0 表示超时时间
	return value : 
		success :	
		fail : 	
*/
int32_t crs_write_queue(crs_queue_cb_t* cb, void* data, int32_t timeout_ms)
{
	void * tmp = NULL;

	if( NULL == cb || NULL == data )
	{
		crs_dbg("cb or data NULL\r\n");
		return QUEUE_WRITE_FAIL;
	}
	tmp = message_queue_message_alloc_blocking ( &( cb->queue_cb ) );

	if( NULL == tmp )
	{
		return QUEUE_WRITE_FAIL;
	}
	crs_memcpy( tmp, data, strlen(data) );
	message_queue_write( &( cb -> queue_cb ), tmp );
	crs_dbg( "crs_write_queue suceess\n" );
	return QUEUE_WRITE_SUCCESS;
}
 /*
	function : 
		阻塞读取队列中的元素
	input : 
		crs_queue_cb_t* cb ： 队列控制块
 	 	void *data ： 存储读取元素的buffer
	return value : 
		success :	返回QUEUE_READ_SUCCESS
		fail : 返回QUEUE_READ_FAIL
*/
int32_t crs_read_queue( crs_queue_cb_t* cb, void *data ,int32_t timeout_ms)
{
	void* tmp = NULL;
	int32_t cnt = timeout_ms;
	if( NULL == cb || NULL == data )
	{
		crs_dbg("cb or data NULL\r\n");
		return QUEUE_READ_FAIL;
	}

	if( 0 == timeout_ms )
	{
		tmp = message_queue_read( &( cb->queue_cb) );
	}
	else
	{
		while( NULL == (tmp = message_queue_tryread( &( cb->queue_cb)) ) )
		{
			cnt -= 10;
			if(cnt < 0)
			{
				break;
			}
		}
	}

	if( NULL == tmp )
	{
		crs_dbg( "read queue failed\r\n" );
		return QUEUE_READ_FAIL;
	}
	else
	{
		dana_memcpy(data,tmp,sizeof(void*));
		message_queue_message_free(&(cb->queue_cb),tmp);
	}
	return QUEUE_READ_SUCCESS;
}

 /*
	function : 
		销毁队列，并释放内存。			
	input : 
		crs_queue_cb_t* cb : 所需要销毁的队列控制块
	return value : 无
		success :	
		fail : 	
*/
int32_t crs_destroy_queue( crs_queue_cb_t* cb )
{
	if( NULL == cb )
	{
		crs_dbg("crs_destroy_queue failed, cb == NULL\r\n");
		return QUEUE_DESTROY_FAIL;
	}
	message_queue_destroy( &( cb->queue_cb ) );
	crs_free( cb );
	return QUEUE_DESTROY_SUCCESS;
}
