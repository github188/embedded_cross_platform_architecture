/*
*socket management
*socket通信
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "sockets.h"
#include "crs_socket.h"
#include "crs_debug.h"
#include "crs_mem.h"
#include "netdb.h"
#include "lwip/ip_addr.h"

struct crs_socket_handler {
    int32_t fd;
    int32_t sock_type;
    crs_sock_info_t sock_info;
};

struct crs_fd_set {
    fd_set fds;
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
extern int32_t crs_select(crs_socket_handler_t *fd[], uint32_t size, crs_fd_set_t *readfds, crs_fd_set_t *writefds, crs_fd_set_t *exceptfds, uint32_t *timeout_usec)
{
    int32_t max_fd = 0;
    uint32_t count = 0;
    struct timeval delay;
    crs_memset(&delay, 0, sizeof(struct timeval));
    	delay.tv_sec = *timeout_usec / 1000000;
    	delay.tv_usec = *timeout_usec % 1000000;
    for(count = 0; count < size; ++count)
    {
        if(max_fd < fd[count]->fd)
        {
        	max_fd = fd[count]->fd;
        }
    }

    int32_t ret = select(max_fd + 1, &(readfds->fds), &(writefds->fds), &(exceptfds->fds), &delay);

    return ret;
}

/*
	function :
		创建文件集合
	input :
	return value :
		success :
		fail :
*/
extern crs_fd_set_t * crs_fd_set_create()
{
    crs_fd_set_t *set = (crs_fd_set_t *)crs_malloc(sizeof(crs_fd_set_t));
    crs_memset(set, 0, sizeof(crs_fd_set_t));
    return set;
}
/*
	function :
		销毁文件集合crs_fd_set_t handler
	input :
		crs_fd_set_t *set ： 文件集合
	return value :
		success : 返回 0
		fail :
*/
extern int32_t crs_fd_set_destroy(crs_fd_set_t *set)
{
    if (NULL == set)
    {
        return 0;
    }
    crs_memset(set);
    return 1;
}
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
		success : true
		fail : false
*/
extern int32_t crs_fd_isset(crs_socket_handler_t *fd, crs_fd_set_t *set)
{
    if (NULL == fd)
    {
        return 0;
    }

    if (NULL == set)
    {
        return 0;
    }

    return FD_ISSET(fd->fd, &(set->fds));
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
extern void crs_fd_set(crs_socket_handler_t *fd, crs_fd_set_t *set)
{
    if (NULL == fd)
    {
        return ;
    }

    if (NULL == set)
    {
        return ;
    }

    FD_SET(fd->fd, &(set->fds));
}
/*
	function :
		将文件集合清0
	input : crs_fd_set_t *set
	return value : 无
		success :
		fail :
*/
extern void crs_fd_zero(crs_fd_set_t *set)
{
    if (NULL == set)
    {
        return ;
    }

    FD_ZERO(&(set->fds));
}
/*
	function :
		将socket的port和sockaddr_in对应的结构体bind
	input :
		crs_socket_handler_t *sock
		uint16_t port
	return value :
		success : 1
		fail : 0
*/
extern int32_t crs_bind(crs_socket_handler_t *sock, uint16_t port)
{
    struct sockaddr_in local_addr;
    crs_memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(port);

    if (bind(sock->fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0)
    {
        return 0;
    }

    return 1;
}
/*
	function :
		对对应的socket进行监听，监测客户端socket的连接请求
	input :
		crs_socket_handler_t *sock
 	 	uint32_t backlog ：连接所能处理的最大监听连接数目，即服务器端所能接受的最多的客户端请求数
	return value :
		success : true
		fail : false
*/
extern int32_t crs_listen(crs_socket_handler_t *sock, uint32_t backlog)
{
    if (listen(sock->fd, backlog) < 0)
    {
        return 0;
    }
    return 1;
}
/*
	function :
		接收客户端的socket的连接请求，获得客户端的socket信息
	input :
		crs_socket_handler_t *sock
	return value :
		success : return 客户端的socket
		fail : return NULL
*/
extern crs_socket_handler_t *crs_accept(crs_socket_handler_t *sock)
{
    char str_ip[16];
	memset(str_ip, 0,16);
    crs_socket_handler_t *new_sock = (crs_socket_handler_t *) crs_malloc(sizeof(crs_socket_handler_t));
    if (NULL == new_sock) {
        return NULL;
    }
    memset(new_sock, 0, sizeof(crs_socket_handler_t));

    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;
    new_sock->fd = accept(sock->fd, (struct sockaddr *)&peeraddr, &peeraddr_len);
    if (0 > new_sock->fd) {
        crs_memfree(new_sock);
        return NULL;
    }

    strncpy(new_sock->sock_info.peer_ip, crs_inet_ntoa(peeraddr.sin_addr.s_addr,str_ip,16), sizeof(new_sock->sock_info.peer_ip) -1);
    new_sock->sock_info.peer_port = ntohs(peeraddr.sin_port);

    return new_sock;
}


/*
	function :
		socket 信息结构体
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
		获得所需要的socket的结构体信息
	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_getsock_info(crs_socket_handler_t *sock, crs_sock_info_t *sock_info)
{
    mem_copy(sock_info, &sock->sock_info, sizeof(crs_sock_info_t));
    return 0;
}


/*
	function :

	input :
	return value :
		success :
		fail :
*/
/*
 * struct ip_addr {
  	  u32_t addr;
	};
 * */
extern bool crs_gethostbyname(const char *name, char *ip, const uint8_t  ip_size)
{
	char **pptr = NULL;
	struct hostent *hptr = NULL;

    if (NULL == name)
    {
        crs_dbg("crs_gethostbyname invalid name\n");
        return false;
    }
    if (NULL == ip) {
        crs_dbg("crs_gethostbyname invalid ip\n");
        return false;
    }
    if (ip_size < 16) {
        crs_dbg("crs_gethostbyname ip_size[%zd](<16) is invalid\n", ip_size);
        return false;
    }
    hptr = gethostbyname(name);
    if (NULL == hptr) {
        crs_dbg("crs_gethostbyname for host %s failed: %d\n", name, errno);
        return false;
    }

    crs_dbg("crs_gethostbyname %s official hostname: %s\n", name, hptr->h_name);
    for(pptr = hptr->h_aliases; *pptr != NULL; pptr++) {
        crs_dbg("crs_gethostbyname %s alias: %s\n", name, *pptr);
    }

    switch(hptr->h_addrtype) {
        case AF_INET:
        	// 选择最后一个IP  TODO 后期随机选择一个
			pptr = hptr->h_addr_list;
            for(; *pptr != NULL; pptr++) {
                crs_memset(ip, 0, ip_size);
                crs_strcpy(ip, inet_ntoa(*((struct in_addr *)*pptr)));
                crs_dbg("crs_gethostbyname %s ip: %s\n", name, ip);
            }
            break;
        default:
            crs_dbg("crs_gethostbyname get %s ip failed Unkonwn address type\n", name);
            return false;
    }
    return true;
}

/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern char* crs_inet_ntoa(const uint32_t ip, char *str_ip, uint32_t str_ip_size)
{
    struct in_addr addr;
    crs_memset(&addr, 0, sizeof(addr));
    addr.s_addr = htonl(ip);

    ipU32toString(htonl(addr.s_addr),str_ip);
    return str_ip;
}


/*
	function :

	input :
	return value :
		success :
		fail :
*/
static char * crs_inet_ntop(int family, const void *addrptr, char *strptr, size_t len )
{

    unsigned char  *p = (unsigned char *)addrptr;
    if(family == AF_INET)
    {
        char temp[16];
        snprintf(temp,sizeof(temp),"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
        if(strlen(temp) >= len)
        {
            return NULL;
        }
        strcpy(strptr,temp);
        return strptr;
    }
    return NULL;

}

/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern uint32_t crs_inet_addr(const char* ip)
{
	long a, b, c, d;
	long address = 0;
    sscanf(ip, "%ld.%ld.%ld.%ld", &a, &b, &c, &d);
    address |= d<<24;
    address |= c<<16;
    address |= b<<8;
    address |= a;
    return address;
}

/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern uint32_t crs_htonl(uint32_t hostlong)
{
    return htonl(hostlong);
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern uint16_t crs_htons(uint16_t hostlong)
{
    return htons(hostlong);
}

/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern uint32_t crs_ntohl(uint32_t netlong)
{
    return ntohl(netlong);
}
/*
	function :

	input :
	return value :
		success :
		fail :
*/
extern uint16_t crs_ntohs(uint16_t netlong)
{
    return ntohs(netlong);
}

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
    if(setsockopt(fd,SOL_SOCKET,SL_SO_NONBLOCKING,&enable,sizeof(enable)) < 0)
    {
			crs_memfree(sock);
			close(fd);
			return NULL;
    }


    sock->fd = fd;
    sock->sock_type = SOCK_STREAM;

    return sock;
}

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
extern int32_t crs_tcp_connect(crs_socket_handler_t *sock, char *ip, uint16_t port, uint32_t timeout_usec)
{
    int32_t fd = sock->fd;
    struct sockaddr_in peer_addr;
	int val,timeout_ms;
	val = 0;
	timeout_ms = timeout_usec/1000;
    crs_memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = crs_inet_addr(ip);
    peer_addr.sin_port = htons(port);

    while (1)
    {
        val = connect(fd, (struct sockaddr *)&peer_addr, sizeof(peer_addr));
		if((SL_EALREADY == val)||(SL_POOL_IS_EMPTY == val))
		{
			if(timeout_ms > 0)
			{
					timeout_ms -=5;
					osi_Sleep(5);
					continue;
			}
			else
			{
				return -1;
			}
		}
		else if(val < 0)
		{
			return (-1);
		}
		else
		{
			 break;
		}
    }
    return val;
}


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
extern int32_t crs_tcp_recv(crs_socket_handler_t *sock, void *buf, uint32_t n, uint32_t timeout_usec)
{
    int32_t fd = sock->fd;
    int32_t ret;
    uint32_t len = n;
    uint8_t * recv_buf;
    recv_buf = buf;

    if (0 == timeout_usec)
    {
        return recv(fd, recv_buf, len, SL_SO_NONBLOCKING);
    }

    uint32_t timeout_left = timeout_usec;
    struct timeval delay;
    while(len > 0)
    {
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
            if(FD_ISSET(fd, &fds))
            {
                timeout_left = delay.tv_sec * 1000000 + delay.tv_usec;
                ret = recv(fd, recv_buf, len, 0);
                if(SL_EAGAIN == ret)
                {
					osi_Sleep(100);
					continue;
                }
                else if(ret<0)
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
	//dbg("FREE STACK SPACE:%d\r\n",uxTaskGetStackHighWaterMark());

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
        timeout.tv_sec = (___timeout)/1000000;
        timeout.tv_usec = (___timeout)%1000000;
        ret = select(fd+1, NULL, &wset, NULL, &timeout);
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
                return -1; //sock 错误？
            }
            //send
            ret = send(fd, send_buf, send_len, 0);
            if (SL_EAGAIN == ret)
            {
               osi_Sleep(100);
			   continue;
            }
            else if(ret < 0)
            {
				return (-1);
            }
			return ret;
        }
    }
    return 0;
}

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
extern int32_t crs_tcp_socket_destroy(crs_socket_handler_t *sock)
{
    close(sock->fd);
    crs_memfree(sock);
    return 0;
}
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
extern crs_socket_handler_t* crs_udp_socket_create()
{
	int yes = 1;
    crs_socket_handler_t *sock = (crs_socket_handler_t *) crs_malloc( sizeof(crs_socket_handler_t));
    if (NULL == sock)
    {
        return NULL;
    }

    int32_t fd = -1;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > fd)
    {
        close(fd);
        crs_memfree(sock);
        return NULL;
    }

	if(setsockopt(fd,SOL_SOCKET,SL_SO_NONBLOCKING,&yes,sizeof(yes)) < 0)
	{
		crs_memfree(sock);
		close(fd);
		return NULL;
	}
    sock->fd = fd;
    sock->sock_type = SOCK_DGRAM;

    return sock;
}
/*
 * 加入组播组
 */
#if 0
extern int32_t crs_udp_socket_join_multicast(crs_socket_handler_t *sock, char *ip)
{
    int32_t fd = sock->fd;

	SlSockIpMreq mreq;
	crs_memset((void *)&mreq,0,sizeof(mreq));
	mreq.imr_multiaddr.s_addr = crs_inet_addr(ip);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if(setsockopt(fd, SL_IPPROTO_IP, SL_IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
			return -1;
	};

	return 0;
}
#endif
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
extern int32_t crs_udp_recvfrom(crs_socket_handler_t *sock, char *ip, uint32_t ip_len, uint16_t *port, void *buf, uint32_t n, uint32_t timeout_usec)
{

    struct sockaddr_in peer_addr;
    socklen_t peeraddr_len = sizeof(peer_addr);
    int32_t __fd = sock->fd;


    if (0 == timeout_usec)
    {
        int32_t ret = recvfrom(__fd, buf, n, 0, (struct sockaddr*)&peer_addr, &peeraddr_len);
        if (ret > 0)
        {
            *port = ntohs(peer_addr.sin_port);
            my_inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, ip_len - 1);
        }

        return ret;
    }
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
                crs_inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, ip_len - 1);
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
extern int32_t crs_udp_sendto(crs_socket_handler_t *sock, char *ip, uint16_t port, void *buf, uint32_t n, uint32_t timeout_usec)
{
    uint32_t send_len = n;
    uint8_t *send_buf = buf;

    uint32_t ___timeout = timeout_usec;
    int32_t fd = sock->fd;

    struct sockaddr_in peer_addr;
    crs_memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = crs_inet_addr(ip);
    peer_addr.sin_port = htons(port);

    if (0 == timeout_usec)
    {
        return sendto(fd, send_buf, send_len, 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
    }

    while (0 != send_len)
    {
        //判断是否可写
        fd_set wset;
        struct timeval timeout;
        FD_ZERO(&wset);
        FD_SET(fd, &wset);
        timeout.tv_sec = (___timeout)/1000000;
        timeout.tv_usec = (___timeout)%1000000;
        int32_t ret = select(fd+1, NULL, &wset, NULL, &timeout);
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
                return -1; //sock 错误？
            }
            //send
            ret = sendto(fd, send_buf, send_len, 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
            if (SL_EAGAIN == ret)
            {
				osi_Sleep(10);
				continue;
            }
            else if(ret<0)
            {
				return -1;
            }
			return ret;
        }
    }
    return 0;
}


#if 1
/*
 *
 */
 /*
	function :
		销毁 udp socket
	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_udp_socket_destroy(crs_socket_handler_t *sock)
{
    close(sock->fd);
    crs_memfree(sock);
    return 0;
}
#endif

/*
 *
 */
 /*
	function :
		销毁 socket
	input :
	return value :
		success :
		fail :
*/
extern int32_t crs_socket_destroy(crs_socket_handler_t *sock)
{
    close(sock->fd);
    crs_memfree(sock);
    return 0;
}

