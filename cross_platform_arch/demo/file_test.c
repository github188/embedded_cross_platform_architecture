
/*******************************************************************
*					file API demo
********************************************************************/
#include "crs_types.h"
#include "crs_mem.h"
#include "crs_debug.h"
#include "crs_str.h"
#include "crs_file.h"


void file_test()
{
	int8_t *buf = "abcdefghijklmnopqrstuvwxyz";
	int8_t *context_buf = NULL;
	file_info_t finfo;

	crs_file_handler_t *fhp = crs_file_open( "file_test", fmode_a);
	if(NULL == fhp)
	{
		crs_dbg("file test crs_file_open failed\r\n");
		return ;
	}
	if ( -1 == crs_file_write(fhp, buf, crs_strlen(buf)) )
	{
		crs_dbg("file_test crs_file_write failed\r\n");
		return ;
	}

	if ( -1 == crs_file_seek( fhp, SEEK_SET, 0) )
	{
		crs_dbg("file_test crs_file_seek failed\r\n");
		return ;
	}

	if( -1 == crs_file_read( fhp, context_buf, 10) )
	{
		crs_dbg("file test crs_file_read failed\r\n");
		return ;
	}
	else
	{
		crs_printf("read from file : %s", context_buf);
	}

	crs_memset(&finfo, 0, sizeof(finfo));
	if( -1 == crs_file_get_info(fhp, &finfo) )
	{
		crs_dbg("file test crs_file_get_info failed\r\n");
		return ;
	}
	else
	{
		crs_printf("file info :\r\n file_name : %s\r\n, file_size : %d\r\n,read_pos : %d\r\n,write_pos : %d\r\n",
				finfo.file_name, finfo.file_size, finfo.read_pos, finfo.write_pos);
	}
}

int main()
{
	crs_printf("crs_file API test demo and how to use demo\r\n");
	void file_test();
	return 0;
}
