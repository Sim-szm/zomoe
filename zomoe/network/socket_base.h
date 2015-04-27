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


#ifndef SOCKET_BASE_H
#define SOCKET_BASE_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <unistd.h>
#include <zomoe/network/netaddress.h>

namespace zomoe { namespace network {

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
	int set_socketopt(int sockfd,unsigned int timeout);
	void set_reuseaddr(bool on);
	void bind_t(zomoe::network::netaddress& localaddr);
	void listen_t();
	int accept_t(zomoe::network::netaddress* address);
	void shutdown_write();

private:
	int m_sockfd;
};

}}
#endif

