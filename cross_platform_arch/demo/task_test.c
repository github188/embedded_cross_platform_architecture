/*
 * 	任务管理测试
 */

#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"
#include "crs_str.h"
#include "crs_mutex.h"

/*******************************************************************
*		此处定义所需要测试的部分的开关
*		宏定义为0表示不进行测试
*		宏定义为1表示进行测试
********************************************************************/
#define test_mutex 1


/*******************************************************************
*					global variables
********************************************************************/
//计数器，用于测试mutex对临界资源的保护
int cnt = 0;
//mutex，用于保护临界资源，实现其他任务对临界资源的互斥访问
crs_mutex_handler_t *crs_lock;
//semaphore, 此处用于实现多任务之间的同步，相当于软中断

crs_sem_handler_t *bus_arrive_station;
crs_sem_handler_t *bus_door_open;
crs_sem_handler_t *passenger_aboard;

/*******************************************************************
*					test mutex in multitasks						*
********************************************************************/
void task_a_mutex(void *args)
{
	while( true )
	{
		crs_mutex_lock( crs_lock );
		cnt ++;
			printf("task_a run, cnt : %d\r\n ", cnt );
		crs_mutex_unlock( crs_lock );
//进入睡眠状态，主动让出cpu
		crs_sleep( 20 );
	}
}

void task_b_mutex(void *args)
{
	while( true )
	{
		crs_mutex_lock( crs_lock );
		cnt ++;
			printf("task_b run, cnt : %d\r\n ", cnt );
		crs_mutex_unlock( crs_lock );
//进入睡眠状态，主动让出cpu
		crs_sleep( 20 );
	}
}

/********************************************************************
* 本例子通过创建两个任务task_a_mutex 和  task_b_mutex,两个任务同时操作全*
* 局变量cnt，通过mutex保护cnt，使得两个任务能够交互操作cnt，并经行相应的*
* 打印输出，以显示任务结* 果的情况* 两个任务交替打印出cnt的值，发现cnt的*
* 值没有重复，并且不断增加* ,说明mutex有保护临界资源cnt的访问，若有出现  *
* 重复的cnt的值，说明mutex没有起到作用								 *
********************************************************************/
void task_and_mutex_test()
{
	crs_task_handler_t *handler_a = NULL, *handler_b = NULL;
	handler_a = crs_task_create(1, 1024, task_a_mutex, NULL);
	if(NULL == handler_a)
	{
		crs_dbg("task_test crs_task_create task_a failed\r\n");
		return;
	}
	handler_b = crs_task_create(1, 1024, task_b_mutex, NULL);
	if(NULL == handler_b)
	{
		crs_dbg("task_test crs_task_create  task_b failed\r\n");
		return;
	}
}

/*******************************************************************
*					test semaphore in multitasks
*现在镜头拉向公交车，有两个任务 公交车司机 -- Jonny 和	售票员 Sara
*Jonny正常情况下在开车，Sara负责售票
*
*当汽车到站时，Jonny停车开门，并告诉Sare当乘客都上车后告诉他一下，当前乘
*客上车，当乘客都上车之后，Sare告诉Jonny，可以开车了，然后Jonny就开车
*
********************************************************************/

void DriverJonny(void *args)
{

}
void TicketSellerSara(void *args)
{

}
void BusStation(void *args)
{
	crs_printf(" Bus is at station !\r\n");
	crs_sem_post( bus_arrive_station );
}
void semaphore_test()
{
	crs_task_handler_t *handler_bus, *handler_jon, *handler_sar;
	bus_arrive_station = crs_sem_create();
	bus_door_open = crs_sem_create();
	passenger_aboard = crs_sem_create();

	handler_bus = crs_task_create(1, 1024, BusStation, NULL);
	if(NULL == handler_bus)
	{
		crs_dbg("semaphore_test crs_task_create BusStation failed\r\n");
		return;
	}

	handler_jon = crs_task_create(1, 1024, DriverJonny, NULL);
	if(NULL == handler_bus)
	{
		crs_dbg("semaphore_test crs_task_create DriverJonny failed\r\n");
		return;
	}

	handler_jon = crs_task_create(1, 1024, TicketSellerSara, NULL);
	if(NULL == handler_bus)
	{
		crs_dbg("semaphore_test crs_task_create TicketSellerSara failed\r\n");
		return;
	}
}
int main()
{
	crs_lock = crs_mutex_create();
	if( NULL == crs_lock )
	{
		crs_dbg("crs_lock create falied\r\n");
		return 0;
	}
#if test_mutex
	task_test_mutex();
#endif

	return 0;
}
