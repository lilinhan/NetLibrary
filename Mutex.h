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

namespace NetworkLib{
    class MutexLock{
        private:
            pthread_mutex_t _mutex;
        public:
            MutexLock() {
                if(pthread_mutex_init(&_mutex, NULL) != 0) { //init mutex
                    throw std::exception();
                }
            }
            ~MutexLock() {  //destruct mutex
                pthread_mutex_destroy(&_mutex);
            }

            bool lock() { //lock
                return pthread_mutex_lock(&_mutex) == 0;
            }
            bool unlock() {  //unlock
                return pthread_mutex_unlock(&_mutex) == 0;
            }

            pthread_mutex_t *getmutex() {  //get mutex
                return &_mutex;
            }
    };

    class MutexLockGuarnd{
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

