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

typedef crs_socket_handler_t crs_tcp_socket_handler_t;

typedef crs_socket_handler_t crs_udp_socket_handler_t;
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
		该函数用来监视文件fd集合内部的一些状态
	input : 
		select crs_tcp_socket_handler_t *fd[]，timeout_usec = 0表示阻塞，timeout_usec ！= 0表示超时的时间
		当readfds ！= NULL, writefds和exceptfds均为NULL时，表示fd集合中有可读文件
		当writefds ！= NULL, readfds和exceptfds均为NULL时，表示fd集合有可写文件
		当exceptfds ！= NULL，writefds和readfds均为NULL时，表示监视fd集合文件错误异常
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_select(crs_socket_handler_t *fd[], crs_fd_set_t *readfds, crs_fd_set_t *writefds, crs_fd_set_t *exceptfds, uint32_t *timeout_usec);
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
extern void crs_fd_clr(crs_tcp_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
		判断fd是否在相应的set中			
	input : 
		文件集合crs_fd_set_t *set
		待判断的crs_tcp_socket_handler_t *fd		
	return value : 
		success :	
		fail : 	
*/
extern int32_t crs_fd_isset(crs_tcp_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
		将fd添加到set中			
	input : 
		文件集合crs_fd_set_t *set
		待添加的crs_tcp_socket_handler_t *fd
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_set(crs_tcp_socket_handler_t *fd, crs_fd_set_t *set);
/*
	function : 
		将文件集合清空 			
	input : 
		crs_fd_set_t *set ： 文件集合
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_zero(crs_fd_set_t *set);
<<<<<<< HEAD
/*
	function : 
		把一个本地协议地址赋予一个socket;
		对于网际协议,协议地址是32位的ipv4或者128位的ipv6地址与16位的TCP或UDP端口号的组合.			
	input : 
		crs_tcp_socket_handler_t *sock : socket控制handle
		char *ip ： 需要绑定的IP地址
					如果ip == NULL ：绑定默认的IP地址
		uint16_t port ： 需要绑定的端口
	return value : 
		success :	返回 0
		fail : 	返回 -1
*/
extern int32_t crs_bind(crs_tcp_socket_handler_t *sock, char *ip, uint16_t port);
=======
>>>>>>> 363c4997f66ae540007ea2dfec8742b285595d6d

/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
typedef struct crs_sock_info_s {
    int8_t local_ip[16];
    int8_t peer_ip[16];
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
extern int32_t crs_getsock_info(crs_tcp_socket_handler_t *sock, crs_sock_info_t *sock_info);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int8_t* crs_gethostbyname(const int8_t *name, int8_t *ip, const size_t ip_size);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern int8_t* crs_inet_ntoa(const uint32_t ip, int8_t *str_ip, uint32_t str_ip_size);
/*
	function : 
					
	input : 
	return value : 
		success :	
		fail : 	
*/
extern uint32_t crs_inet_aton(const int8_t* ip);
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
extern crs_tcp_socket_handler_t* crs_tcp_socket_create();

/*
<<<<<<< HEAD
	function : 
		监听函数，把一个未连接的socket转换成一个被动的socket，指示内核应接受指向该socket的连接请求		
	input : 
		crs_tcp_socket_handler_t *sock ： socket handle
		uint32_t backlog ： 内核所维护的socket两个队列，已完成连接的队列和未完成连接的队列的和的最大值
	return value : 
		success :	返回 0 
		fail : 	返回 -1
*/
extern int32_t crs_listen(crs_tcp_socket_handler_t *sock, uint32_t backlog);
/*
	function : 
		由TCP服务器调用，用于从已完成连接的队列的头返回下一个已完成连接			
	input : 
		crs_tcp_socket_handler_t *sock ： socket handle
	return value : 
		success :	返回 所接收的socket
		fail : 	返回 -1
*/
extern crs_tcp_socket_handler_t *crs_accept(crs_tcp_socket_handler_t *sock);
=======
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
>>>>>>> 363c4997f66ae540007ea2dfec8742b285595d6d

/*
 * socket连接到服务器(ip+port，ip是以'\0'结尾的字符串)，超时时间为timeout_usec微秒
 * 返回值为0：表示连接成功
 * 返回值为-1：表示连接失败
 */
 /*
	function : 
		socket连接到服务器		
	input : 
		crs_tcp_socket_handler_t *sock ： socket handle
		int8_t *ip : 服务器的IP地址，点分十进制表示
		uint16_t port ：服务器的端口号
		uint32_t timeout_usec　：　０表示阻塞，非０表示超时时间
	return value : 
		success : 返回０
		fail : 	返回 -1
*/
extern int32_t crs_tcp_connect(crs_tcp_socket_handler_t *sock, int8_t *ip, uint16_t port, uint32_t timeout_usec);

 /*
	function : 
		从socket中接收数据到buf[0:n)中，超时时间为timeout_usec微秒			
	input : 
		crs_tcp_socket_handler_t *sock　：　socket handle
		void *buf ： 存储所接收数据的buffer
		uint32_t n ：指示第二个参数buf的长度
	return value : 
		success :	返回所接收到的字符的数量，0表示没接收到数据	
		fail : 	返回-1，表示连接断开
*/
extern int32_t crs_tcp_recv(crs_tcp_socket_handler_t *sock, void *buf, uint32_t n);

 /*
	function : 
		发送数据buf[0:n)			
	input : 
		crs_tcp_socket_handler_t *sock ： socket handle
		void *buf ： 发送的字符串
		uint32_t n ：指示第二个参数buf的长度
	return value : 
		success :	返回所发送的数据的长度
		fail : 	返回-1，表示连接断开
*/
extern int32_t crs_tcp_send(crs_tcp_socket_handler_t *sock, void *buf, uint32_t n);

 /*
	function : 
		销毁 tcp socket			
	input : 
		crs_tcp_socket_handler_t *sock ： socket handle
	return value : 无
		success :	
		fail : 	
*/
extern void crs_tcp_socket_destroy(crs_tcp_socket_handler_t *sock);



/*************************** udp 接口 *********************************/

/*
 * 创建udp socket，绑定端口到port，（为了加快近场搜索，建议设置socket支持发送广播包, 组播包）
 * 注意port为本机字节序
 */
 /*
	function : 
		创建一个UDP socket			
	input : 无
	return value : 
		success : 返回新创建的 udp socket	
		fail : 	返回NULL
*/
extern crs_udp_socket_handler_t* crs_udp_socket_create();

  /*
	function : 
		加入组播组			
	input : 
		crs_udp_socket_handler_t *sock ： socket handle
		int8_t *ip : 组播的ip地址
	return value : 
		success :	返回 0
		fail : 	返回 -1
*/
extern int32_t crs_udp_socket_join_multicast(crs_udp_socket_handler_t *sock, int8_t *ip);


 /*
	function : 
		接收数据			
	input : 
		crs_udp_socket_handler_t *sock ：socket handle
		int8_t *ip ： peer的ip
		uint32_t ip_len ： 指示第二个参数ip的长度
		uint16_t *port ： peer的端口
		void *buf ：所接收到的来自peer的数据
		uint32_t n ： 所接收到的来自peer的数据的长度

	return value : 
		success :	成功返回所接收到的数据的长度
		fail : 	返回 -1
*/
extern int32_t crs_udp_recvfrom(crs_udp_socket_handler_t *sock, int8_t *ip, uint32_t ip_len, uint16_t *port, void *buf, uint32_t n);

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
		发送数据			
	input : 
		crs_udp_socket_handler_t *sock ： socket handle
		int8_t *ip ： peer的ip
		uint16_t port ：peer的端口
		void *buf ：发送给peer的数据
		uint32_t n ： 指示第四个参数buf的长度
	return value : 
		success :	返回发送的数据的长度
		fail : 	返回-1
*/
extern int32_t crs_udp_sendto(crs_udp_socket_handler_t *sock, int8_t *ip, uint16_t port, void *buf, uint32_t n);
/*
 * 销毁 udp socket
 */
 /*
	function : 
		销毁 udp socket			
	input : 
	return value : 
		success :	
		fail : 	
*/
extern void crs_udp_socket_destroy(crs_udp_socket_handler_t *sock);


#ifdef __cplusplus
extern "C"
{
#endif
#endif
