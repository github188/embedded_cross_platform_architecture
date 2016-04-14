/*
*file management
*文件操作
*//*
 * Copyright(c)  Shen zhen Danale Telecommunication Corp.
 *
 * Authored by Liao yangyang on: 2015年 09月 11日 星期五 17:05:50 CST
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crs_file.h"
#include "crs_types.h"

struct crs_file_handler_s {
    int * fp;
    file_info_t info;
};
/*
	function :

	input :
	return value :
		success :
		fail :
*/
#if 0
extern crs_file_handler_t* crs_file_open(const char *file_name, file_mode_t mode)
{
    crs_file_handler_t *file = (crs_file_handler_t *)crs_malloc(sizeof(crs_file_handler_t));
	file->fp = (int *)crs_malloc(sizeof(int)*3);	//handle,  w_offset,r_offset
	SlFsFileInfo_t  pFsFileInfo;
	int token=0;
    if (NULL == file) {
        return NULL;
    }

    if (fmode_r == mode) {
         sl_FsOpen(file_name,FS_MODE_OPEN_READ,0,&(file->fp[0]));
		 file->fp[1] = 0;
		 file->fp[2] = 0;
    } else if (fmode_w == mode) {
   	     if(sl_FsOpen(file_name, FS_MODE_OPEN_WRITE, &token, &(file->fp[0]))==0){
		 	    sl_FsClose(file->fp[0],NULL,0,0);
				sl_FsDel(file_name,0);
			}
			sl_FsOpen(file_name, FS_MODE_OPEN_CREATE(65536, _FS_FILE_OPEN_FLAG_COMMIT|_FS_FILE_PUBLIC_WRITE),&token,&(file->fp[0]));
			file->fp[1] = 0;
			file->fp[2] = 0;

    } else if (fmode_a == mode) {
          if(sl_FsOpen(file_name, FS_MODE_OPEN_WRITE, &token, &(file->fp[0]))<0){
				sl_FsOpen(file_name, FS_MODE_OPEN_CREATE(65536, _FS_FILE_OPEN_FLAG_COMMIT|_FS_FILE_PUBLIC_WRITE),&token,&(file->fp[0]));
			};
			if(sl_FsGetInfo(file_name,token, &pFsFileInfo)<0){

					mem_Free((void *)(file->fp));
					mem_Free(file);
					return NULL;
			}

			file->fp[1] = pFsFileInfo.FileLen;
			file->fp[2] = 0;
    }

    file->info.file_name_len = strlen(file_name);
    strncpy(file->info.file_name, file_name, file->info.file_name_len);
	file->info.file_size = pFsFileInfo.FileLen;
	return file;

}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_file_read(crs_file_handler_t *file, uint8_t *buf, uint32_t n)
{
     int val;
	 val =0;
	 if(file->fp[2] >=  file->info.file_size){
	 	return 0;
	 	}
      val = sl_FsRead(file->fp[0],file->fp[2],buf,n);
	  if(val < 0){
		return  (-1);
	  }

	  file->fp[2] += val;
	  return val;
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_file_write(crs_file_handler_t *file, uint8_t *buf, uint32_t n)
{
	int val=0;
	val = sl_FsWrite(file->fp[0],file->fp[1],buf,n);
	if( val< 0){
				return (-1);
	}

	file->fp[1] +=val;
	file->info.file_size += val;
    return  val;
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_file_get_info(crs_file_handler_t *file, file_info_t *info)
{
    memcpy(info, &file->info, sizeof(file_info_t));
    return 0;
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_file_seek(crs_file_handler_t *file, uint32_t pos)
{
    if(pos < 0){
		return (-1);
    }
    if (pos > file->info.file_size) {
		file->fp[1] = file->info.file_size;
		file->fp[2] = file->info.file_size;
        return 0;
    } else {
        file->fp[1] = pos;
		file->fp[2] = pos;
		return 0;
	}
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_file_close(crs_file_handler_t *file)
{
    sl_FsClose(file->fp[0],0,0,0);
	mem_Free(file->fp);
	mem_Free(file);
    return 0;
}
#endif

