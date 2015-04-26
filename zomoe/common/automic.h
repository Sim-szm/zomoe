/* =====================================================================================
 * 
 *       Filename:  automic.cc
 *       Created :  2015年04月26日 16时57分48秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */

#ifndef AUTOMIC_H
#define AUTOMIC_H

#include <stdint.h>
namespace zomoe { namespace common {

template<typename T>
class automic_for_t{
public:
	automic_for_t():m_value(0){
	//......
	}

	T get_value(){
		return __sync_val_compare_and_swap(&m_value,0,0);
	}

	T add_with_x(T x){
		return __sync_fetch_and_add(&m_value,x);
	}

	T add_and_get(T x){
		return add_with_x(x)+x;
	}

	T increment_t(){
		add_and_get(1);
	}

	T get_and_set(T new_value){
		return __sync_lock_test_and_set(&m_value,new_value);
	}

	void add(T x){
		add_with_x(x);
	}

	void increment(){
		increment_t();
	}

	void dcrement(){
		add_and_get(-1);
	}
private:
	volatile T m_value;
};

}}
#endif
