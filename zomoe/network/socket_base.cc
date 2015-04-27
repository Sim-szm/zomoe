/* =====================================================================================
 *
 *       Filename:  socket_base.cc
 *       Created :  2015年04月26日 15时26分56秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>  // snprintf
#include <strings.h>  // bzero
#include <sys/socket.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <zomoe/network/socket_base.h>


#define KEEPALIVE 0
#define LINGER 0
#define NODELAY 0
#define TIMEOUT 0
#define BACKLOG 20

namespace zomoe { namespace network {

typedef struct sockaddr SA;

static inline int set_nonblocking(int fd){
	if(fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0)|O_NONBLOCK)== -1){
		return -1;
	}
	return 0;
}

static inline int set_close_onexec(int sockfd) {
	if(fcntl(sockfd,F_SETFD,fcntl(sockfd,F_GETFD,0)|FD_CLOEXEC) == -1) {
		return -1;
	}
	return 0;
}

int socket_event::new_socket(){
	int sockfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sockfd < 0){
		perror("socket!");
	}
	set_nonblocking(sockfd);
	set_close_onexec(sockfd);
	m_sockfd = sockfd;
	return sockfd;
}
int socket_event::set_socketopt(int sockfd, unsigned int timeout){
	int result=0,flag=0,optval = 1;
    	do{
        	if (KEEPALIVE){
	            //set tcp_keepAlive
        	    result = ::setsockopt(sockfd, SOL_SOCKET,\
                	             SO_KEEPALIVE, &optval,\
                        	        (socklen_t) sizeof(int));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	            result = ::setsockopt(sockfd, SOL_TCP, \
        	                        TCP_KEEPIDLE,\
	                                 &timeout,\
        	                         sizeof(timeout));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	            int keepcnt = 3;
        	    result = ::setsockopt(sockfd, SOL_TCP, \
                	                TCP_KEEPCNT, \
                        	        &keepcnt, \
	                                sizeof(keepcnt));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	            int keepintvl = 10;
	            result = ::setsockopt(sockfd, SOL_TCP, \
	                                TCP_KEEPINTVL, \
	                                &keepintvl,\
	                                sizeof(keepintvl));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	        }
	        if (LINGER){
	            struct linger optval_l;
		    optval_l.l_onoff = true;
	            optval_l.l_linger = timeout;
	            result = ::setsockopt(sockfd, SOL_SOCKET,\
        	                         SO_LINGER, &optval_l,
                	                (socklen_t) sizeof(struct linger));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	        }
	        if (NODELAY){

	            struct timeval waittime;
        	    waittime.tv_sec = timeout;
	            waittime.tv_usec = 0;
	            result = ::setsockopt(sockfd, SOL_TCP, \
        	                        TCP_NODELAY, &optval,\
                	                 sizeof(optval));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	            result = ::setsockopt(sockfd, SOL_SOCKET, \
        	                        SO_RCVTIMEO, &waittime,\
                	                    sizeof(struct timeval));
	            if (-1 == result){
        	        flag=1;
                	break;
            	}
	        }
        	if(TIMEOUT){
	            struct timeval waittime;
        	    waittime.tv_sec = timeout;
	            waittime.tv_usec = 0;
        	    result = ::setsockopt(sockfd, SOL_SOCKET,\
                	                 SO_SNDTIMEO, &waittime,\
                        	            sizeof(struct timeval));
	            if (-1 == result){
        	        flag=1;
                	break;
	            }
	        }
	    }while(0);

	    if (flag == 1){
	        return -1;
	    }
	    return 0;
}

void socket_event::set_reuseaddr(bool on){
	int opt = on ? 1 : 0;
	::setsockopt(m_sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

void socket_event::bind_t(zomoe::network::netaddress& localaddr) {
	int ret = ::bind(m_sockfd,(SA*)&(localaddr.get_sock_netaddr()),sizeof(SA));
	if (ret < 0){
		perror("bind error !");
	}
}

void socket_event::listen_t() {
	int ret = ::listen(m_sockfd,BACKLOG);
	if (ret < 0){
		perror("listen error !");
	}
}

int socket_event::accept_t(zomoe::network::netaddress* address){

        do{
            struct sockaddr_in client_addr;
            bzero(&client_addr,sizeof(client_addr));
            socklen_t addrlen=sizeof(client_addr);

#if NOT_USE_NONBLOCK

            int connfd = ::accept(m_sockfd,\
                (struct sockaddr *)&client_addr,&addrlen);

#else
            int connfd = ::accept4(m_sockfd,(struct sockaddr*)&client_addr,\
                        &addrlen,SOCK_NONBLOCK|SOCK_CLOEXEC);
#endif
            if (connfd < 0)
  			{
    			int savedErrno = errno;
    			switch (savedErrno)
    			{
      				case EAGAIN:
      				case ECONNABORTED:
      				case EINTR:
      				case EPROTO:
      				case EPERM:
      				case EMFILE:
        				errno = savedErrno;
        				break;
      				case EBADF:
      				case EFAULT:
      				case EINVAL:
      				case ENFILE:
      				case ENOBUFS:
      				case ENOMEM:
      				case ENOTSOCK:
      				case EOPNOTSUPP:
        				perror("unexpected error of ::accept ");
        				break;
      				default:
        				break;
    			}
  			}else if (connfd > 0){
                address->set_sock_netaddress(client_addr);
            }
	    	return connfd;

        }while(false);
	return 0;
}

void socket_event::shutdown_write(){

	if(::shutdown(m_sockfd,SHUT_WR) < 0){
		perror("shutdown_write error !");
	}
}
}}
