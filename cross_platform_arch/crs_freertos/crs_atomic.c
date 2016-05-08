/*			FreeRTOS
 * crs_atomic.c
 * 原子操作，原子性的加减操作
 */
#include "crs_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

 /*
	function :
			
	input :
	return value :
		success :
		fail :
*/
//extern void crs_sync();
   /*
	function :
		原子的赋值,对ptr所指向的数据原子的赋值为val
	input :
		void *ptr : 原子操作的对象
		int32_t val : 所设置的值
	return value :
		success :
		fail :
*/
extern int32_t crs_atomic_set(void *ptr, int32_t val);
  /*
	function :
		原子的加或者减,对ptr所指向的数据进行原子的增加或者减小val(val为正数时为+,负数时为-)
	input :
		void *ptr : 原子加的对象
		int val : 原子加的值
	return value : 
		success :
		fail :
*/
extern int32_t crs_atomic_add(void *ptr, int32_t val);

/*
 * 随机数自增 对一个随机数进行自增(随机数一次后固定)
 */
  /*
	function :
		原子自增
	input :
		void *ptr : 原子自增1的对象
	return value :
		success :
		fail :
*/
extern int32_t crs_atomic_auto_inc(void *ptr);
  /*
	function :
		原子自减
	input :
		原子自减1的对象
	return value :
		success :
		fail :
*/
extern int32_t crs_atomic_auto_dec(void *ptr);


#ifdef __cplusplus
extern "C"
{
#endif
#endif
