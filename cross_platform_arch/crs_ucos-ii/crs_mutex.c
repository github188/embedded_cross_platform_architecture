/*			ucos-ii
*mutex.c
*mutex management
*mutex锁的创建,使用和删除等操作
*/
#include "crs_mutex.h"
#include "crs_types.h"
#include "ucos_ii.h"
/*
	function : 
				mutex handler	
	input : 
	return value : 
		success :	
		fail : 	
*/
struct crs_mutex_handler_s {
    OS_EVENT *mutex;
};


 /*
	function : 
				分配内存并创建mutex,创建失败
	input : 
	return value : 
		success :	返回所创建的mutex_handler类型的地址的指针
		fail : 	返回NULL
*/
crs_mutex_handler_t* crs_mutex_create()
{
            OS_EVENT *local_mutex = NULL;
            crs_mutex_handler_t *mutex = (crs_mutex_handler_t *)crs_malloc(sizeof(crs_mutex_handler_t));
	    if (NULL == mutex) 
		{
			crs_dbg("create mutex failed\r\n");
	        return NULL;
	    }

	    local_mutex = OSSemCreate(1);
	    if (NULL == local_mutex) 
		{
			crs_free(mutex);
	        return NULL;
	    } 
		else 
		{
	        mutex->mutex = local_mutex;
	    }
	    return mutex;
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
int32_t crs_mutex_lock(crs_mutex_handler_t *mutex) 
{
	int8_t err;
	if (NULL == mutex) {
        return -1;
    }
	if (OSSemAccept(mutex->mutex)) {
		return 0;	
	}
	OSSemPend(mutex->mutex, 0, &err);//0 琛ㄧず闃诲

	return 0;
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
int32_t crs_mutex_unlock(crs_mutex_handler_t *mutex) {
	if (NULL == mutex) {
		crs_dbg("mutex NULL\r\n");
		return -1;
	}
	return ((OS_ERR_NONE == OSSemPost(mutex->mutex)) ? 0: -1);
}
 /*
	function : 
			销毁mutex并释放内存		
	input : crs_mutex_handler_t *mutex -- mutex handler
	return value : 
		success :	返回1
		fail : 	返回0
*/
int32_t crs_mutex_destroy(crs_mutex_handler_t *mutex) 
{
	int8_t err;
	if (NULL == mutex) {
			return -1;
	}	
	OSSemDel(mutex->mutex, OS_DEL_NO_PEND, &err);
	if(OS_ERR_NONE != err)
	{
		crs_dbg("crs_mutex_destroy failed\r\n");
		return 0;
	}
	crs_free(mutex);
	return 0;
}
