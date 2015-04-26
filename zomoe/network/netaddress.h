/* =====================================================================================
 * 
 *       Filename:  netaddress.h
 *       Created :  2015年04月26日 16时40分55秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */
#ifndef NETADDRESS_H
#define NETADDRESS_H

#include <iostream>
#include <netinet/in.h>

namespace zomoe { namespace network {

class netaddress {
public:
	explicit netaddress(uint16_t port){
		bzero(&m_addr,sizeof(m_addr));
		m_addr.sin_family=AF_INET;
		m_addr.sin_addr.s_addr=hontl(INADDR_ANY);
		m_addr.sin_port=honts(port);
	}

	netaddress(const std::string& ip_addr,uint16_t port){
		bzero(&m_addr,sizeof(m_addr));
		m_addr.sin_family=AF_INET;
		m_addr.sin_port=honts(port);
		inet_pton(AF_INET,ip_addr.c_str(),&(m_addr.sin_addr));
	}

	netaddress(const struct sockaddr_in& addr):m_addr(addr){

	}

	const struct sockaddr_in& get_sock_netaddr() const {
		return m_addr;
	}

	void set_sock_netaddress(const struct sockaddr_in& addr){
		m_addr = addr;
	}
private:
	struct sockaddr_in m_addr;
}

}}

#endif
