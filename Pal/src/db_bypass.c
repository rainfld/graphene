#include "pal.h"

int socket_bypass(int family, int type, int protocol)
{
  return _socket_bypass(family, type, protocol);
}


int bind_bypass (int sockfd, void* addr, unsigned short addrlen)
{
	return _bind_bypass(sockfd, addr, addrlen);
}

ssize_t sendmsg_bypass (int sockfd, void * msg, int flags)
{
	return _sendmsg_bypass(sockfd, msg, flags);
}

ssize_t recvmsg_bypass (int sockfd, void * msg, int flags)
{
	return _recvmsg_bypass(sockfd, msg, flags);
}

int fcntl_bypass (int fd, int cmd, unsigned long arg)
{
    return _fcntl_bypass(fd, cmd, arg);
}

int setsockopt_bypass (int fd, int level, int optname, char * optval, int optlen)
{
    return _setsockopt_bypass(fd, level, optname, optval, optlen);
}

