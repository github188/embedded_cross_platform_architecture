/*		freertos
*crs_queue.h
*queue management
*队列的创建,使用和删除等
*/
#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"
#include "crs_queue.h"

#include "queue.h"
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/

struct crs_queue_cb_s{
	QueueHandle_t queue_cb;
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
	crs_queue_cb_t *queue = NULL;
	queue = (crs_queue_cb_t *) crs_malloc( sizeof (crs_queue_cb_t) );
	if(queue_size <= 0 || element_size <= 0)
	{
		crs_dbg("crs_create_queue queue_size of element size error!\r\n");
		*err_code = QUEUE_CREATE_FAIL;
		return NULL;
	}
	
	if(NULL == queue)
	{
		*err_code = QUEUE_CREATE_FAIL;
		return NULL;
	}
	
	queue = xQueueCreate( queue_size, element_size)
	if ( queue == NULL) 
	{
		*err_code = QUEUE_CREATE_FAIL;
		crs_free(queue);
		return NULL;
	} 
	else 
	{
		*err_code = QUEUE_CREATE_SUCCESS;
		return (crs_queue_cb_t)queue;
	}
}

 /*
	function : 
		将message写入队列			
	input : 
		timeout_ms判断是否阻塞，0表示阻塞，非0表示超时时间
	return value : 
		success :	
		fail : 	
*/
int32_t crs_write_queue(crs_queue_cb_t* cb, void* message, int32_t timeout_ms)
{
    int tmp = 0;
    if(0 == timeout_ms)
    {
        while( pdPASS != ( tmp = xQueueSend(cb->queue_cb, message, os_msec_to_ticks(1000*1000)) ) )
        {
        	crs_dbg("try write queue......\r\n");
        }
        return QUEUE_WRITE_SUCCESS;
    }
    tmp = xQueueSend(cb->queue_cb, message, os_msec_to_ticks(timeout_ms));

	if(pdPASS != tmp)
	{
		crs_dbg("crs_write_queue write failed\r\n");
		return QUEUE_WRITE_FAIL;
	}
    return QUEUE_WRITE_SUCCESS;
}
 /*
	function : 
		读取队列元素，根据timeout_ms判断是否阻塞			
	input : 
		crs_queue_cb_t* cb ：队列控制
		void *data	： 读取数据buffer
		int32_t timeout_ms ：超时时间,0表示
		uint8_t *err_code
	return value : 通过err-code返回结果完成信息
		success :	
		fail : 	
*/
void crs_read_queue(crs_queue_cb_t* cb, void *data, int32_t timeout_ms, uint8_t *err_code)
{
    if(0 == timeout_ms) 
	{
    	 while(pdPASS != (tmp = xQueueReceive(cb->queue_cb, data, os_msec_to_ticks(100))))
    	 {
    		 crs_dbg("try read queue......\r\n");
    	 }
    	 return QUEUE_READ_SUCCESS;
    } 
	else 
	{
		if ( pdPASS != xQueueReceive(&(cb->queue_cb), data, timeout_ms))
		{
			*err_code=QUEUE_READ_FAIL;
			return;
		} 
		else 
		{
			*err_code = QUEUE_READ_SUCCESS;
			crs_dbg("crs_read_queue write suceess\n");
            return;
		}
	}
}
 /*
	function : 
		销毁队列，并释放内存。			
	input :
		crs_queue_cb_t* cb ： 队列控制
		uint8_t *err_code ： 错误码
	return value : err_code返回执行信息
		success :	
		fail : 	
*/
int32_t crs_destroy_queue(crs_queue_cb_t* cb, uint8_t *err_code)
{
	vQueueDelete( cb->queue_cb );
	crs_free(cb);
	return QUEUE_DESTROY_SUCCESS;
}

/*
	function : 
		计算队列中数据的个数			
	input : 
		crs_queue_cb_t *cb ： 队列控制
	return value : 
		success :	返回队列中元素的个数
		fail : 	返回
*/
int32_t crs_queue_count(crs_queue_cb_t *cb)
{
	return uxQueueMessagesWaiting(cb->queue_cb);
}
/*
	function : 
		计算队列中数据的个数			
	input : 
		crs_queue_cb_t *cb ： 队列控制
	return value : 
		success :	返回队列中元素的个数
		fail : 	返回
*/

int32_t crs_queue_spaces_available(crs_queue_cb_t *cb)
{
	return uxQueueSpacesAvailable(cb->queue_cb);
}
