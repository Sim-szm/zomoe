/* =====================================================================================
 * 
 *       Filename:  mutex.h
 *       Created :  2015年04月25日 16时06分20秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

namespace zomoe { namespace network{

class mutex_lock{
public:
	mutex_lock();
	~mutex_lock();
	void lock_mutex();
	void unlock_mutex();
	pthread_mutex_t* get_mutex();
private:
	pthread_mutex_t m_mutex;
};

mutex_lock::mutex_lock(){
	pthread_mutex_init(&m_mutex,NULL);
}

mutex_lock::~mutex_lock(){
	pthread_mutex_destroy(&m_mutex);
}

void mutex_lock::lock_mutex(){
	pthread_mutex_lock(&m_mutex);
}

void mutex_lock::unlock_mutex(){
	pthread_mutex_unlock(&m_mutex);
}

pthread_mutex_t* mutex_lock::get_mutex(){
	return &m_mutex;
}

class mutex_lock_guard{
public:
	explicit mutex_lock_guard(mutex_lock& mutex):m_mutex(mutex){
		m_mutex.lock_mutex();
	}
	~mutex_lock_guard(){
		m_mutex.unlock_mutex();
	}
private:
	mutex_lock& m_mutex;
};

}}

#endif


