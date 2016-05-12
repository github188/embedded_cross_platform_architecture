/*					linux
*crs_socket.c
*socket management
*socket通信
*/
#include "crs_types.h"
#include "crs_mem.h"
#include "crs_socket.h"
#include "crs_time.h"


#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
 
struct crs_socket_handler {
    int32_t fd;
    int32_t sock_type;
    crs_sock_info_t sock_info;
};
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
struct crs_fd_set {
    fd_set fds;
};

/*
	function : 
		该函数用来监视文件fd集合内部的一些状态
	input : 
		select crs_socket_handler_t *fd[]，timeout_usec = 0表示阻塞，timeout_usec ！= 0表示超时的时间
		当readfds ！= NULL, writefds和exceptfds均为NULL时，表示fd集合中有可读文件
		当writefds ！= NULL, readfds和exceptfds均为NULL时，表示fd集合有可写文件
		当exceptfds ！= NULL，writefds和readfds均为NULL时，表示监视fd集合文件错误异常
	return value : 
		success :	0表示超时时间内没有数据,正值表示成功
		fail : 	-1
*/
extern int32_t crs_select(int32_t maxfd, crs_fd_set_t *readfds, crs_fd_set_t *writefds, crs_fd_set_t *exceptfds, uint32_t *timeout_usec)
{
    uint32_t count = 0;
    struct timeval delay;
    crs_memset(&delay, 0, sizeof(struct timeval));
    	delay.tv_sec = *timeout_usec / 1000000;
    	delay.tv_usec = *timeout_usec % 1000000;
    if( readfds == NULL || writefds == NULL || exceptfds == NULL )
    {
    	crs_dbg("all fds are NULL\r\n");
    	return ;
    }
    return select(max_fd + 1, &(readfds->fds), &(writefds->fds), &(exceptfds->fds), &delay);
}

/*
	function : 
		创建文件集合			
	input : 
		无
	return value : 
		success :	返回新创建的crs_fd_set结构体地址
		fail : 	NULL
*/
extern crs_fd_set_t * crs_fd_set_create()
{
    crs_fd_set_t *set = (crs_fd_set_t *)crs_malloc(sizeof(crs_fd_set_t));
    if( NULL == set)
    {
    	crs_dbg("crs_fd_set_create malloc failed\r\n");
    	return NULL;
    }
    crs_memset(set, 0, sizeof(crs_fd_set_t));
    return set;
}
/*
	function : 
		销毁文件集合crs_fd_set_t handler			
	input : 
		crs_fd_set_t *set ： 文件集合
	return value : 
		success :  0
		fail : 	-1
*/
extern int32_t crs_fd_set_destroy( crs_fd_set_t *set )
{
    if ( NULL == set )
    {
        return -1;
    }
    crs_free( set );
    set = NULL;
    return 0;
}
/*
	function : 
		清除文件集合中的一个fd			
	input : 
		文件集合crs_fd_set_t *set
		需要清除的fd
	return value : 无
		success :	
		fail : 	
*/
extern void crs_fd_clr(crs_socket_handler_t *fd, crs_fd_set_t *set)
{
    if (NULL == fd)
    {
        return ;
    }

    if (NULL == set)
    {
        return ;
    }

    FD_CLR(fd->fd, &(set->fds));
}
/*
	function : 
		判断fd是否在相应的set中			
	input : 
		文件集合crs_fd_set_t *set
		待判断的crs_socket_handler_t *fd
	return value : 
		success :	1
		fail : 	0
*/
extern int32_t crs_fd_isset(crs_socket_handler_t *fd, crs_fd_set_t *set)
{
    if ( NULL == fd )
    {
        return 0;
    }

    if ( NULL == set )
    {
        return 0;
    }

    return FD_ISSET( fd->fd, &( set->fds ) );
}

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
extern void crs_fd_set( crs_socket_handler_t *fd, crs_fd_set_t *set )
{
    if (NULL == fd)
    {
        return ;
    }

    if (NULL == set)
    {
        return ;
    }

    FD_SET( fd->fd, &( set->fds ) );
}
/*
	function : 
		将文件集合清空 			
	input : 
		crs_fd_set_t *set ： 文件集合
	return value : 
		success :	
		fail : 	
*/
extern void crs_fd_zero( crs_fd_set_t *set )
{
    if (NULL == set)
    {
        return ;
    }

    FD_ZERO( &( set->fds ) );
}

/*
	function : 
		获取socket的信息，即得倒crs_sock_info_t结构体内表示的信息
	input : 
		crs_socket_handler_t *sock ： scoket控制块
		crs_sock_info_t *sock_info ： socket结构体指针，函数返回时传出socket的信息
	return value : 
		success :	0
		fail : 	-1
*/
extern int32_t crs_getsock_info( crs_socket_handler_t *sock, crs_sock_info_t *sock_info )
{
    if( NULL == crs_memcpy( sock_info, &sock -> sock_info, sizeof( crs_sock_info_t ) ) )
    {
    	return -1;
    }
    return 0;
}
/*
	function : 
		对应于给定主机名的ip地址
	input : 
		const int8_t *name ：
		int8_t *ip
 	 	const size_t ip_size
	return value :
		success :	true
		fail : 	false
*/
extern int8_t crs_gethostbyname( const int8_t *name, int8_t *ip, const size_t ip_size )
{
   if (NULL == name)
   {
       crs_dbg("crs gethostbyname invalid name\n");
       return false;

   }
   if (NULL == ip)
   {
       crs_dbg("crs gethostbyname invalid ip\n");
       return false;

   }
   if (ip_size < 16)
   {
       crs_dbg("crs gethostbyname ip_size[%zd](<16) is invalid\n", ip_size);
       return false;

   }

   struct hostent *hptr = gethostbyname(name);
   if (NULL == hptr)
   {
       crs_dbg("crsgethostbyname for host %s failed: %s\n", name, strerror(errno));
       return false;
   }

   char **pptr;
   crs_dbg("crsgethostbyname %s official hostname: %s\n", name, hptr->h_name);
   for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
   {
       crs_dbg("crsgethostbyname %s alias: %s\n", name, *pptr);
   }

   switch(hptr->h_addrtype)
   {
       case AF_INET:
           // 选择最后一个IP  TODO 后期随机选择一个
           pptr = hptr->h_addr_list;
           for(; *pptr != NULL; pptr++)
           {
               crs_memset(ip, 0, ip_size);
               crs_strcpy(ip, inet_ntoa(*((struct in_addr *)*pptr)));
               crs_dbg("crsgethostbyname %s ip: %s\n", name, ip);
           }
           break;
       default:
           crs_dbg("crsgethostbyname get %s ip failed Unkonwn address type\n", name);
           return false;
   }

   return true;
}
/*
	function :
		将32位整形ip地址转换为点分十进制的字符串表示的IP地址
	input :
		unsigned int ipaddr,char * ipv4
	return value :
		success :
		fail :
*/
extern void *crs_inet_ntoa( uint32_t ipaddr)
{
	int32_t index;
	int32_t temp;
	int32_t i, k, f ,length;
	index = 3;
	i = 0;
    f = 0;

    int8_t ipv4[20] = NULL;
    int8_t *ip_str = NULL;
	 for( index = 4; index > 0; index -- )
	 {
		 temp =   ( ( ipaddr >> ( ( index-1 )*8 ) ) & 0xFF );
		 k = temp / 100;
		 if( k != 0 )
		 {
		   ipv4[i++] = ( temp / 100 ) + '0';
		 }
		 else
		 {
			 f = 1;                                      //百位为0标志
		 }
		 k = temp / 10;
		 if( k != 0 )
		 {
			ipv4[i++] = ( temp / 10 ) % 10 + '0';
		 }
		 else if( f == 0 )                               //百位不为零
		 {
			ipv4[i++] = ( temp / 10 ) % 10 +'0';
		 }

		 ipv4[i++] = ( temp % 10 ) + '0';
		 ipv4[i++] = '.';
	 }
	 length = i;
		 for( -- i; i < 16; i ++ )
		 {
			 ipv4[i] = 0;
		 }
		 ip_str =( int8_t *) crs_malloc( length );

		 crs_strncpy( ip_str, ipv4, length);
		 return ip_str;
}
/*
	function : 
		将32位整形ip地址转换为点分十进制的字符串表示的IP地址
	input : 
		const uint32_t ip : 32w位整型的IP地址
	return value : 
		success :	点分十进制的ip地址
		fail : 	返回NULL

extern int8_t* crs_inet_ntoa(const uint32_t ip)
{
	uint32_t sock_addr = 0;
    int8_t *str_ip = NULL;
    sock_addr = crs_htonl( ip );

    crs_ip_ntoa( crs_htonl( sock_addr ), str_ip );
    return str_ip;
}
*/
/*
	function : 
		将点分十进制的IP地址转换为32位的IP地址
	input : 
		const int8_t* ip ： 点分十进制表示的IP地址
	return value : 
		success :	返回转换后的32位IP地址
		fail : 	返回 -1
*/
extern uint32_t crs_inet_aton(const int8_t* ip)
{
	struct sockaddr_in addr_inet;

	if( 0 != inet_aton( ip, &add_inet.sin_addr ) )
	{
		return -1;
	}
	return addr_inet.sin_addr.s_addr;
}
/*
	function : 
		将本机字节序转换为32位的网络字节序的数
	input : 
		uint32_t hostlong ： 无符号的32位的本机字节序的数
	return value : 
		success :	返回网络字节序的数
		fail : 	else
*/
extern uint32_t crs_htonl(uint32_t hostlong)
{
	return htonl(hostlong);
}
/*
	function : 
		将本机字节序转换为16位的网络字节序的数
	input : 
		无符号的16位的本机字节序的数
	return value : 
		success :	返回网络字节序
		fail : 	else
*/
extern uint16_t crs_htons(uint16_t hostlong)
{
	return htons( hostlong );
}
/*
	function : 
		将32位的网络字节序转换为主机字节序
	input : 
		uint32_t netlong ：网络字节序
	return value : 
		success :	主机字节序
		fail : 	else
*/
extern uint32_t crs_ntohl(uint32_t netlong)
{
	return ntonl( netlong );
}
/*
	function : 
		将16位的网络字节序转为主机字节序
	input : 
		uint16_t netlong ： 网络字节序
	return value : 
		success :	主机字节序
		fail : 	else
*/
extern uint16_t crs_ntohs(uint16_t netlong)
{
	return ntohs( netlong );
}

/*************************** tcp 接口 *********************************/

/*
 * 创建tcp socket
 */
 /*
	function : 
		创建TCPsocket
	input : 无
	return value : 
		success :	返回socket控制块
		fail : 	NULL
*/
extern crs_socket_handler_t* crs_tcp_socket_create()
{
	int enable = 1;
	crs_socket_handler_t *sock = (crs_socket_handler_t *) crs_malloc(sizeof(crs_socket_handler_t));
	if (NULL == sock)
	{
		return NULL;
	}

	int32_t fd = -1;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > fd)
	{
		close(fd);
		crs_memfree(sock);
		return NULL;
	}
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1)
	{
	    return -1;
	}
    if(0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int)))
    {
    	crs_dbg("set SO_REUSEADDR failed\r\n");
    }
	sock->fd = fd;
	sock->sock_type = SOCK_STREAM;

	return sock;
}
/*
	function :
		把一个本地协议地址赋予一个socket;
		对于网际协议,协议地址是32位的ipv4或者128位的ipv6地址与16位的TCP或UDP端口号的组合.
	input :
		crs_socket_handler_t *sock : socket控制handle
		char *ip ： 需要绑定的IP地址
					如果ip == NULL ：绑定默认的IP地址
		uint16_t port ： 需要绑定的端口
	return value :
		success :	返回 0
		fail : 	返回 -1
*/
extern int32_t crs_bind( crs_socket_handler_t *sock, char *ip, uint16_t port )
{
    struct sockaddr_in local_addr;
    crs_memset( &local_addr, 0, sizeof( local_addr ) );
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = crs_htonl ( INADDR_ANY );
    local_addr.sin_port = crs_htons ( port );

    if ( bind(sock->fd, (struct sockaddr *)&local_addr, sizeof(local_addr) ) < 0) {
        return -1;
    }
    return 0;
}
/*
	function : 
		监听函数，把一个未连接的socket转换成一个被动的socket，指示内核应接受指向该socket的连接请求		
	input : 
		crs_socket_handler_t *sock ： socket handle
		uint32_t backlog ： 内核所维护的socket两个队列，已完成连接的队列和未完成连接的队列的和的最大值
	return value : 
		success :	返回 0 
		fail : 	返回 -1
*/
extern int32_t crs_listen(crs_socket_handler_t *sock, uint32_t backlog)
{
    if ( listen(sock->fd, backlog) < 0 )
    {
        return -1;
    }
    return 0;
}
/*
	function : 
		由TCP服务器调用，用于从已完成连接的队列的头返回下一个已完成连接			
	input : 
		crs_socket_handler_t *sock ： socket handle
	return value : 
		success :	返回 所接收的socket
		fail : 	返回 -1
*/
extern crs_socket_handler_t *crs_accept(crs_socket_handler_t *sock)
{
    char str_ip[16];

	memset(str_ip, 0, 16);
    crs_socket_handler_t *new_sock = ( crs_socket_handler_t * ) crs_malloc(sizeof(crs_socket_handler_t));
    if ( NULL == new_sock )
    {
        return NULL;
    }
    memset(new_sock, 0, sizeof(crs_socket_handler_t));

    struct sockaddr_in peeraddr;
    uint16_t peeraddr_len;
    new_sock->fd = accept( sock->fd, (struct sockaddr *)&peeraddr, &peeraddr_len );
    if (0 > new_sock->fd)
    {
        crs_free(new_sock);
        return NULL;
    }

    strncpy(new_sock->sock_info.peer_ip, crs_inet_ntoa(peeraddr.sin_addr.s_addr,str_ip,16), sizeof(new_sock->sock_info.peer_ip) -1);
    new_sock->sock_info.peer_port = ntohs(peeraddr.sin_port);

    return new_sock;
}

/*
 * socket连接到服务器(ip+port，ip是以'\0'结尾的字符串)，超时时间为timeout_usec微秒
 * 返回值为0：表示连接成功
 * 返回值为-1：表示连接失败
 */
 /*
	function : 
		socket连接到服务器		
	input : 
		crs_socket_handler_t *sock ： socket handle
		int8_t *ip : 服务器的IP地址，点分十进制表示
		uint16_t port ：服务器的端口号
		uint32_t timeout_usec　：　０表示阻塞，非０表示超时时间
	return value : 
		success : 返回０
		fail : 	返回 -1
*/
extern int32_t crs_tcp_connect(crs_socket_handler_t *sock, int8_t *ip, uint16_t port, uint32_t timeout_usec)
{
    int32_t fd = sock -> fd;
    struct sockaddr_in peer_addr;
	int val, timeout_ms;
	val = 0;
	timeout_ms = timeout_usec / 1000;
    crs_memset( &peer_addr, 0, sizeof( peer_addr ) );
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = crs_inet_addr( ip );
    peer_addr.sin_port = htons( port );


    while ( 1 )
    {
        val = connect( fd, ( struct sockaddr *)&peer_addr, sizeof( peer_addr ) );
		if( ( EALREADY == val ) || ( POOL_IS_EMPTY == val ) )
		{
			if(timeout_ms > 0)
			{
				timeout_ms -=5;
				crs_sleep(5);
				continue;
			}
			else
			{
				return -1;
			}
		}
		else if( val < 0 )
		{
			return ( -1 );
		}
		else
		{
			 break;
		}
    }
    return val;
}

 /*
	function : 
		从socket中接收数据到buf[0:n)中，超时时间为timeout_usec微秒			
	input : 
		crs_socket_handler_t *sock　：　socket handle
		void *buf ： 存储所接收数据的buffer
		uint32_t n ：指示第二个参数buf的长度
		uint32_t timeout_usec : 非0表示超时时间，0表示阻塞
	return value : 
		success :	返回所接收到的字符的数量，0表示没接收到数据	
		fail : 	返回-1，表示连接断开
*/
extern int32_t crs_tcp_recv(crs_socket_handler_t *sock, void *buf, uint32_t n, uint32_t timeout_usec)
{
    int32_t fd = sock->fd;
    int32_t ret;
    uint32_t len = n;
    uint8_t * recv_buf;
    recv_buf = buf;

    if (0 == timeout_usec) {
        return recv(fd, recv_buf, len, SO_NONBLOCKING);
    }

    uint32_t timeout_left = timeout_usec;
    struct timeval delay;
    while(len > 0) {
        crs_memset(&delay, 0, sizeof(struct timeval));
        delay.tv_sec = timeout_left / 1000000;
        delay.tv_usec = timeout_left % 1000000;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        ret = select(fd + 1, &fds, NULL, NULL, &delay);
        if(ret < 0)
        {
            return -1;
        }
        else if(ret == 0)
        {
			return 0;
        }
        else
        {
            if( CRS_FD_ISSET( fd, &fds ) )
            {
                timeout_left = delay.tv_sec * 1000000 + delay.tv_usec;
                ret = recv( fd, recv_buf, len, 0 );
                if( ret == EAGAIN )
                {
					crs_sleep(40);
					continue;
                }
                else if(ret < 0)
                {
					return -1;
                }
                else
                {
					return ret;
                }

            }
            else
            {
                return -1;
            }
        }
    }
    return 0;
}
 /*
	function : 
		发送数据buf[0:n)			
	input : 
		crs_socket_handler_t *sock ： socket handle
		void *buf ： 发送的字符串
		uint32_t n ：指示第二个参数buf的长度
	return value : 
		success :	返回所发送的数据的长度
		fail : 	返回-1，表示连接断开
*/
extern int32_t crs_tcp_send(crs_socket_handler_t *sock, void *buf, uint32_t n, uint32_t timeout_usec)
{
    uint32_t send_len ;
    uint8_t *send_buf;
    uint32_t ___timeout;
    int32_t fd ;
    int32_t ret=0;

	send_len = n;
	send_buf = buf;
	___timeout = timeout_usec;
	fd = sock->fd;
    //TODO 如果timeout_usec 为0 则直接进行发送一次
    if (0 == timeout_usec)
    {
		ret = send(fd, send_buf, send_len, 0);
		return ret;
    }
    while (0 != send_len)
    {
        //判断是否可写
        fd_set wset;
        struct timeval timeout;
        FD_ZERO(&wset);
        FD_SET(fd, &wset);
        timeout.tv_sec = (___timeout) / 1000000;
        timeout.tv_usec = (___timeout) % 1000000;
        ret = select ( fd+1, NULL, &wset, NULL, &timeout );
        if (0 > ret)
        {
            return -1;
        }
        else if(0 == ret)
        {
			return 0;
		}
        else
        {
            if ( FD_ISSET( fd, &wset ) )
            {
                ___timeout = timeout.tv_sec*1000000 + timeout.tv_usec;
            }
            else
            {
                return -1; //sock 错误？
            }
            ret = send( fd, send_buf, send_len, 0 );
            if ( EAGAIN == ret )
            {
               crs_sleep(40);
			   continue;
            }
            else if( ret < 0 )
            {
				return (-1);
            }
			return ret;
        }
    }
    return 0;
}


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
extern crs_socket_handler_t* crs_udp_socket_create()
{
    crs_socket_handler_t *sock = (crs_socket_handler_t *) crs_malloc( sizeof ( crs_socket_handler_t ) );
    if (NULL == sock)
    {
        return NULL;
    }

    int32_t fd = -1;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > fd)
    {
        close(fd);
        crs_free(sock);
        return NULL;
    }
    sock->fd = fd;
    sock->sock_type = SOCK_DGRAM;

    return sock;
}

  /*
	function : 
		加入组播组			
	input : 
		crs_socket_handler_t *sock ： socket handle
		int8_t *ip : 组播的ip地址
	return value : 
		success :	返回 0
		fail : 	返回 -1
*/
#if 0
int32_t crs_udp_join_multicast(crs_socket_handler_t *sock, const uint8_t *multicast_addr, uint16_t port)
{
    sock->fd = socket(AF_INET, SOCK_DGRAM, 0);
    int32_t fd = sock->fd;
    if(-1 == fd)
    {
        crs_dbg("crs udp socket error : %s\n", strerror(errno));
        return -1;
    }
    struct   sockaddr_in   srv;
    struct ip_mreq mreq;
    crs_memset(&srv, 0, sizeof(struct sockaddr_in));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl(INADDR_ANY);
    srv.sin_port = htons(port);
    if(bind(fd,(struct   sockaddr*)&srv,sizeof(srv)) <0)
    {
        close(fd);
        crs_dbg("bind failed : %s\n", strerror(errno));
        return -1;
    }
    crs_memset(&mreq, 0, sizeof(struct ip_mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(multicast_addr);
    mreq.imr_interface.s_addr = crs_htonl(INADDR_ANY);
    if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        close(fd);
        crs_dbg("setsockop IP_ADD_MEMBERSHIP: %s \n", strerror(errno));
        return -1;
    }
    return 0;
}
#endif
/*
	function :
		加入广播播组
	input :
		crs_socket_handler_t *sock ： socket handle
		uint16_t port
	return value :
		success :	返回 0
		fail : 	返回 -1
*/
int32_t crs_broadcast_connect(crs_socket_handler_t *sock, uint16_t port)
{
    sock->fd = socket(AF_INET, SOCK_DGRAM, 0);
    int32_t fd = sock->fd;
    if(-1 == fd) {
        crs_dbg_red("crs udp socket error : %s\n", strerror(errno));
        return -1;
    }
    struct   sockaddr_in   srv;
    crs_memset(&srv, 0, sizeof(struct sockaddr_in));
    srv.sin_family=AF_INET;
    srv.sin_addr.s_addr=crs_htonl(INADDR_ANY);
    srv.sin_port=crs_htons(port);
    if(bind(fd,(struct sockaddr*)&srv,sizeof(srv)) <0)
    {
        close(fd);
        crs_dbg("bind failed : %s\n", strerror(errno));
        return -1;
    }
    return 0;
}
 /*
	function : 
		接收数据			
	input : 
		crs_socket_handler_t *sock ：socket handle
		int8_t *ip ： peer的ip
		uint32_t ip_len ： 指示第二个参数ip的长度
		uint16_t *port ： peer的端口
		void *buf ：所接收到的来自peer的数据
		uint32_t n ： 所接收到的来自peer的数据的长度

	return value : 
		success :	成功返回所接收到的数据的长度
		fail : 	返回 -1
*/
extern int32_t crs_udp_recvfrom(crs_socket_handler_t *sock, int8_t *ip, uint16_t *port, void *buf, uint32_t timeout_usec)
{
	struct sockaddr_in peer_addr;
	socklen_t peeraddr_len = sizeof(peer_addr);
	int32_t __fd = sock->fd;
	int32_t ip_len = crs_strlen(ip);
	int32_t n = crs_strlen(buf);
	if (0 == timeout_usec)
	{
		int32_t ret = recvfrom(__fd, buf, n, 0, (struct sockaddr*)&peer_addr, &peeraddr_len);
		if (ret > 0)
		{
			*port = ntohs(peer_addr.sin_port);
			if(NULL == ip)
			{
				ip = crs_inet_ntoa(peer.sin_addr.s_addr);
				if( NULL == ip )
				{
					crs_dbg("crs_inet_ntoa failed\r\n");
					return -1;
				}
			}
			else
			{
				int8_t *ip_ret = crs_inet_ntoa(peer.sin_addr.s_addr);
				crs_strcpy(ip, ip_ret, crs_strlen(ip_ret));
			}
		}
		return ret;
	}
	else
	{
		struct timeval __timeout;
		crs_memset(&__timeout, 0, sizeof(struct timeval));
		__timeout.tv_sec = timeout_usec / 1000000;
		__timeout.tv_usec = timeout_usec % 1000000;
		fd_set rwet;
		FD_ZERO(&rwet);
		FD_SET(__fd, &rwet);
		int32_t __ret = select(__fd + 1, &rwet, NULL, NULL, &__timeout);
		if(__ret < 0)
		{
			return -1;
		}
		else if(0 == __ret)
		{
			return 0;
		}
		else
		{
			if(FD_ISSET(__fd, &rwet))
			{
				__ret = recvfrom(__fd, buf, n, 0, (struct sockaddr*)&peer_addr, &peeraddr_len);
				if (__ret > 0)
				{
					*port = ntohs(peer_addr.sin_port);
					int8_t *ip_ret = crs_inet_ntoa(peer.sin_addr.s_addr);
					crs_strcpy(ip, ip_ret, crs_strlen(ip_ret));
				}
				else if(SL_EAGAIN == __ret)
				{
					return 0;
				}
				return __ret;
			}
			else
			{
				return -1;
			}
		}
	}
}


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
		crs_socket_handler_t *sock ： socket handle
		int8_t *ip ： peer的ip
		uint16_t port ：peer的端口
		void *buf ：发送给peer的数据
		uint32_t timeout_usec ： timeout_usec = 0表示阻塞模式，timeout_usec > 0表示超时时间
	return value : 
		success :	返回发送的数据的长度
		fail : 	返回-1
*/
extern int32_t crs_udp_sendto(crs_socket_handler_t *sock, int8_t *ip, uint16_t port, void *buf, uint32_t timeout_usec)
{
	uint32_t send_len = crs_strlen(buf);
	uint8_t *send_buf = buf;

	uint32_t ___timeout = timeout_usec;
	int32_t fd = sock->fd;

	struct sockaddr_in peer_addr;
	crs_memset( &peer_addr, 0, sizeof( peer_addr ) );
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = crs_inet_addr( ip );
	peer_addr.sin_port = htons( port );

	if (0 == timeout_usec)
	{
		return sendto( fd, send_buf, send_len, 0, (struct sockaddr*)&peer_addr, sizeof( peer_addr ) );
	}
	while (0 != send_len)
	{
		//判断是否可写
		fd_set wset;
		struct timeval timeout;
		FD_ZERO( &wset );
		FD_SET(fd, &wset);
		timeout.tv_sec = (___timeout) / 1000000;
		timeout.tv_usec = (___timeout) % 1000000;
		int32_t ret = select( fd+1, NULL, &wset, NULL, &timeout );
		if (0 > ret)
		{
			return -1;
		}
		else if(0 == ret)
		{
			return 0;
		}
		else
		{
			if (FD_ISSET(fd, &wset))
			{
				___timeout = timeout.tv_sec*1000000 + timeout.tv_usec;
			}
			else
			{
				return -1; //sock 错误
			}
			ret = sendto( fd, send_buf, send_len, 0, ( struct sockaddr* ) &peer_addr, sizeof( peer_addr ) );
			if ( EAGAIN == ret )
			{
				crs_sleep(20);
				continue;
			}
			else if( ret < 0 )
			{
				return -1;
			}
			return ret;
		}
	}
	return 0;
}

 /*
	function : 
		销毁  socket
	input : 
		crs_socket_handler_t *sock : socket handle
	return value :  无
		success :	
		fail : 	
*/
extern int32_t crs_socket_destroy( crs_socket_handler_t *sock )
{
    crs_close(sock->fd);
    crs_free(sock);
    return 0;
}
