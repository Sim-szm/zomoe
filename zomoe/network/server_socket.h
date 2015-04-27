/* =====================================================================================
 *
 *       Filename:  server_socket.h
 *       Created :  2015年04月27日 16时26分56秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */

 #ifndef SERVER_SOCKET_H
 #define SERVER_SOCKET_H

 #include <zomoe/network/socket_base.h>
 #include <zomoe/network/netaddress.h>
 #include <map>

 using namespace zomoe;
 using namespace zomoe::network;

 namespace zomoe { namespace network{

 class server_socket {
 public:
 	server_socket(uint16_t port);
 	server_socket(netaddress& server_addr, uint16_t port);
 	~server_socket(){
 	}
 	int server_accept_open();

 private:
 	socket_event server_;
 	std::map<int,struct sockaddr_in> clientset_;
 };

 }}

 #endif