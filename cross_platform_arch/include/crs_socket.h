/*
*crs_socket.h
*socket management
*socket通信
*/

/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
#ifndef _CRS_SOCK_H_
#define _CRS_SOCK_H_

#ifdef LITE_OS
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/types.h>
	#elif defined TI_RTOS
	#include "socket.h"
#elif defined UCOS_II
	#include "includes.h"
	#include "sockets.h"
	#include "inet.h"
	#include "netdb.h"
#else
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/types.h>

//#include <netdb.h>
//#include <arpa/nameser.h>
//#include <resolv.h>
//#include <netinet/in.h>
//#include <netinet/tcp.h>
//#include <arpa/inet.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * TCP socket，这里read与write函数，开发者可以实现为阻塞或非阻塞模式，SDK并不关心
 * 内部维系了read与write，不关心具体实现是否阻塞
 */
 
/*
	function : 
		socket handler			
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_socket_handler crs_socket_handler_t;

/*
	function : 
		crs_fd_set 			
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_fd_set  crs_fd_set_t;

/*
	function : 
		该函数是用来监视文件fd集合内部的一些状态的
	input : 
		select crs_socket_handler_t *fd[]，timeout_usec = 0表示阻塞，timeout_usec ！= 0表示超时的时间
		当readfds ！= NULL, writefds和exceptfds均为NULL时，表示fd集合中有可读文件
		当writefds ！= NULL, readfds和exceptfds均为NULL时，表示fd集合有可写文件
		当exceptfds ！= NULL，writefds和readfds均为NULL时，表示监视fd集合文件错误异常
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_select(crs_socket_handler_t *fd[], uint32_t size, crs_fd_set_t *readfds, crs_fd_set_t *writefds, crs_fd_set_t *exceptfds, uint32_t *timeout_usec);
/*
	function : 
		创建文件集合			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern crs_fd_set_t * crs_fd_set_create();
/*
	function : 
		销毁文件集合crs_fd_set_t handler			
	input : 
		crs_fd_set_t *set ： 文件集合
	return value : 
		success : 返回 0	
		fail : 	
*/
extern int32_t crs_fd_set_destroy(crs_fd_set_t *set);
/*
	function : 
		清除文件集合中的一个fd			
	input : 
		文件集合crs_fd_set_t *set
		需要清除的fd
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_clr(crs_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
		判断fd是否在相应的set中			
	input : 
		文件集合crs_fd_set_t *set
		待判断的crs_socket_handler_t *fd		
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_fd_isset(crs_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
		将fd添加到set中			
	input : 
		文件集合crs_fd_set_t *set
		待添加的crs_socket_handler_t *fd
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_set(crs_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_zero(crs_fd_set_t *set);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_bind(crs_socket_handler_t *sock, uint16_t port);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_listen(crs_socket_handler_t *sock, uint32_t backlog);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern crs_socket_handler_t *crs_accept(crs_socket_handler_t *sock);

/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_sock_info_s {
    char local_ip[16];
    char peer_ip[16];
    uint16_t local_port;
    uint16_t peer_port;
    uint32_t sock_type;
}crs_sock_info_t;
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_getsock_info(crs_socket_handler_t *sock, crs_sock_info_t *sock_info);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern char* crs_gethostbyname(const char *name, char *ip, const size_t ip_size);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern char* crs_inet_ntoa(const uint32_t ip, char *str_ip, uint32_t str_ip_size);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint32_t crs_inet_addr(const char* ip);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint32_t crs_htonl(uint32_t hostlong);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint16_t crs_htons(uint16_t hostlong);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint32_t crs_ntohl(uint32_t netlong);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint16_t crs_ntohs(uint16_t netlong);

//#define SOCK_STREAM 1
//#define SOCK_DGRAM  0

/*************************** tcp 接口 *********************************/

/*
 * 创建tcp socket
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern crs_socket_handler_t* crs_tcp_socket_create();


/*
 * socket连接到服务器(ip+port，ip是以'\0'结尾的字符串)，超时时间为timeout_usec微秒
 * 返回值为0：表示连接成功
 * 返回值为-1：表示连接失败
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_tcp_connect(crs_socket_handler_t *sock, char *ip, uint16_t port, uint32_t timeout_usec);


/*
 * 从socket中接收数据到buf[0:n)中，超时时间为timeout_usec微秒
 * 返回值为-1：表示连接断开
 * 返回值为0：表示在timeout_usec时间内没有收到数据
 * 返回值为正数：表示读收到的字节数
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_tcp_recv(crs_socket_handler_t *sock, void *buf, uint32_t n, uint32_t timeout_usec);

/*
 * 发送数据buf[0:n)，超时时间为timeout_usec微秒
 * 返回值为-1：表示连接断开
 * 返回值为0：表示在timeout_usec时间内没有发送数据
 * 返回值为正数：表示发送的字节数
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_tcp_send(crs_socket_handler_t *sock, void *buf, uint32_t n, uint32_t timeout_usec);

#if 1
/*
 * 销毁 tcp socket
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_tcp_socket_destroy(crs_socket_handler_t *sock);
#endif



/*************************** udp 接口 *********************************/

/*
 * 创建udp socket，绑定端口到port，（为了加快近场搜索，建议设置socket支持发送广播包, 组播包）
 * 注意port为本机字节序
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern crs_socket_handler_t* crs_udp_socket_create();

/*
 * 加入组播组
 */
extern int32_t crs_udp_socket_join_multicast(crs_socket_handler_t *sock, char *ip);

/*
 * 接收数据，超时时间为timeout_usec微秒
 * ip: 用于保存对端ip, ip_len为ip缓冲区大小，ip为大端模式的字符串
 * port: 用于保存对端port，注意port为本机字节序
 * 接收到的数据写入到buf[0,n)中
 *
 * 返回值为-1：表示出错
 * 返回值为0：表示在timeout_usec时间内没有接收到数据
 * 返回值为正数：表示接收到的字节数
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_udp_recvfrom(crs_socket_handler_t *sock, char *ip, uint32_t ip_len, uint16_t *port, void *buf, uint32_t n, uint32_t timeout_usec);

/*
 * 向ip:port发送数据：buf[0,n)， 超时时间为timeout_usec微秒
 * 注意port为本机字节序
 *
 * 返回值为-1：表示表示出错
 * 返回值为0：表示在timeout_usec时间内没有写入数据
 * 返回值为正数：表示发送的字节数
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_udp_sendto(crs_socket_handler_t *sock, char *ip, uint16_t port, void *buf, uint32_t n, uint32_t timeout_usec);

#if 1
/*
 * 销毁 udp socket
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_udp_socket_destroy(crs_socket_handler_t *sock);
#endif

/*
 * 销毁 socket
 */
 /*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_socket_destroy(crs_socket_handler_t *sock);

//ntohl/ntohs htons htonl


//inet_ntop/inet_ntoa 


#ifdef __cplusplus
extern "C"
{
#endif
#endif
