/* =====================================================================================
 * 
 *       Filename:  socket_base.h
 *       Created :  2015年04月26日 15时26分56秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */


#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <unistd.h>

namespace zomoe { namespace network {

typedef struct sockaddr SA;

class netaddress;

SA* sockaddr_cast(struct sockaddr_in* addr){
	return static_cast<SA*> (implicit_cast<void*> addr)
}

static inline int set_nonblocking(int fd){
	if(fcntl(fd,F_SETFL,fcntl(fd,GETFD,0)|O_NON_BLOCK)== -1){
		return -1;
	}
	return 0;
}

void set_close_onexec(int sockfd) {
	int ret = fcntl(fd,F_SETFL,fcntl(fd,GETFD,0)|FD_CLOEXEC);
}


class socket_event{
public:
	explicit socket_event(int sockfd):m_sockfd(sockfd){
	}
	~socket_event(){
		close(m_sockfd);
	}
	int get_sockfd() const{
		return m_sockfd;
	}
	int new_socket();
	int set_socketopt(int sockfd);
	void set_reuseaddr(bool on);
	void bind_t(const netaddress& localaddr);
	void listen_t();
	int accept_t(netaddress* address);
	void shutdown_write();

private:
	const int m_sockfd;
	netaddress client_addr;
};

int socket_event::new_socket(){
	int sockfd = socket(AF_INET,SOCK_STERAM,IPPROTO_TCP);
	if (sockfd < 0){
		perror("socket!")
	}
	set_nonblocking(sockfd);
	set_close_onexec(sockfd);
	return sockfd;
}
int socket_event::set_socketopt(int sockfd, unsigned int timeout){
	int result=0,flag=0;
    	do{
        	if (KEEPALIVE){
	            //set tcp_keepAlive
        	    result = setsockopt(sockfd, SOL_SOCKET,\
                	             SO_KEEPALIVE, &optval,\
                        	        (socklen_t) sizeof(int));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	            result = setsockopt(sockfd, SOL_TCP, \
        	                        TCP_KEEPIDLE,\
	                                 &timeout,\
        	                         sizeof(timeout));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	            int keepcnt = 3;
        	    result = setsockopt(sockfd, SOL_TCP, \
                	                TCP_KEEPCNT, \
                        	        &keepcnt, \
	                                sizeof(keepcnt));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	            int keepintvl = 10;
	            result = setsockopt(sockfd, SOL_TCP, \
	                                TCP_KEEPINTVL, \
	                                &keepintvl,\
	                                sizeof(keepintvl));
	            if (-1 == result){
	                flag=1;
	                break;
	            }
	        }
	        if (LINGER){
	            struct linger optval;
		    optval.l_onoff = true;
	            optval.l_linger = timeout;
	            result = setsockopt(sockfd, SOL_SOCKET,\
        	                         SO_LINGER, &optval,
                	                (socklen_t) sizeof(struct linger));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	        }
	        if (NODELAY){
	            result = setsockopt(sockfd, SOL_TCP, \
        	                        TCP_NODELAY, &optval,\
                	                 sizeof(optval));
	            if (-1 == result){
        	        flag=1;
	                break;
        	    }
	            result = setsockopt(sock, SOL_SOCKET, \
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
        	    result = setsockopt(sockfd, SOL_SOCKET,\
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
	setsockopt(&m_sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

void socket_event::bind_t(const netaddress& localaddr) {
	int ret = bind(m_sockfd,sockaddr_cast(&(localaddr.get_sock_netaddr())),sizeof(struct sockaddr));
	if (ret < 0){
		perror("bind error !");
	}
}

void socket_event::listen_t(int listenfd) {
	int ret = listen(m_sockfd,BACKLOG);
	if (ret < 0){
		perror("listen error !");
	}
}

int socket_event::accept_t(netaddress& address){

        do{
            struct sockaddr_in client_addr;
            bzero(&client_addr,sizeof(client_addr));
            socklen_t addrlen=sizeof(client_addr);

#if NOT_USE_NONBLOCK

            int connfd=accept(m_sockfd,\
                (struct sockaddr *)&client_addr,&addrlen);

#else
            int connfd=accept4(m_sockfd,(struct sockaddr*)&client_addr,\
                        &addrlen,SOCK_NONBLOCK|SOCK_CLOEXEC);
#endif

            if (connfd < 0){
                perror("accept error! connfd < 0");
		break;
            }else if (connfd > 0){
                address->set_sock_netaddress(client_addr);
            }
	    return connfd;

        }while(false);
    }
    return 0;

}

void socket_event::shutdown_write(){
	
	if(shutdown(m_sockfd,SHUT_WR) < 0){
		perror("shutdown_write error !");
	}
}
}}
#endif 

