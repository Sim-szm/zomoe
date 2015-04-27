/* =====================================================================================
 *
 *       Filename:  server_socket.cc
 *       Created :  2015年04月27日 17时26分56秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */
#include <zomoe/network/server_socket.h>
#include <cstring>
#include <cassert>
using namespace zomoe;
using namespace zomoe::network;

namespace zomoe { namespace network {

server_socket::server_socket(uint16_t port){
	netaddress server_addr = new netaddress(port);
	socket_event serversocket = new socket_event();
	int sockfd = serversocket.new_socket();
	assert(sockfd > 0);
	serversocket.set_reuseaddr(true);
	serversocket.bind_t(server_addr);
	serversocket.listen_t();
	server_ = serversocket;
}

server_socket::server_socket(std::string ip_addr, uint16_t port){
	netaddress server_addr = new netaddress(ip_addr,port);
	socket_event serversocket = new socket_event();
	int sockfd = serversocket.new_socket();
	serversocket.set_reuseaddr(true);
	serversocket.bind_t(server_addr);
	serversocket.listen_t();
	server_ = serversocket;
}

int server_socket::server_accept_open(){
	netaddress client_addr = new netaddress();
	int connfd = server_.accept_t(&client_addr);
	if (connfd <= 0) {
		perror ("accept_t error!");
		return -1;
	}
	clientset_.insert(std::pair<int,struct sockaddr_in> (connfd,client_addr.get_sock_netaddr());
	/**
	 *这里要建立notify机制，通知工作线程组去执行任务
	 */
	return 0
}

}}
