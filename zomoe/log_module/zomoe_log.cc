/*
 * =====================================================================================
 *
 *        Filename:  zomoe_log.cc
 *        Created :  2015年08月18日 16时49分18秒
 *        Email   :  xianszm007@gmail.com
 *        Compiler:  g++
 *        Author  :  zomoe
 *        Company :  free coder as aspire, but work for life
 *
 * =====================================================================================
 */
#include <fstream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "zomoe_log.h"


namespace zomoe { namespace log_module {

int log_level = DEBUG_L; //default as debug
char log_s[2048];
char log_file_str[50] = "log_data/log.txt";

std::string log_ptr;

std::string get_time() {

	char timeshow[50];
	struct timeval tv;
	struct tm *tm;
	gettimeofday(&tv,NULL);
	tm = localtime(&tv.tv_sec);
	sprintf(timeshow,"%04d-%02d-%02d %02d:%02d:%02d.%03d",\
				tm->tm_year + 1900, tm->tm_mon + 1, rm->tm_mday,\
				tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(tv.tv_usec/1000));
	return std::string(timeshow);

}

void set_log_level(const char *level) {

	if (strcasecmp(level,"ERROR") == 0) {
		return ERROR_L;
	}
	if (strcasecmp(level,"WARN") == 0) {
		return WARN_L;
	}
	if (strcasecmp(level,"INFO") == 0) {
		return INFO_L;
	}
	if (strcasecmp(level,"DEBUG") == 0) {
		return DEBUG_L;
	}
	return DEBUG_L;
	
}

int get_log_config(char *filename) {
	std::map<std::string, std::string> configs;
	std::stringstream ss;
	std::fstream fs(filename);
	if (!fs.is_open()) {
		return -1;
	}
	while (fs.good()) {
		std::string line;
		std::getline(fs,line);
		ss << line;
		std::string key,value; // filter string by std::getline
		std::getline(ss,key,'=');
		std::getline(ss,value,'=');
		configs[key] = value;
	}
	fs.close();

	if (!configs.empty()) {
		std::string log_str = configs["log_level"];
		set_log_level(log_str.c_str());
		log_ptr = configs["log_file"];
	}

	return 0;
}

void output_log_stream(const char *fromat, va_list ap) {

	std::fstream fs(log_ptr.c_str(), std::fstream::out | std::fstream::app);
	if (fs.is_open()) {
		vsprintf(log_s, format, ap);
		fs << log_s << "\n";
		fs.close();
	}
}

void zomoe_error(const char *format, ...) {
	get_log_config(log_file_str);
	if (log_level < ERROR_L) {
		return;
	}

	va_list ap;
	va_start(ap,format);
	output_log_stream(format,ap);
	va_end(ap);

}

void zomoe_warn(const char *format, ...) {
	get_log_config(log_file_str);
	if (log_level < WARN_L) {
		return;
	}
	va_list ap;
	va_start(ap,format);
	output_log_stream(format,ap);
	va_end(ap);

}

void zomoe_info(const char *format, ...) {
	get_log_config(log_file_str);
	if (log_level < INFO_L) {
		return;
	}
	va_list ap;
	va_start(ap,format);
	output_log_stream(format,ap);
	va_end(ap);
}

void zomoe_debug(const char *format, va_list ap) {
	get_log_config(log_file_str);
	if (log_level < DEBUG_L) {
		return;
	}
	va_list ap;
	va_start(ap,format);
	output_log_stream(format,ap);
	va_end(ap);
}

}}
