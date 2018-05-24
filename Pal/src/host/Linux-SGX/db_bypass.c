#include "pal_linux.h"
#include "linux_types.h"

int _socket_bypass(int family, int type, int protocol)
{

   SGX_DBG(DBG_M, "_socket_bypass is called!\n");
   return ocall_socket_bypass(family, type, protocol);
}

int _bind_bypass(int sockfd, struct sockaddr * addr, socklen_t addrlen)
{
	SGX_DBG(DBG_M, "_bind_bypass is called!\n");
	return ocall_bind_bypass(sockfd, addr, addrlen);
}

ssize_t _sendmsg_bypass (int sockfd, struct msghdr * msg, int flags)
{
	SGX_DBG(DBG_M, "_sendmsg_bypass is called!\n");
	return ocall_sendmsg_bypass(sockfd, msg, flags);
}

ssize_t _recvmsg_bypass (int sockfd, struct msghdr * msg, int flags)
{
	SGX_DBG(DBG_M, "_recvmsg_bypass is called!\n");
	return ocall_recvmsg_bypass(sockfd, msg, flags);
}


int _fcntl_bypass (int fd, int cmd, unsigned long arg)
{
    SGX_DBG(DBG_M, "_fcntl_bypass is called!\n");
    return ocall_fcntl_bypass(fd, cmd, arg);
}

int _setsockopt_bypass (int fd, int level, int optname, char * optval, int optlen)
{
    SGX_DBG(DBG_M, "_setsockopt_bypass is called!\n");
    return ocall_setsockopt_bypass(fd, level, optname, optval, optlen);
}
