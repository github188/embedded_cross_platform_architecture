code for the linux

还差atomic

udp 广播和组播没有实现

extern int32_t crs_udp_socket_join_multicast(crs_udp_socket_handler_t *sock, int8_t *ip)
{
    int32_t fd = sock->fd;

	SlSockIpMreq mreq;
	crs_memset((void *)&mreq,0,sizeof(mreq));
	mreq.imr_multiaddr.s_addr = crs_inet_addr(ip);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if(sl_SetSockOpt(fd, SL_IPPROTO_IP, SL_IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
			return -1;
	};

	return 0;
}

crs_udp_socket_join_broadcast