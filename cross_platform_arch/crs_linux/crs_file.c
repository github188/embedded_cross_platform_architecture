/*				linux
 * crs_file.c
*file management
*文件操作
*/

#include "crs_types.h"
#include "crs_mem.h"
#include "crs_file.h"

#include <fcntl>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define STR_LEN 60
/*
	SEEK_SET,SEEK_CUR,SEEK_END三个宏定义是用于crs_file_seek函数的第三个参数whence的，表示偏移量的相对的位置
	
	SEEK_SET表示从文件头开始算起
	SEEK_CUR表示从文件指针当前位置开始
	SEEK_END表示从文件末尾位置算起
*/

/************************ file 接口 *********************************/

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
		open ("helloq.txt", O_RDWR | O_CREAT , S_IRUSR | S_IWUSR)
*/
extern crs_file_handler_t* crs_file_open(const int8_t *file_name, file_mode_e mode)
{
	crs_file_handler_t *file_handle = (crs_file_handler_t *)crs_malloc(sizeof(crs_file_handler_t));
	crs_memcpy( file_handle -> finfo -> file_name, file_name, crs_strlen(file_name));
	file_handle -> finfo -> file_name_len = crs_strlen(file_name);

	if( NULL == file_name )
	{
		crs_dbg(" file name is NULL\r\n");
		return NULL;
	}
	if( fmode_r == mode )
	{
		if( -1 == ( *( file_handle  -> fd) = open( file_name, O_RDONLY ,  S_IRUSR | S_IWUSR) ))
		{
			crs_dbg( "open file failed\r\n");
			crs_free(file_handle);
			return NULL;
		}
		 file_handle ->finfo -> write_pos = 0;
		 file_handle -> finfo -> read_pos = 0;
	}
	else if( fmode_w == mode)
	{
		if( -1 == ( *( file_handle  -> fd) = open(file_name, O_WRONLY , S_IRUSR | S_IWUSR) ) )
		{
			crs_dbg( "open file failed\r\n");
			crs_free(file_handle);
			return NULL;
		}
		 file_handle ->finfo -> write_pos = 0;
		 file_handle -> finfo -> read_pos = 0;
	}
	else if(fmode_a == mode)
	{
		if( -1 == ( *( file_handle  -> fd) = open(file_name, O_APPEND | O_CREAT, S_IRUSR | S_IWUSR) ) )
		{
			crs_dbg( "open file failed\r\n");
			crs_free(file_handle);
			return NULL;
		}
		 file_handle ->finfo -> write_pos = 0;
		 file_handle -> finfo -> read_pos = 0;
	}
}

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
extern int32_t crs_file_read(crs_file_handler_t *file, int8_t *buf, uint32_t n)
{
	if(file -> finfo -> read_pos >=  file -> finfo -> file_size)
	{
		return 0;
	}
	int32_t ret = read( *( file_handle  -> fd), buf, n);
	if(-1 == ret)
	{
		crs_dbg("read file failed\r\n");
		return -1;
	}

	file -> finfo -> read_pos += ret;
	return ret;
}

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
extern int32_t crs_file_write(crs_file_handler_t *file, int8_t *buf, uint32_t n)
{
	int ret = write (  *( file_handle  -> fd), buf, n);
	if( -1 == ret )
	{
		crs_dbg( "write file failed\r\n");
		return -1;
	}
	file -> finfo -> write_pos += ret;
	file->finfo->file_size += ret;
	return ret;
}
  /*
	function :
		获取文件的信息
	input :
		crs_file_handler_t *file : 文件控制handle
		file_info_t *info : 描述文件的结构体
	return value :
		success : 将file指针指向的文件的相关的信息赋值到file_info结构体中,同时返回0
		fail : 返回 -1
*/
extern int32_t crs_file_get_info(crs_file_handler_t *file, file_info_t *finfo)
{
	file_info_t *finfo_t = crs_malloc( sizeof( file_info_t ));

	if(NULL == file || NULL == file -> finfo)
	{
		crs_dbg("file info is NULL\r\n");
		return -1;
	}
	crs_memcpy( finfo, file -> finfo);
	return 0;
}
 /*
	function :
		从whence处算起,移动文件读写指针到文件的离whence第pos个字节处
	input :
		crs_file_handler_t *file : 文件控制handle
		uint32_t pos : 
			
	return value :
		success : 0
		fail : 返回-1
*/
extern int32_t crs_file_seek(crs_file_handler_t *file, int32_t pos, int32_t whence)
{
	int64_t fromwhere = 0;
	switch(whence)
	{
		case 0: fromwhere = 0;		break;				//从文件头开始算位置
		case 1:	fromwhere = file -> finfo -> read;	break;//从当前位置处算
		case 2:	fromwhere = file -> file_size;		break;//从文件末尾开始算
		default: crs_dbg("whence is beyond 0,1,2\r\n"); from_where = file -> file_size; break;
	}

	if(pos + fromwhere < 0 )
	{
		return (-1);
	}
	if (pos + fromwhere > file-> finfo -> file_size)
	{
		file->finfo->write_pos = file->finfo->file_size;
		file->finfo->read_pos = file->finfo->file_size;
		return 0;
	}
	else
	{
		file->finfo->write_pos = pos + fromwhere;
		file->finfo->read_pos = pos + fromwhere;
		return 0;
	}
}

  /*
	function :
		关闭文件
	input :
		crs_file_handler_t *file : 文件控制handle
	return value :
		success : 返回 1
		fail : 返回 0
*/
extern int32_t crs_file_close(crs_file_handler_t *file)
{

	if (file == NULL || -1 == close( *( file_handle  -> fd) ) )
	{
		crs_dbg("file NULL or file close filed\r\n");
	}
	crs_free( file -> info );
	crs_free( file );
}

