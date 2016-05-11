/*******************************************************************
*					test queue
*
* 队列的创建，删除等等
* 场景描述
* 生产者 -- 消费者模型
* 生产者生产好东西后检查队列是否满，不满则将生产好的东西放到队列中，满了
* 则停止生产，等待队列有空闲位置
* 消费者这边需要消耗东西时检查队列是否为空，不空则从队列中取出一个东西，
* 若空则等待，直到队列中有东西
********************************************************************/

#include "crs_types.h"
#include "crs_queue.h"
#include "crs_task.h"
#include "crs_mem.h"


/*******************************************************************
*					global variables
********************************************************************/
crs_queue_cb_t * product_line;
crs_mutex_handler_t * protect_queue;

void productor(void *args)
{
	while( true )
	{
		crs_write_queue(product_line, )
	}
}

void consumer(void *args)
{
	while( true )
	{

	}
}

void queue_test()
{
	int32_t errno = 0;
	crs_task_handler_t *consumer_h, *productor_h;

	product_line = crs_create_queue(5, 32, &errno);
	if( NULL == product_line )
	{
		crs_dbg("queue_test crs_create_queue falied\r\n");
		return;
	}
	protect_queue = crs_mutex_create();
	if( NULL == protect_queue )
	{
		crs_dbg("queue_test crs_mutex_create failed\r\n");
		return;
	}

	consumer_h = crs_task_create( 1, 1024, productor, NULL);
	if(NULL == consumer_h)
	{
		crs_dbg("queue_test crs_task_create productor failed\r\n");
		return;
	}
	productor_h = crs_task_create(1, 1024, consumer, NULL);
	if(NULL == productor)
	{
		crs_dbg("queue_test crs_task_create consumer failed\r\n");
		return;
	}
}
