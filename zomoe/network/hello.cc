/*
 * =====================================================================================
 *
 *       Filename:  hello.cc
 *        Version:  1.0
 *        Created:  2015年04月25日 17时26分47秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <iostream>
#include <zomoe/common/mutex.h>
#include <zomoe/common/condition.h>
#include <zomoe/network/socket_base.h>
#include <zomoe/network/netaddress.h>

int main(int argc, char *argv[])
{
	std::cout << zomoe::common::fucktest << std::endl;
	return 0;
}

