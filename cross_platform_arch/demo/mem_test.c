
/*******************************************************************
*					内存管理API测试
********************************************************************/

#include "crs_mem.h"
#include "crs_types.h"
#include "crs_debug.h"
#include "crs_str.h"

void mem_test()
{
	int i = 0;
	int8_t *str[10];
	int8_t *ret = NULL;
	int8_t *str_t = "abcdefghijklmnopqrstuvwxyz";
//crs_malloc
	for(i = 0; i < 10; i ++)
	{
		str[i] = (int8_t *)crs_malloc(64);
		if(NULL == str[i])
		{
			crs_dbg("crs_malloc failed : %d\r\n",i);
		}
	}
//crs_memset
	for(i = 0;i < 10;i ++)
	{
		ret = crs_memset(str[i], i, sizeof(str[i]));
		if(NULL == ret )
		{
			crs_dbg( "crs_memset failed : %d\r\n",i);
		}
	}
//crs_memcpy
	for(i = 0;i < 10;i ++)
	{
		ret = crs_memcpy(str[i], str_t, i+5);
		if(NULL == ret)
		{
			crs_printf("crs_memcpy failed : %d\r\n",i);
		}
	}
//crs_printf
	for(i = 0;i < 10;i ++)
	{
		crs_printf("str[%d] : %s\r\n", i, str[i]);
	}
//crs_free
	for(i = 0;i < 10;i ++)
	{
		crs_free(str[i]);
	}
	printf("if no falied print,mem APIs OK\r\n");
}

int main()
{
	crs_printf("*********************** mem API test ***********************\r\n")
	mem_test();
	return 0;
}
