/*************************************************************************
    > File Name: Mutex.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月29日 星期一 14时58分29秒
 ************************************************************************/
#ifndef _MUTEX_H_
#define _MUTEX_H_

#include<iostream>
#include<pthread.h>
#include"noncopyable.h"

namespace NetworkLib{
    class MutexLock:noncopyable {
        private:
            pthread_mutex_t _mutex;
        public:
            MutexLock() {
                if(pthread_mutex_init(&_mutex, NULL) != 0) {
                    throw std::exception();
                }
            }
            ~MutexLock() {
                pthread_mutex_destroy(&_mutex);
            }

            bool lock() {
                return pthread_mutex_lock(&_mutex) == 0;
            }
            bool unlock() {
                return pthread_mutex_unlock(&_mutex) == 0;
            }

            pthread_mutex_t *getmutex() {
                return &_mutex;
            }
    };

    class MutexLockGuarnd:noncopyable {
        private:
            MutexLock &_mutex;

        public:
            explicit MutexLockGuarnd(MutexLock &mutex):_mutex(mutex) {
                _mutex.lock();
            }
            ~MutexLockGuarnd() {
                _mutex.unlock();
            }
    };
}

#endif

