/* =====================================================================================
 * 
 *       Filename:  lockfreeQueue.h
 *       Created :  2015年04月25日 13时06分20秒
 *       Email   :  xianszm007@gmail.com
 *       Compiler:  g++
 *       Author  :  zomoe
 *       Company :  free coder as aspire, but work for life
 * 
 * =====================================================================================
 */

#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H
#pragma once 


#include <stdint.h>
#include <sys/types.h>

#pragma pack(1)

namespace common {

typedef struct {

	volatile int32_t next;
	volatile int32_t use_flag;

}unit_head;

typedef struct {

	int32_t unit_size;
	int32_t max_unit_num;

	volatile int32_t p_head;
	volatile int32_t p_tail;

	volatile int32_t w_tail;

	volatile int32_t w_len;
	volatile int32_t r_len;

}queue_head;

typedef void * lock_free_queue;

/*
 *
 *  <  0  error 
 * ==  0  success
 * shm_key: use share memory if not zero !
 */
int lock_fQueue_init(lock_free_queue *queue,key_t shm_key, int32_t unit_size,int32_t max_unit_num);

/*
 *
 * <  -1  error 
 * == -1  full
 * ==  0  success
 *
 */
int lock_fQueue_push(lock_free_queue queue,void *unit);

/*
 *
 * <  -1  error 
 * == -1  empty
 * ==  0  success
 *
 */
int lock_fQueue_pop(lock_free_queue queue,void *unit);

/*
 *
 * <  0  error 
 * >= 0 len
 *
 */
int lock_fQueue_len(lock_free_queue queue);

}

#endif
