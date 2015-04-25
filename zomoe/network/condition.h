/* =====================================================================================
 * 
 *       Filename:  condition.h
 *       Created :  2015年04月25日 16时20分20秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */
#ifndef CONDITION_H
#define CONDITION_h

#include <pthread.h>
#include "mutex.h"

namespace zomoe { namespace network {

class condition{
public:
	condition(mutex_lock& mutex):m_mutex(mutex){
		pthread_cond_init(&m_cond,NULL);
	}
	~condition();
	void condition_wait();
	void condition_notify();
	void condition_notifyAll();
private:
	pthread_cond_t m_cond;
	mutex_lock& m_mutex;
};

condition::~condition(){
	pthread_cond_destroy(&m_cond);
}

void condition::condition_wait(){
	pthread_cond_wait(&m_cond,m_mutex.get_mutex());
}

void condition::condition_notify(){
	pthread_cond_signal(&m_cond);
}

void condition::condition_notifyAll(){
	pthread_cond_broadcast(&m_cond);
}

}}

#endif

