/*
*rand 
*��������ɺ���
*/
#ifndef CRS_RAND_H
#define CRS_RAND_H
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifdef __cplusplus
extern "C" {
#endif
/*
	function : 
		�������������			
	input : 
		uint32_t seed : ���õ����������
	return value :	��	
*/
void crs_srand(uint32_t seed);
/*
	function : 
		����һ�������
		����crs_rand�������в���ʱ�����ͨ��crs_rand���������Ӳ����������
		����crs_rand�������в��֣�Ĭ�ϵ���crs_rand(1)��Ȼ�����������������
	input : 
		NULL
	return value : 
		����һ�������[0 ~ RAND_MAX]
		
*/
int32_t crs_rand( void );


#ifdef __cplusplus
}
#endif

#endif /*end of CRS_RAND_H*/