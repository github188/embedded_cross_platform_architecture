/*
*crs_queue.h
*queue management
*队列的创建,使用和删除等
*/
#include "queue.h"
#include "crs_types.h"
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
					
	input : 
	return value : 
		success :	
		fail : 	
*/

/*
 * 创建队列，分配内存，并初始化
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
crs_queue_cb_t *crs_create_queue(int8_t queue_size, int16_t element_size, uint8_t *err_code)
{
	crs_queue_cb_t *queue = NULL;
	queue = (crs_queue_cb_t *) crs_malloc( sizeof (crs_queue_cb_t) );
	if(queue_size <= 0 || element_size <= 0)
	{
		crs_dbg("crs_create_queue queue_size of element size error,please check!\r\n");
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
		crs_memfree(queue);
		return NULL;
	} 
	else 
	{
		*err_code = QUEUE_SUCCESS;
		return (crs_queue_cb_t)queue;
	}
}
/*
 *将message写入队列,根据timeout_ms判断是否阻塞，0表示阻塞，非0 表示超时时间
 */
 /*
	function : 
		将message写入队列			
	input : 
		timeout_ms判断是否阻塞，0表示阻塞，非0表示超时时间
	return value : 
		success :	
		fail : 	
*/
void crs_queue_write(crs_queue_cb_t* cb, void* message, int32_t timeout_ms, uint8_t *err_code)
{
    if(0 == timeout_ms) 
	{	//equivalent to xQueueSendToBack()
		if (crs_failed == xQueueSend(&(cb->queue_cb), message, CRS_WAIT_FOREVER)) 
		{
			*err_code = QUEUE_WRITE_FALI;
			return ;
		} 
		else 
		{
			*err_code = QUEUE_SUCCESS;
			crs_dbg("crs_write_queue write suceess\n");
            return;
		}
    } 
	else 
	{
		if (crs_failed == xQueueSend(&(cb->queue_cb), message, timeout_ms)) 
		{
			*err_code=QUEUE_WRITE_FALI;
			return ;
		} 
		else 
		{
			*err_code = QUEUE_SUCCESS;
			crs_dbg("crs_write_queue write suceess\n");
            return;
		}
	}
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
		if (crs_failed == xQueueReceive(&(cb->queue_cb), data, CRS_WAIT_FOREVER)) 
		{
			*err_code=QUEUE_WRITE_FALI;
			return;
		} 
		else 
		{
			*err_code = QUEUE_SUCCESS;
			crs_dbg("crs_read_queue write suceess\n");
            return;
		}
    } 
	else 
	{
		if (crs_failed == xQueueReceive(&(cb->queue_cb), data, timeout_ms)) 
		{
			*err_code=QUEUE_WRITE_FALI;
			return;
		} 
		else 
		{
			*err_code = QUEUE_SUCCESS;
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
void crs_destroy_queue(crs_queue_cb_t* cb, uint8_t *err_code)
{
	vQueueDelete( (QueueHandle_t)(&(cb->queue_cb)) );
	crs_memfree(cb);
	*err_code = QUEUE_SUCCESS;
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
