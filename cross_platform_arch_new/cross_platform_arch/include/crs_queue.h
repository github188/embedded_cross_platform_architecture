/*
*crs_queue.h
*queue management
*队列的创建,使用和删除等
*/

/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef CRS_QUEUE_H_
#define CRS_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 队列的控制信息
 */
typedef enum {
	QUEUE_WRITE_FALI = 1,
	QUEUE_READ_FAIL = 2,
	QUEUE_SUCCESS = 3,
	QUEUE_CREATE_FAIL = 4,
	QUEUE_DESTROY_FAIL = 5,
	//队列满
	QUEUE_FULL = 6,
	//队列为空
	QUEUE_EMPTY = 7
} CRS_QUEUE_ERR;


 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_queue_cb_t crs_queue_cb_t;

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
crs_queue_cb_t *crs_create_queue(int32_t queue_size, int32_t element_size, int32_t *err_code);
 /*
	function : 
		非阻塞的写入队列,如果能够写入队列,则进行写,如果不能,则立即返回			
	input : 
		crs_queue_cb_t* cb : 所写的队列的队列控制块
		void* data : 向队列中写入的数据
	return value : 
		success :	返回0
		fail : 	返回errno
*/
int32_t crs_trywrite_queue(crs_queue_cb_t* cb, void* data);
/*
 *将data写入队列,根据timeout_ms判断是否阻塞，0表示阻塞，非0 表示超时时间
 */
 /*
	function : 
		将data写入队列			
	input : 
		crs_queue_cb_t* cb
		void* data, int32_t timeout_ms : 0表示forever，非0 表示超时时间
		uint8_t *err_code
	return value : 
		success :	
		fail : 	
*/
int32_t crs_write_queue(crs_queue_cb_t* cb, void* data);
/*
 * 读取队列元素。根据timeout_ms判断是否阻塞，0表示阻塞，非0 表示超时时间
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
int32_t crs_read_queue(crs_queue_cb_t* cb, void *data);

  /*
	function : 
		非阻塞读取队列中的数据
		如果有数据则读取,并将读取的数据放到data中
		如果队列中没有数据,则立即返回,并返回errno
	input : 
		crs_queue_cb_t* cb : 队列控制块
		void *data	: 所读取的队列的信息,NULL表示队列中没有数据
	return value : 
		success :	返回0
		fail : 	返回errno
*/
int32_t crs_tryread_queue(crs_queue_cb_t* cb, void *data);
/*
 * 销毁队列，并释放内存。
 */
 /*
	function : 
		销毁队列，并释放内存。			
	input : 
		crs_queue_cb_t* cb : 所需要销毁的队列控制块
	return value : 无
		success :	
		fail : 	
*/
void crs_destroy_queue( crs_queue_cb_t* cb );

/*
	function : 
		统计队列中空闲的队列空间个数			
	input : 
		crs_queue_cb_t *cb : 队列控制块
	return value : 
		success :	返回空闲队列控制块的数目
		fail : 	返回0
*/
int32_t crs_queue_count(crs_queue_cb_t *cb);



#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* CRS_QUEUE_H_ */