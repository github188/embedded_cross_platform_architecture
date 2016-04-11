/*
*mutex.h
*mutex management
*mutex锁的创建,使用和删除等操作
*/
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef __CRS_MUTEX_H__
#define __CRS_MUTEX_H__


#ifdef __cplusplus
extern "C" {
#endif
/*
	function : 
				mutex handler	
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_mutex_handler_t crs_mutex_handler_t;

 /*
	function : 
				分配内存并创建mutex,创建失败
	input : 
	return value : 
		success :	返回所创建的mutex_handler类型的地址的指针
		fail : 	返回NULL
*/
extern crs_mutex_handler_t* crs_mutex_create(void);

 /*
	function : 
			锁住mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回0
		fail : 	返回-1
*/
extern int32_t crs_mutex_lock(crs_mutex_handler_t *mutex);

 /*
	function : 
			解锁mutex		
	input : 
			crs_mutex_handler_t *mutex
	return value : 
		success :	返回0
		fail : 	返回-1
*/
extern int32_t crs_mutex_unlock(crs_mutex_handler_t *mutex);

 /*
	function : 
			销毁mutex并释放内存		
	input : crs_mutex_handler_t *mutex -- mutex handler
	return value : 
		success :	返回0
		fail : 	返回-1
*/
extern int32_t crs_mutex_destroy(crs_mutex_handler_t *mutex);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __crs_THREAD_H__ */
