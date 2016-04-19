/*
*file management
*文件操作
*/
#ifndef _CRS_IOOPS_H_
#define _CRS_IOOPS_H_

#include "crs_types.h"
#define STR_LEN 60
/*
	SEEK_SET,SEEK_CUR,SEEK_END三个宏定义是用于crs_file_seek函数的第三个参数whence的，表示偏移量的相对的位置
	
	SEEK_SET表示从文件头开始算起
	SEEK_CUR表示从文件指针当前位置开始
	SEEK_END表示从文件末尾位置算起
*/
#define SEEK_SET 0	
#define SEEK_CUR 1
#define SEEK_END 2


#ifdef __cplusplus
extern "C"
{
#endif


/*
 * 文件操作接口
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/

typedef struct crs_file_handler crs_file_handler_t;
 
 /*
	function : 
		文件打开模式			
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef enum 
{	
    fmode_r		= 0x0001,   	// 只读。    
    fmode_w		= 0x0002,   	// 只写。如果文件不存在，则创建新文件，否则将清空文件，再写入。
	fmode_a		= 0x0003,		// 追加。如果文件不存在，则创建新文件
} file_mode_e;

/*
 * 文件具有的基本属性
 */
typedef struct 
{
    int8_t  file_name[STR_LEN];     // 用于标记该文件，具有唯一性，可以看作文件名
    uint8_t file_name_len;    		// 文件名的长度，最多不超过60字节
    uint64_t file_size;       		// 文件大小，以字节计算
	uint64_t file_read_start;		//读文件的开始
	uint64_t file_read_pos;		//读文件的位置
	uint64_t file_read_end;		//能读的文件的末尾
	uint64_t file_write_start;		//能写文件的开始
	uint64_t file_write_pos;		//当前写文件的位置
	uint64_t file_write_end;		//能写的文件的末尾
	
} file_info_t;

/************************ file 接口 *********************************/
/*
	function : 
		创建一个mode的新的文件,返回文件描述符	
	input : 
		const int8_t *file_name : 文件名,可以是绝对地址,也可以是相对地址
		file_mode_e mode : 文件创建之后就可以进行相应的读写了,mode表示之后具有的对文件操作的模式
	return value : 
		success : 返回文件控制handle
		fail : 	返回NULL
*/
//extern crs_file_handler_t* crs_file_create(const int8_t *file_name, file_mode_e mode);


 /*
	function : 
		以mode方式打开文件，文件类型为file_type	，如果文件不存在，且mode为fmode_w或者fmode_a时，会创建新的文件
		fmode :
			fmode_r : 只读模式打开文件
			fmode_w : 写模式打开文件（同时可以读）
			fmode_a : 追加模式打开文件；如果文件存在，直接打开文件
										如果文件不存在，则需要创建新文件
	input : 
		const char *file_name : 字符串型文件名
		file_mode_e mode ：操作文件的模式
	return value : 
		success :	返回文件的控制handle
		fail : 	返回NULL
*/
extern crs_file_handler_t* crs_file_open(crs_file_handler_t *file, file_mode_e mode);

  /*
	function :
		从file中读取数据到buf[0:n)中
	input :
		crs_file_handler_t *file : 文件控制handle，内部指向文件描述符
		int8_t *buf ：存储所读取数据的缓存
		uint32_t n ： 所需要读取的字节数
	return value : 
		success : 返回 0，表示已经读取0个字节，返回正数，表示读取到的字节数
		fail : 返回 -1：表示读取发生错误 
*/
extern int32_t crs_file_read(crs_file_handler_t *file, int8_t *buf, uint32_t n);

  /*
	function :
		向file中写入buf[0:n)
	input :
		crs_file_handler_t *file ： 文件控制handle，内部指向文件描述符
		int8_t *buf ：存储所要写入的数据的缓存
		uint32_t n ： 写入的字节数
	return value : 
		success : 返回值为0：表示没有写入数据， 返回值为正数：表示写入的字节数
 		fail : 返回值为-1：表示写入发生错误
*/
extern int32_t crs_file_write(crs_file_handler_t *file, int8_t *buf, uint32_t n);
  /*
	function :
		获取文件的信息
	input :
		crs_file_handler_t *file : 文件控制handle
		file_info_t *info : 描述文件的结构体
	return value :
		success : 将file指针指向的文件的相关的信息赋值到file_info结构体中,同时返回1
		fail : 返回 0
*/
extern int32_t crs_file_get_info(crs_file_handler_t *file, file_info_t *info);
 /*
	function :
		从whence处算起,移动文件读写指针到文件的离whence第pos个字节处
	input :
		crs_file_handler_t *file : 文件控制handle
		uint32_t pos : 
			
	return value :
		success : 文件指针指向
		fail : 返回0
*/
extern int32_t crs_file_seek(crs_file_handler_t *file, int32_t pos, int32_t whence);

  /*
	function :
		关闭文件
	input :
		crs_file_handler_t *file : 文件控制handle
	return value :
		success : 返回 1
		fail : 返回 0
*/
extern int32_t crs_file_close(crs_file_handler_t *file);


#ifdef __cplusplus
extern "C"
{
#endif

#endif