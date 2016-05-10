/*		ucos-ii
*crs_queue.c
*queue management
*队列的创建,使用和删除等
*/
#include "crs_types.h"
#include "crs_queue.h"

#include "ucos_ii.h"
struct crs_queue_cb_s{
	OS_EVENT* queue_cb;
};

 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
crs_queue_cb_t *crs_create_queue(int8_t queue_size, int16_t element_size,uint8_t *err_code)
{
	crs_queue_cb_t *queue=NULL;
	queue=(crs_queue_cb_t *) crs_malloc(sizeof(crs_queue_cb_t));
	queue->queue_cb->OSEventType = OS_EVENT_TYPE_Q;

	if(NULL==queue)
	{
		*err_code = QUEUE_CREATE_FAIL;
		return NULL;
	}
	queue->queue_cb = OSQCreate(queue_size, element_size);
	if(queue->queue_cb != 0)
	{
		*err_code = QUEUE_CREATE_SUCCESS;
		return queue;
	}
	else
	{
        crs_free(queue);
		*err_code = QUEUE_CREATE_FAIL;
		return NULL;
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

void crs_write_queue(crs_queue_cb_t* cb, void* message, int32_t timeout_ms,uint8_t *err_code)
{
    if(0 == timeout_ms)
    {
		if (osi_MsgQWrite(&(cb->queue_cb), message, OSI_WAIT_FOREVER) < 0)
		{
			*err_code = QUEUE_WRITE_FAIL;
			return ;
		}
		else
		{
			*err_code = QUEUE_WRITE_SUCCESS;
			crs_dbg("crs_write_queue write suceess\n");
            return;
		}
    }
    else
    {
		if (osi_MsgQWrite(&(cb->queue_cb), message, timeout_ms) < 0)
		{
			*err_code = QUEUE_WRITE_FAIL;
			return ;
		}
		else
		{
			*err_code = QUEUE_WRITE_SUCCESS;
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
void crs_read_queue(crs_queue_cb_t* cb, void *data,  int32_t timeout_ms, uint8_t *err_code)
{
    if(0 == timeout_ms)
    {
		if (OSQAccept(&(cb->queue_cb), data) < 0)
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
    else
    {
    	crs_sleep(timeout_ms);//如何设置超时？
		if (OSQAccept(&(cb->queue_cb), data) < 0)
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
		计算队列中数据的个数			
	input : 
		crs_queue_cb_t *cb ： 队列控制
	return value : 
		success :	返回队列中元素的个数
		fail : 	返回

int32_t crs_queue_count(crs_queue_cb_t *cb)
{

}
*/
/*
	function : 
		计算队列中数据的个数			
	input : 
		crs_queue_cb_t *cb ： 队列控制
	return value : 
		success :	返回队列中元素的个数
		fail : 	返回
*/

void crs_destroy_queue(crs_queue_cb_t* cb, uint8_t *err_code)
{
	if (OSQDel((OS_EVENT *)&(cb->queue_cb), OS_DEL_NO_PEND, err_code) == NULL)
	{
		*err_code=QUEUE_DESTROY_FAIL;
	}
	else
	{
		*err_code=QUEUE_DESTROY_SUCCESS;
		crs_free(cb);
	}
}
