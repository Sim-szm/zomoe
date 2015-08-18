/*
 * =====================================================================================
 *
 *        Filename:  zomoe_log.h
 *        Created :  2015年08月18日 16时06分46秒
 *        Email   :  xianszm007@gmail.com
 *        Compiler:  g++
 *        Author  :  zomoe
 *        Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */

#ifndef ZOMOE_LOG_H
#define ZOMOE_LOG_H

#include <cstring>
#include <string>

namespace zomoe { namespace log_module {

extern int log_level;

const int ERROR_L = 1;
const int WARN_L = 2;
const int INFO_L = 3;
const int DEBUG_L = 4;

std::string get_time();

void zomoe_error(const char *format, ...);
void zomoe_warn(const char *format, ...);
void zomoe_info(const char *format, ...);
void zomoe_debug(const char *format, ...);
void set_log_level(const char *level);


#define ZOMOE_ERROR(format,args...) \
	if (log_level >= ERROR_L) { \
		zomoe_error("%S %S |%s|%d :" format,get_time().c_str(),"ERROR",__FILE__,__LINE__,##args)
	}
#define ZOMOE_WARN(format,args...) \
	if (log_level >= WARN_L) { \
		zomoe_warn("%S %S |%s|%d :" format,get_time().c_str(),"WARN",__FILE__,__LINE__,##args)
	}
#define ZOMOE_DEBUG(format,args...) \
	if (log_level >= DEBUG_L) { \
		zomoe_debug("%S %S |%s|%d :" format,get_time().c_str(),"DEBUG",__FILE__,__LINE__,##args)
	}
#define ZOMOE_INFO(format,args...) \
	if (log_level >= INFO_L) { \
		zomoe_info("%S %S |%s|%d :" format,get_time().c_str(),"INFO",__FILE__,__LINE__,##args)
	}
}}

#endif
