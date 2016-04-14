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
 * 
 */
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
crs_queue_cb_t *crs_create_queue(int8_t queue_size, int16_t element_size, uint8_t *err_code);

/*
 *将message写入队列,根据timeout_ms判断是否阻塞，0表示阻塞，非0 表示超时时间
 */
 /*
	function : 
		将message写入队列			
	input : 
		crs_queue_cb_t* cb
		void* message, int32_t timeout_ms
		uint8_t *err_code
	return value : 
		success :	
		fail : 	
*/
void crs_write_queue(crs_queue_cb_t* cb, void* message, int32_t timeout_ms, uint8_t *err_code);
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
void crs_read_queue(crs_queue_cb_t* cb, void *data,  int32_t timeout_ms,
		uint8_t *err_code);

/*
 * 销毁队列，并释放内存。
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
void crs_destroy_queue(crs_queue_cb_t* cb, uint8_t *err_code);

/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
int crs_queue_count(crs_queue_cb_t *cb);



#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* CRS_QUEUE_H_ */