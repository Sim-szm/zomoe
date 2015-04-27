/* =====================================================================================
 *
 *       Filename:  event_base.h
 *       Created :  2015年04月27日 16时26分56秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */
#include <map>
#include <iostream>

namespace zomoe { namespace network {

enum selectioney_ {

};
typedef struct {
	int OP_READ = 1 << 0;
	int OP_WRITE = 1 << 2;
	int OP_CONNECT = 1 << 3;
	int OP_ACCEPT = 1 << 4;
}selectionkey;

class event_base {
public:
	event_base();
	~event_base();
	std::map<int,int> map_event_key();
private:
	selectionkey event_key_;
	std::map<int, int> event_;

};
}}
