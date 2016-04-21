/*
*rand 
*随机数生成函数
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
		设置随机数种子
	input : 
		uint32_t seed : 设置的随机数种子
	return value :	无
*/
void crs_srand(uint32_t seed);
/*
	function : 
		产生一个随机数
		当有crs_rand函数进行播种时，获得通过crs_rand所播的种子产生的随机数
		若无crs_rand函数进行播种，默认调用crs_rand(1)，然后获得所产生的随机数
	input : 
		NULL
	return value : 
		返回一个随机数[0 ~ RAND_MAX]
		
*/
int32_t crs_rand( void );


#ifdef __cplusplus
}
#endif

#endif /*end of CRS_RAND_H*/
