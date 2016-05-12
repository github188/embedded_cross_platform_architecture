/*******************************************************************
*						socket demo
* TCP Server
* TCP Client
* UDP Socket
* UDP Client
* UDP Multicast
********************************************************************/

/*******************************************************************
*						TCP Server
********************************************************************/
#include "crs_socket.h"
#include "crs_task.h"
#include "crs_types.h"
#include "crs_mem.h"

#define default_port		8080
#define default_backlog		10
#define BUFF_SIZE			100
#define default_timeout_ms	500
#define server_ip			"127.0.0.1"
void crs_tcp_server()
{
	crs_socket_handler_t *sock_t = NULL;
	int32_t maxfd = 0;
	int8_t recv_buf[BUFF_SIZE];
	int8_t *send_buf = "hello, i am tcp server";
	int32_t recv_len = 0;
	int32_t cnt = 100;
	crs_socket_handler_t *accept_handle;
	//对recv_buff初始化清零
	crs_memset(recv_buf, 0, BUFF_SIZE);
	//创建一个tcp socket
	sock_t = crs_tcp_socket_create();
	if( NULL == sock_t )
	{
		crs_dbg("crs_tcp_server crs_tcp_socket_create failed\r\n");
		return ;
	}
	//对所创建的socket 绑定监听端口
	if ( -1 == crs_bind( sock_t, default_port ) )
	{
		crs_dbg("crs_bind failed\r\n");
		return ;
	}
	//对绑定的端口进行监听
	if ( -1 == crs_listen( sock_t, default_backlog) )
	{
		crs_dbg("crs_listen failed\r\n");
		return ;
	}

	while( cnt -- >= 0 )
	{
		accept_handle = crs_accept( sock_t );
		if( NULL == accept_handle )
		{
			crs_dbg("crs_accpet failed\r\n");
			return ;
		}

		//非阻塞从客户端获得数据
		crs_memset(recv_buf, 0, BUFF_SIZE);
		int32_t recv_ret = crs_tcp_recv( accept_handle, recv_buf, crs_strlen(recv_buf), default_timeout_ms);
		if( recv_ret < 0)
		{
			crs_dbg("crs_tcp_server crs_tcp_recv failed\r\n");
		}
		else if(0 == recv_ret)
		{
			crs_dbg("crs_tcp_recv timeout\r\n");
		}
		else
		{
			crs_dbg("recv_len :** %d ** recv_buf : ** %s **\r\n", recv_ret, recv_buf);
			crs_dbg("ip : ** %s ** port : ** %d **\r\n",accept_handle->sock_info.peer_ip, accept_handle->sock_info.peer_port);
		}
		//非阻塞向客户端发送数据
		int32_t send_ret = crs_tcp_send( accept_handle, send_buf, crs_strlen(send_buf), default_timeout_ms);
		if(send_ret < 0)
		{
			crs_dbg("crs_tcp_send failed\r\n");
		}
		else if( 0 == send_ret )
		{
			crs_dbg("crs_tcp_send timeout\r\n");
		}
		else
		{
			crs_dbg("send_len : %d, send_buf : %s\r\n",send_ret, send_buf);
			crs_dbg("client ip : %s, client port : %d\r\n",accept_handle->sock_info.peer_ip, accept_handle->sock_info.peer_port);
		}
		crs_sleep(100);
	}

	crs_socket_destroy(sock_t);
	crs_dbg("end of crs_tcp_server\r\n");
}
/*******************************************************************
*						TCP Client
********************************************************************/
void crs_tcp_client()
{
	int8_t *send_buf = "hello, i am tcp client";
	int8_t recv_buf[BUFF_SIZE];
	int32_t send_ret = 0,recv_ret = 0;
	int32_t cnt = 100;
	crs_socket_handler_t *tcp_client = crs_tcp_socket_create();
	if(NULL == tcp_client)
	{
		crs_socket_destroy(tcp_client);
		crs_dbg("crs_tcp_socket_create failed\r\n");
		return ;
	}
	if( -1 == crs_tcp_connect( tcp_client, server_ip, default_port, default_timeout_ms) )
	{
		crs_socket_destroy(tcp_client);
		crs_dbg("crs_tcp_client crs_tcp_connect failed\r\n");
		return ;
	}
	crs_dbg("client connect to the server\r\n");
	while( cnt -- >= 0 )
	{
		//向服务器端发送数据
		send_ret = crs_tcp_send(tcp_client, send_buf, BUFF_SIZE, default_timeout_ms);
		if(send_ret < 0)
		{
			crs_dbg("crs_tcp_send failed\r\n");
		}
		else if( 0 == send_ret )
		{
			crs_dbg("crs_tcp_send timeout\r\n");
		}
		else
		{
			crs_dbg("send_len : %d, send_buf : %s\r\n",send_ret, send_buf);
		}

		//接收来自服务器端的数据
		crs_memset(recv_buf, 0, BUFF_SIZE);
		recv_ret = crs_tcp_recv( tcp_client, recv_buf, crs_strlen(recv_buf),default_timeout_ms);
		if(recv_ret < 0)
		{
			crs_dbg("crs_tcp_client crs_tcp_recv failed\r\n");
		}
		else if(0 == recv_ret)
		{
			crs_dbg("crs_tcp_recv timeout\r\n");
		}
		else
		{
			crs_dbg("recv_len : %d, recv_buf : %s\r\n",recv_ret, recv_buf);
		}
		crs_sleep(100);
	}
	crs_socket_destroy(tcp_client);
	crs_dbg("end of crs_tcp_client\r\n");
}

/*******************************************************************
*						UDP Server
********************************************************************/
void crs_udp_server()
{
	int8_t *send_buf = "hello, i am udp server";
	int8_t recv_buf[BUFF_SIZE];
	int32_t send_ret = 0,recv_ret = 0;
	int8_t *ip = NULL;
	int32_t port = 0;
	int32_t cnt = 100;
	crs_socket_handler_t *udp_server = crs_udp_socket_create();
	if(NULL == udp_server)
	{
		crs_dbg("crs_udp_socket_create failed\r\n");
		return ;
	}

	if( -1 == crs_bind(udp_server, default_port) )
	{
		crs_dbg("crs_bind failed\r\n");
		return ;
	}

	while( cnt -- >= 0 )
	{
		//接收来自客户端的数据
		crs_memset(recv_buf, 0, BUFF_SIZE);
		recv_ret = crs_udp_recvfrom(udp_server, ip, &port,recv_buf, default_timeout_ms);
		if(recv_ret < 0)
		{
			crs_dbg("crs_udp_server crs_udp_recvfrom failed\r\n");
		}
		else if(0 == recv_ret)
		{
			crs_dbg("crs_tcp_recv timeout\r\n");
		}
		else
		{
			crs_dbg("recv_len : %d, recv_buf : %s\r\n",recv_ret, recv_buf);
		}

		//向客户端发送数据
		send_ret = crs_udp_sendto(udp_server, ip, port, send_buf, default_timeout_ms);
		if(send_ret < 0)
		{
			crs_dbg("crs_udp_sendto failed\r\n");
		}
		else if( 0 == send_ret )
		{
			crs_dbg("crs_udp_sendto timeout\r\n");
		}
		else
		{
			crs_dbg("send_len : %d, send_buf : %s\r\n",send_ret, send_buf);
		}
		crs_sleep(100);
	}
	crs_socket_destroy(udp_server);
	crs_dbg("end of crs_udp_server\r\n");
}
/*******************************************************************
*						UDP Client
********************************************************************/

void crs_udp_client()
{
	int8_t *send_buf = "hello, i am udp client";
	int8_t recv_buf[BUFF_SIZE];
	int32_t send_ret = 0,recv_ret = 0;
	int8_t ip[16];
	int32_t port = 0;
	int32_t cnt = 0;
	//创建udp_clinet socket
	crs_socket_handler_t *udp_client = crs_udp_socket_create();
	if(NULL == udp_client)
	{
		crs_dbg("crs_udp_socket_create failed\r\n");
		return ;
	}

	crs_memset(ip, 0, 16);
	crs_strcpy(ip,server_ip);
	port = default_port;

	while( cnt-- >= 0 )
	{
		//向服务器发送数据
		send_ret = crs_udp_sendto(udp_client, ip, port, send_buf, default_timeout_ms);
		if(send_ret < 0)
		{
			crs_dbg("crs_udp_sendto failed\r\n");
		}
		else if( 0 == send_ret )
		{
			crs_dbg("crs_udp_sendto timeout\r\n");
		}
		else
		{
			crs_dbg("send_len : %d, send_buf : %s\r\n",send_ret, send_buf);
		}

		//接收来自服务器端的数据
		crs_memset(recv_buf, 0, BUFF_SIZE);
		recv_ret = crs_udp_recvfrom(udp_client, ip, &port,recv_buf, default_timeout_ms);
		if(recv_ret < 0)
		{
			crs_dbg("crs_udp_server crs_udp_recvfrom failed\r\n");
		}
		else if(0 == recv_ret)
		{
			crs_dbg("crs_tcp_recv timeout\r\n");
		}
		else
		{
			crs_dbg("recv_len : %d, recv_buf : %s\r\n",recv_ret, recv_buf);
		}
		crs_sleep(100);
	}
	crs_socket_destroy(udp_client);
	crs_dbg("end of crs_udp_client\r\n");
}
