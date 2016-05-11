/*
*sem.h
*semaphore management
*信号量的创建,使用,删除等
*/
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef _CRS_SEM_H_
#define _CRS_SEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
	function : 
		信号量的handle			
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_sem_handler crs_sem_handler_t;

/*
	function : 
		创建一个信号量			
	input : 
		无
	return value : 
		success :	返回所创建的信号量的内存空间
		fail : 	返回NULL
*/
crs_sem_handler_t * crs_sem_create();

 /*
	function : 
		等待信号量触发			
	input : 
		crs_sem_handler_t *sem : 信号量的handle
	return value : 
		success : 
		fail : 	
*/
int32_t crs_sem_wait(crs_sem_handler_t *sem);

 /*
	function : 
		触发信号量	power on self test		
	input : 
	return value : 
		success :	
		fail : 	
*/
int32_t crs_sem_post(crs_sem_handler_t *sem);

 /*
	function : 
		销毁信号量			
	input : 
		crs_sem_handler_t *sem  
	return value : 
		success :	
		fail : 	
*/
int32_t crs_sem_destroy(crs_sem_handler_t *sem);

#ifdef __cplusplus
extern "C"
{
#endif
#endif
