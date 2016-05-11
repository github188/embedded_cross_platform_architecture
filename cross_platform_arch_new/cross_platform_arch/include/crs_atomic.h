#ifndef _CRS_ATOMIC_H_
#define _CRS_ATOMIC_H_
 /*
	function :

	input :
	return value :
		success :
		fail :
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
		ԭ�ӵĸ�ֵ,��ptr��ָ�������ԭ�ӵĸ�ֵΪval
	input :
		void *ptr : ԭ�Ӳ����Ķ���
		int32_t val : �����õ�ֵ
	return value :
		success :
		fail :
*/
extern int32_t crs_atomic_set(void *ptr, int32_t val);
  /*
	function :
		ԭ�ӵļӻ��߼�,��ptr��ָ������ݽ���ԭ�ӵ����ӻ��߼�Сval(valΪ����ʱΪ+,����ʱΪ-)
	input :
		void *ptr : ԭ�ӼӵĶ���
		int val : ԭ�Ӽӵ�ֵ
	return value : 
		success :
		fail :
*/
extern int32_t crs_atomic_add(void *ptr, int32_t val);

/*
 * ��������� ��һ���������������(�����һ�κ�̶�)
 */
  /*
	function :
		ԭ������
	input :
		void *ptr : ԭ������1�Ķ���
	return value :
		success :
		fail :
*/
extern int32_t crs_atomic_auto_inc(void *ptr);
  /*
	function :
		ԭ���Լ�
	input :
		ԭ���Լ�1�Ķ���
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
